#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_positive_float (string prompt);

int main(void)
{
    float change;
    int r, r1, r2, n, n1, n2, total;
    change = get_positive_float ("change:");
    int cents = round(change*100);
    r = cents % 25; //remainder after removing 25c
    r1 = r % 10; // remainder after removing 10c
    r2 = r1 % 5; // no. of 1c coins
    n = cents / 25; // no. of 25c coins
    n1 = r / 10; // no. of 10c coins
    n2 = r1 / 5; // no. of 5c coins
    total = r2+n+n1+n2;
    printf("no. of coins:%i\n", total);
}

float get_positive_float (string prompt)
{
     float c;
        do 
        {
            c= get_float("%s", prompt);
        }
    while (c<0 || c>=1);
        return c;
}
   
