package edu.harvard.cs50.notes;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DefaultItemAnimator;
import androidx.recyclerview.widget.ItemTouchHelper;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.room.Database;
import androidx.room.Room;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

public class MainActivity extends AppCompatActivity {
    private RecyclerView recyclerView;
    private RecyclerView.LayoutManager layoutManager;
    private NotesAdapter adapter;
    public static NotesDatabase database;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Setting up the database
        database = Room
            .databaseBuilder(getApplicationContext(), NotesDatabase.class, "notes")
            .allowMainThreadQueries()
            .build();
        // The recycler view
        recyclerView = findViewById(R.id.recycler_view);
        layoutManager = new LinearLayoutManager(this);
        adapter = new NotesAdapter();

        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setAdapter(adapter);
        // Getting ItemTouchHelper on action so that the swipe and delete function
        // can work later on
        new ItemTouchHelper(itemTouchCallBack).attachToRecyclerView(recyclerView);
        // Get the add button and implements its function
        FloatingActionButton fab = findViewById(R.id.add_note_button);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                database.noteDao().create();
                adapter.reload();
            }
        });
    }
    // Whenever we go back to the activity
    @Override
    protected void onResume() {
        super.onResume();

        adapter.reload();
    }
    // The main function for swiping
    // The arguments allows only movement to the right
    ItemTouchHelper.SimpleCallback itemTouchCallBack = new ItemTouchHelper.SimpleCallback(0, ItemTouchHelper.RIGHT) {
        // I don't need any moving
        @Override
        public boolean onMove(@NonNull RecyclerView recyclerView, @NonNull RecyclerView.ViewHolder viewHolder, @NonNull RecyclerView.ViewHolder target) {
            return false;
        }
        // When swiped to the right:
        @Override
        public void onSwiped(@NonNull RecyclerView.ViewHolder viewHolder, int direction) {
            // deleting the item by first getting the index of the object in the
            // listArray, then send the index back to get the real ID
            // from checkId defined in adapter
            // Then I delete and reload the list
            database.noteDao().delete(adapter.checkId(viewHolder.getAdapterPosition()));
            adapter.reload();
        }
    };
}
