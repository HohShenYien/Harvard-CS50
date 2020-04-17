#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key;
    string txt;

    if (argc == 2)//checking number of command-line arguments
    {
        for (int i = 0, n = strlen(argv[1]) ; i < n; i++)
        {
            if (!(isdigit(argv[1][i]))) //if the argument consist of non-integer
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        key = atoi(argv[1]) % 26; //parsing the string into integer
        //printf("%i\n", key);

    }
    else //if length of argument does not equal to 2, error is shown
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    txt = get_string("plaintext: "); //prompting the user input
    char res[strlen(txt)]; //declaring an array of char to place the output
    //I used the value of the alphabet(ex: A/a = 0) and add back its value of whether
    //capitalised or not
    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        if (isupper(txt[i]))
        {
            res[i] = ((txt[i] - 65) + key) % 26 + 65; //the value of 'A' is 65
        }
        else if (islower(txt[i]))
        {
            res[i] = ((txt[i] - 97) + key) % 26 + 97; //the value of 'a' is 95
        }
        else
        {
            res[i] = txt[i]; //All other types of char besides characters
        }
    }
    printf("ciphertext: ");
    for (int i = 0, n = strlen(txt); i < n; i++) //printing output
    {
        printf("%c", res[i]);
    }
    printf("\n");

}
