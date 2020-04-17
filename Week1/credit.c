#include <stdio.h>
#include <cs50.h>

//check whether works for luhn algorithm
int luhn_algo(long num);
//check the types of credit card
void check_type(long num);
//get 10**num
long  pow_10(int num);

int main(void)
{
    long num = get_long("Number: ");
    //check whether pass the test or not
    if (luhn_algo(num) == 1)
    {
        printf("pass");
        //checking the type
        check_type(num);
    }
    else
    {
        printf("INVALID\n");
    }
}

int luhn_algo(long num)
{
    //starting counter at 0 because starts with 1
    int counter = 0;
    int temp1 = 0;
    int temp2 = 0;
    int mytemp ;
    long copy_temp = num;
    int total ;
    //gets the sum of number at odd and even place
    while (copy_temp > 0)
    {
        counter ++;//adding counter
        if (counter % 2 == 0)//for even position...
        {
            mytemp = copy_temp % 10 * 2;
            while (mytemp > 0) //getting the digits place
            {
                temp1 += mytemp % 10;
                mytemp /= 10;
            }
        }
        else //for odd place
        {
            temp2 += copy_temp % 10;
        }
        copy_temp /= 10; //moving to the left
    }
    //for debugging
    /*printf("even is %i and odd is %i\n",temp1,temp2);
    total = temp1 + temp2;
    printf("total is %i\n",total);*/
    total = temp1 + temp2;
    if (total % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//checking what type of credit card.....
void check_type(long num)
{
    int counter = 0;
    long temp = num;
    int start_num;
    //get length of numbers
    while (temp > 0)
    {
        counter++;
        temp /= 10;
    }
    if (counter == 15)
    {
        start_num = num / pow_10(13);
        //for amex
        if (start_num == 34 || start_num == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //for mastercard and visa....
    else if (counter == 16)
    {
        start_num = num / (pow_10(14));
        if ((start_num - 50) >= 1 && (start_num - 50) <= 5)
        {
            printf("MASTERCARD\n");
        }
        else if (start_num / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //for visa
    else if (counter == 13)
    {
        start_num = num / (pow_10(12));
        if (start_num == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
//raising 10**num
long pow_10(int num)
{
    long res = 1;
    for (int i = 0; i < num; i++)//looping through the multiplication
    {
        res *= 10;
    }
    return res;
}
