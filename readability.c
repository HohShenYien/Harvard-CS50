#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>


void test(string txt);

int main(void)
{
    string text = get_string("Text: "); //Getting input
    test(text);
}

void test(string txt)
{
    int letters = 0, words = 0, sentences = 0;

    for (int i = 0; txt[i] != '\0'; i++)
    {
        if (isupper(txt[i])) //if it is uppercase letter or
        {
            letters++;
        }
        else if (islower(txt[i])) // a lowercase letter , then letters count increase
        {
            letters++;
        }

        else if (isspace(txt[i])) // increase words count when encounter space
        {
            words++;
        }

        else if (txt[i] == '.' || txt[i] == '?' || txt[i] == '!') // increase sentence count when encounter those symbols
        {
            sentences++;
        }
    }
    //the last word in the text does not have any consequent space so add one to word count
    if (words != 0) //if null text, no addition
    {
        words++;
    }
    //debugging
    //printf("letters: %i , words: %i , sentences: %i \n", letters, words, sentences);
    float L = (float) letters / words * 100; // average letters per 100 words
    float S = (float) sentences / words * 100; // average sentences per 100 words
    float index = 0.0588 * L - 0.296 * S - 15.8; // the index
    //debugging purpose
    //printf("L is %f, S is %f, index is %f\n", L, S, index);
    int res = round(index);
    //checking the value of index and output their respective result
    if (res < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (res >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", res);
    }

}
