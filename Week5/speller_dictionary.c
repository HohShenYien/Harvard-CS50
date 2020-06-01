// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 2999; // Largest prime number below 3000
// Using prime number as for the Rabin-Karp rolling hash , and below 3000 so that
// every linked list hopefully have about 143000/3000 = 48 nodes.

// Hash table
node *table[N];
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *tmp = table[hash(word)];
    while (tmp != NULL)
    {
        // Regardless of upper or lowercase using strcasecmp function
        if (strcasecmp(word, tmp -> word) == 0)
        {
            return true;
        }
        tmp = tmp -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // I am using the Rabin-Karp rolling hash function found
    int a = 256;
    // Using a random number less than N
    long res = 0;
    // The hash function
    for (int i = 0, j = strlen(word); i < j; i++)
    {
        //converts every letter to lowercase
        res += (tolower(word[i]) * pow(a, j - i));
    }
    // somehow the final value can be negative.... so I used absolute
    return labs(res % N);
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    // checking if the file is empty
    if (dict == NULL)
    {
        return false;
    }
    // Two nodes required, mynode for current node and tmp stores the new node
    node *mynode, *tmp ;
    // Stores the word
    char tempword[(LENGTH + 1)];
    int ind, i;
    for (i = fscanf(dict, "%s", tempword); i != EOF; i = fscanf(dict, "%s", tempword))
    {
        count++;
        // hash value
        ind = hash(tempword);
        // allocating space for tmp
        tmp = malloc(sizeof(node));
        strcpy(tmp -> word, tempword);
        tmp -> next = NULL;
        // If the position is NULL then assign it straight away
        if (table[ind] == NULL)
        {
            table[ind] = tmp;
        }
        else
        {
            // If not NULL, then it'll travel down the linked list
            tmp -> next = table[ind];
            table[ind] = tmp;
            mynode = table[ind];
            // Until the next node is null
            while (mynode -> next != NULL)
            {
                mynode = mynode -> next;
            }
            mynode -> next = tmp;
        }
    }
    // Freeing up and closing the dict file
    fclose(dict);
    //free(tmp); <- A big mistake here
    //I am not supposed to free tmp else the last pointer would point nowhere, causing many errors in check50
    
    // Nothing is wrong if i == EOF
    if (i == EOF)
    {
        return true;
    }
    return false;
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    /*// I assume the size function is to travel the dictionary again?
    // Or else I will add a count function in load but nevermind
    int count = 0;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        while (tmp != NULL)
        {
            count++;
            tmp = tmp -> next;
        }
    }
    return count; */
    // nevermind again, I made a change
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0 ; i < N; i++)
    {
        //Cheking if the liked list is empty
        if (table[i] != NULL)
        {
            //usfull variables
            node *cursor = table[i];
            node *temp = cursor;

            //freeing the linked lists
            while (cursor != NULL)
            {
                cursor = cursor -> next;
                free(temp);
                temp = cursor;
            }
        }
    }
    return true;
}
