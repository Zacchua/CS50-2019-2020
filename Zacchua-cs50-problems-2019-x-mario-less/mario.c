#include <cs50.h>
#include <stdio.h>

int get_positive_int (string prompt);

int main(void)
{
  int h = get_positive_int ("height:");
  for (int j=1; j<=h; j++)
    {
      for (int l=8; l>j; l--)
      {
          printf(" ");
      }
      for (int k=0; k<j; k++)
      {
          printf ("#");
      }
        printf ("\n");
    }
}

int get_positive_int (string prompt)
{
    int i;
    do
    {
        i = get_int ("%s", prompt);
    }
    while (i<1 || i>8);
    return i;        
}
