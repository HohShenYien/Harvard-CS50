#include <cs50.h>
#include <stdio.h>

int get_positive_int_less_than(int x);
void build_pyramid(int x);

int main(void)
{
    int n = get_positive_int_less_than(8);
    build_pyramid(n);
}

//this function will prompt for input
//until a positive number less than x is give
int get_positive_int_less_than(int x)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > x);
    
    return n;
}

//this function builds the pyramid
void build_pyramid(int x)
{
    //first loop for every row
    for (int i = 1; i <= x; i++)
    {
        //loop for the space
        for (int k = x; k > i; k--)
        {
            printf(" ");
        }
        //loop for the blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
