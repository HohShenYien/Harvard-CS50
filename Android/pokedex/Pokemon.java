package edu.harvard.cs50.pokedex;

import java.io.Serializable;
// serializable so that can be packed into bundle to send to next intent
public class Pokemon implements Serializable {
    private String name;
    private String url;
    private boolean caught;

    Pokemon(String name, String url) {
        this.name = name;
        this.url = url;
        caught = false;
    }

    public String getName() {
        return name;
    }

    public String getUrl() {
        return url;
    }

    public void changeState(boolean currentState)
    {
        this.caught = !currentState;
    }

    public boolean getCaught(){return caught; }
}
