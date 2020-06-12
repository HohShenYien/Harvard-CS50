package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView descpriptionText;
    private String url;
    private RequestQueue requestQueue;
    private Button btnCatch;
    final String CAUGHTSTATE = "edu.caught_state.pokedex";
    boolean state;
    private ImageView pokemonImg;
    // URL for description
    String descURL = "https://pokeapi.co/api/v2/pokemon-species/";
    String description;
    SharedPreferences sharedpreferences;
    SharedPreferences.Editor editor ;
    Bundle newBundle;
    Pokemon currentP;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        // Getting url from previous intent
        url = getIntent().getStringExtra("url");
        nameTextView = findViewById(R.id.pokemon_name);
        pokemonImg = findViewById(R.id.pokemonImg);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        descpriptionText = findViewById(R.id.descText);
        btnCatch = findViewById(R.id.btnCatch);
        newBundle = getIntent().getBundleExtra("extra");
        currentP = (Pokemon) newBundle.getSerializable("pokemon");
        // The stored data
        sharedpreferences = getSharedPreferences(CAUGHTSTATE, Context.MODE_PRIVATE);
        state = sharedpreferences.getBoolean(currentP.getName(), false);
        editor = sharedpreferences.edit();
        currentP.changeState(!state);
        btnCheck(btnCatch, currentP);
        // Loading the data
        load();
    }

    public void load() {
        // Initiating the text to nothing
        type1TextView.setText("");
        type2TextView.setText("");
        // Requesting api from url
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    // Setting name and id
                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));
                    // from the id I get URL of description
                    descURL += Integer.toString(response.getInt("id")) + "/";
                    // I don't know why I need to nest the second request in the first one
                    final JsonObjectRequest requestDesc = new JsonObjectRequest(Request.Method.GET, descURL, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response2) {
                            try {
                                // Getting the flavor_text
                                JSONArray descArray = response2.getJSONArray("flavor_text_entries");
                                JSONObject tempObj = descArray.getJSONObject(0);
                                // Got it
                                description = tempObj.getString("flavor_text");
                                // Set it
                                descpriptionText.setText(description);
                            } catch (JSONException e) {
                                Log.e("error", "JSON description error", e);
                            }
                        }
                        // Error in response if any
                    }, new Response.ErrorListener(){
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("error", "Pokemon descriptions error", error);
                        }
                    }
                    );
                    requestQueue.add(requestDesc);
                    // Below are for setting up types
                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }
                    // Getting images for the pokemon
                    JSONObject spriteDict = response.getJSONObject("sprites");
                    String imgURL = spriteDict.getString("front_default");
                    new DownloadSpriteTask().execute(imgURL);
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });

        requestQueue.add(request);
        // I don't know why but when I put the second request below the first, it doesn't
        // reach the json file I wanted
/*
        final JsonObjectRequest requestDesc = new JsonObjectRequest(Request.Method.GET, descURL, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response2) {
                try {
                    Log.e("errorNotsure",response2.toString());
                    JSONArray descArray = response2.getJSONArray("flavor_text_entries");
                    JSONObject tempObj = descArray.getJSONObject(0);
                    description = tempObj.getString("flavor_text");
                    Log.d("description",description);
                    descpriptionText.setText(description);
                } catch (JSONException e) {
                    Log.e("error", "JSON description error", e);
                    Log.e("errorURL", descURL);
                }
            }
        }, new Response.ErrorListener(){
                @Override
                public void onErrorResponse(VolleyError error) {
                    Log.e("error", "Pokemon descriptions error", error);
                }
            }
        );
        requestQueue.add(requestDesc); */
    }
    // catch the pokemon !
    public void toggleCatch(View view){
        // I put some extra information from previous intent XD
        // The bottom 2 lines get the current selected pokemon
        newBundle = getIntent().getBundleExtra("extra");
        currentP = (Pokemon) newBundle.getSerializable("pokemon");
        // I get the capture state from storage for now
        state = sharedpreferences.getBoolean(currentP.getName(), false);
        // Change it
        currentP.changeState(state);
        // Then change the storage data
        editor.putBoolean(currentP.getName(), currentP.getCaught());
        editor.apply();
        btnCheck(btnCatch, currentP);
    }
    // Check and compare if the status of button the same as the pokemon's
    public void btnCheck(Button btn, Pokemon pokemon){
        if (pokemon.getCaught() == true){
            btn.setText("Release");
        }
        else{
            btn.setText("Catch");
        }
    }
    // Download the image
    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            }
            catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            pokemonImg.setImageBitmap(bitmap);
        }
    }
}
