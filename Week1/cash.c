  
#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_positive_float(void);
int get_dollar(float val);
int number_of_change(int coins);

int main(void)
{
    float change = get_positive_float();
    int dollar = get_dollar(change);
    printf("%i\n", number_of_change(dollar));
}
//prompts user for change
//until a positive number is given
float get_positive_float(void)
{
    float x;
    do
    {
        x = get_float("Change owed: ");
    }
    while (x <= 0);

    return x;
}
//converts float into int for better manipulation
int get_dollar(float val)
{
    int cents = round(val * 100);
    return cents;
}
//main solution 
int number_of_change(int coins)
{
    int ans = 0;
    int temp;
    //get the remainder after taking out some 25
    temp = coins / 25;
    ans += temp;
    coins -= temp * 25;
    //same as above but for 10
    temp = coins / 10;
    ans += temp;
    coins -= temp * 10;

    temp = coins / 5;
    ans += temp;
    coins -= temp * 5;

    ans += coins;
    return ans;

}#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_positive_float(void);
int get_dollar(float val);
int number_of_change(int coins);

int main(void)
{
    float change = get_positive_float();
    int dollar = get_dollar(change);
    printf("%i\n", number_of_change(dollar));
}
//prompts user for change
//until a positive number is given
float get_positive_float(void)
{
    float x;
    do
    {
        x = get_float("Change owed: ");
    }
    while (x <= 0);

    return x;
}
//converts float into int for better manipulation
int get_dollar(float val)
{
    int cents = round(val * 100);
    return cents;
}
//main solution 
int number_of_change(int coins)
{
    int ans = 0;
    int temp;
    //get the remainder after taking out some 25
    temp = coins / 25;
    ans += temp;
    coins -= temp * 25;
    //same as above but for 10
    temp = coins / 10;
    ans += temp;
    coins -= temp * 10;

    temp = coins / 5;
    ans += temp;
    coins -= temp * 5;

    ans += coins;
    return ans;

}
