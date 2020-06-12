package edu.harvard.cs50.pokedex;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Filter;
import android.widget.Filterable;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PokedexAdapter extends RecyclerView.Adapter<PokedexAdapter.PokedexViewHolder> implements Filterable {
    public static class PokedexViewHolder extends RecyclerView.ViewHolder {
        public LinearLayout containerView;
        public TextView textView;

        PokedexViewHolder(View view) {
            super(view);
            // Row
            containerView = view.findViewById(R.id.pokedex_row);
            textView = view.findViewById(R.id.pokedex_row_text_view);

            containerView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    // Send the information into intent!
                    // This getTag comes from putTag into the conatiner at the bottom
                    Pokemon current = (Pokemon) containerView.getTag();
                    Intent intent = new Intent(v.getContext(), PokemonActivity.class);
                    // Send the url!
                    intent.putExtra("url", current.getUrl());
                    // Send the pokemon!
                    Bundle bundle = new Bundle();
                    bundle.putSerializable("pokemon", current);
                    intent.putExtra("extra", bundle);
                    // Start the next activity
                    v.getContext().startActivity(intent);
                }
            });
        }
    }

    private List<Pokemon> pokemon = new ArrayList<>();
    private RequestQueue requestQueue;
    private List<Pokemon> filteredPokemon;
    // switch between all the pokemon and filtered
    private List<Pokemon> cur = new ArrayList<>();
    // constructor class loads all the pokemons
    PokedexAdapter(Context context) {
        requestQueue = Volley.newRequestQueue(context);
        loadPokemon();
    }

    public void loadPokemon() {
        String url = "https://pokeapi.co/api/v2/pokemon?limit=151";
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    JSONArray results = response.getJSONArray("results");
                    for (int i = 0; i < results.length(); i++) {
                        JSONObject result = results.getJSONObject(i);
                        String name = result.getString("name");
                        pokemon.add(new Pokemon(
                            name.substring(0, 1).toUpperCase() + name.substring(1),
                            result.getString("url")
                        ));

                    }
                    Log.d("CS50xxx",pokemon.toString());
                    cur = pokemon;
                    notifyDataSetChanged();
                } catch (JSONException e) {
                    Log.e("cs50", "Json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon list error", error);
            }
        });

        requestQueue.add(request);
    }
    // Expand the row structure in xml layout
    @NonNull
    @Override
    public PokedexViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.pokedex_row, parent, false);

        return new PokedexViewHolder(view);
    }
    // This is for searching
    private class PokemonFilter extends Filter {
        @Override
        protected FilterResults performFiltering(CharSequence constraint) {
            List<Pokemon> filteredTmp = new ArrayList<>();
            // using regex.....
            String pattern = constraint.toString();
            Pattern r = Pattern.compile(pattern);
            // check all the names in pokemon data
            for (int i = 0; i < pokemon.size(); i++){
                String name = pokemon.get(i).getName();
                Matcher match = r.matcher(name);
                if (match.find()){
                    // send it to filtered if matched
                    filteredTmp.add(pokemon.get(i));
                }
            }
            FilterResults results = new FilterResults();
            results.values = filteredTmp; // you need to create this variable!
            results.count = filteredTmp.size();
            return results;
        }

        @Override
        protected void publishResults(CharSequence constraint, FilterResults results) {
            // I just change cur the filtered version
            // So first line actually don't need also can.....
            filteredPokemon = (List<Pokemon>) results.values;
            cur = filteredPokemon;
            notifyDataSetChanged();
        }
    }
    // This one edits whatever in the row xml for each row (holder)
    @Override
    public void onBindViewHolder(@NonNull PokedexViewHolder holder, int position) {
        Pokemon current = cur.get(position);
        holder.textView.setText(current.getName());
        holder.containerView.setTag(current);
    }

    @Override
    public int getItemCount() {
        return cur.size();
    }

    @Override
    public Filter getFilter() {
        return new PokemonFilter();
    }
}
