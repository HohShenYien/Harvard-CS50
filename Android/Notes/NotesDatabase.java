package edu.harvard.cs50.notes;

import androidx.room.Database;
import androidx.room.RoomDatabase;
// Creating the database and getting the class required
// Also combines with the DAO class
@Database(entities = {Note.class}, version = 1)
public abstract class NotesDatabase extends RoomDatabase {
    public abstract NoteDao noteDao();
}