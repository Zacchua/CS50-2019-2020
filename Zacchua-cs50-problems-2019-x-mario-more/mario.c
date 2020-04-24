#include <cs50.h>
#include <stdio.h>

int get_positive_int (string prompt);
    
int main(void)
{
    int height = get_positive_int("height:");
    for(int j=0; j<height; j++)
    {
        for(int k=7; k>j; k--)
        {
            printf (" ");
        }
        for(int l=0; l<=j; l++)
        {
            printf ("#");
        }
        printf ("  ");
        for (int m=0; m<=j; m++)
        {
            printf ("#");
        }
        printf("\n");
    }
}

int get_positive_int (string prompt)
{
    int h;
    do 
    { 
      h = get_int("%s", prompt);
    }
      while (h<0 || h>8);
      return h;
}
