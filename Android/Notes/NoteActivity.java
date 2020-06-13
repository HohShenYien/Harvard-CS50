package edu.harvard.cs50.notes;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class NoteActivity extends AppCompatActivity {
    private EditText editText;
    private Button btnDel;
    // When enters this page:
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Getting some values from previous activity via intent
        final Intent intent = getIntent();
        // Specifically the id of the current note
        final int id = intent.getIntExtra("id", 0);
        // Setting layout and button
        setContentView(R.layout.activity_note);
        btnDel = findViewById(R.id.btnDel);
        // When the delete button is pressed:
        btnDel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Delete the item from the database
                MainActivity.database.noteDao().delete(id);
                // Then return to previous page (The main page)
                Intent returnIntent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(returnIntent);
            }
        });
        // Setting the editText and getting the value
        editText = findViewById(R.id.note_edit_text);
        editText.setText(intent.getStringExtra("content"));
    }
    // Whenever the page exits or pause:
    @Override
    protected void onPause() {
        super.onPause();
        // Getting the id and updating the new values
        Intent intent = getIntent();
        int id = intent.getIntExtra("id", 0);
        MainActivity.database.noteDao().save(editText.getText().toString(), id);
    }
}
