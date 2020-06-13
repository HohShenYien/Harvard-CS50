package edu.harvard.cs50.notes;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;
// The adaptor
public class NotesAdapter extends RecyclerView.Adapter<NotesAdapter.NoteViewHolder> {
    public static class NoteViewHolder extends RecyclerView.ViewHolder {
        public LinearLayout containerView;
        public TextView nameTextView;

        //For every column in the recyclerview
        public NoteViewHolder(View view) {
            super(view);
            this.containerView = view.findViewById(R.id.note_row);
            this.nameTextView = view.findViewById(R.id.note_row_name);
            // When the column is pressed:
            this.containerView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Context context = v.getContext();
                    // Get the note object of the current column
                    Note note = (Note) containerView.getTag();
                    // Sending the id and content to the next activity
                    Intent intent = new Intent(v.getContext(), NoteActivity.class);
                    intent.putExtra("id", note.id);
                    intent.putExtra("content", note.content);

                    context.startActivity(intent);
                }
            });
        }
    }
    // The list that holds on everything
    private List<Note> notes = new ArrayList<>();
    // Whenever each column is created:
    @Override
    public NoteViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        // Inflate kinda means expand the layout for each row to me
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.note_row, parent, false);

        return new NoteViewHolder(view);
    }
    // After some understandings, the following function loads the data
    // and keep it 'on bind' before releasing it into recyclerview
    @Override
    public void onBindViewHolder(NoteViewHolder holder, int position) {
        Note current = notes.get(position);
        holder.containerView.setTag(current);
        holder.nameTextView.setText(current.content);

    }
    // Nothing much
    @Override
    public int getItemCount() {
        return notes.size();
    }
    // Checks if there's any change in data
    public void reload() {
        notes = MainActivity.database.noteDao().getAll();
        notifyDataSetChanged();
    }
    // Find the id of the object so that can be deleted in MainActivity
    public int checkId(int index){
        return notes.get(index).id;
    }
}