#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool is_valid_key(string str);

int main(int argc, string argv[])
{
    int key[26]; //declaring an array of size 26 to contain the keys in the same order
    if (argc == 2) //checking if the command-line argument has a length of 2
    {
        if (is_valid_key(argv[1])) //this functions check if the key is valid
        {
            string str = argv[1];
            int dummy; //just a value that temporary stores values

            for (int i = 0, n = strlen(str); i < n; i++)
            {
                if (isupper(str[i]))
                {
                    dummy = str[i] - 65;
                }

                else if (islower(str[i]))
                {
                    dummy = str[i] - 97;
                }

                key[i] = dummy; //dummy stores the value of each char as int
                //for example, A/a = 0, D/d = 3

            }
        }
        else
        {
            return 1; 
            //the error message has been printed in the 
            //function is_valid_key
        }
    }
    else //if command-line does not have 2 arguments
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //for checking purpose
    //printf("first and second keys are:%i and %i\n",key[0],key[1]);
    
    /*-----------------------------------------------------*/
    //the following codes are for ciphering 
    string input = get_string("plaintext:  ");
    int len = strlen(input);
    char output[len];
    char temp; //again a variable that store temporary value
    
    for (int i = 0; i < len; i++)
    {
        if (isupper(input[i]))
        {
            temp = key[input[i] - 65 ] + 65; //ciphering part as (int) A = 65
        }
        else if (islower(input[i]))
        {
            temp = key[input[i] - 97] + 97; //ciphering part as (int) a = 97
        }
        else
        {
            temp = input[i]; //if it's not a letter
        }
        output[i] = temp;
    }
    
    printf("ciphertext: "); //output
    for (int i = 0; i < len; i++)
    {
        printf("%c", output[i]); //printing every characters that are ciphered
    }
    printf("\n");
}

//A function to check if the key is valid
bool is_valid_key(string txt)
{
    bool temp[26]; //the method I'm doing is called hashmap
    for (int i = 0; i < 26; i++)
    {
        temp[i] = false; //I initialise an array of 26*false
    }
    int dummy;
    int n = strlen(txt);
    if (n != 26) //if the key length is not equal to 26
    {
        printf("Key must contain 26 characters.\n"); 
        //notice that I've included the error message in this function
        
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        //the following section getting the value of each char in the key
        if (isupper(txt[i]))
        {
            dummy = txt[i] - 65; 
        }

        else if (islower(txt[i]))
        {
            dummy = txt[i] - 97;
        }

        else
        {
            printf("Usage: ./substitution key\n");
            return false;
        }
        
        //if the value is true on this position, it means there's a repetition as I have converted
        //the value to true for every char in the key I checked.
        if (temp[dummy] == true) 

        {
            printf("Usage: ./substitution key\n");
            return false;
        }

        else
        {
            temp[dummy] = true; 
            //converting the value to true
            //the position of the array corresponds to the letter
            //For example: if I have checked 'A',temp[0] will be true
            //So if the second time 'a' has appeared, it would be detected above.
        }
    }
    return true;
}
//I didn't know that C cannot have array as return type :(
/*int[] to_key(string str)
{
    int res[26];
    int dummy;
    int n = strlen(str);

    for(int i = 0, n = strlen(str); i < n; i++)
    {
        if (isupper(str[i]))
        {
            dummy = str[i] - 65;
        }

        else if (islower(str[i]))
        {
            dummy = str[i] - 97;
        }

        res[0] = dummy;

    }
    return res;
}*/
