//including functions from other files
#include <stdio.h>
#include <cs50.h>

//main code block
int main(void)
{
    //the following codes initiate a string variable name,
    // and gets an input from user
    string name = get_string("what is your name?\n");
    //the following code prints the out put
    printf("hello, %s\n", name);
}
