package edu.harvard.cs50.notes;

import androidx.room.Dao;
import androidx.room.Query;

import java.util.List;

@Dao
public interface NoteDao {
    // Creating new table with values New note
    @Query("INSERT INTO notes (content) VALUES ('New note')")
    void create();
    // Getting all the data from notes table
    @Query("SELECT * FROM notes")
    List<Note> getAll();
    // Updating the current note with new data
    @Query("UPDATE notes SET content = :content WHERE id = :id")
    void save(String content, int id);
    // Deleting the data with specific id
    @Query("DELETE FROM notes WHERE id = :id")
    void delete(int id);
}
