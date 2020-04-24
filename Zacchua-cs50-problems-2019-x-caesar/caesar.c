#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for(int i = 0; i < strlen(argv[1]); i++)
           if(isdigit(argv[1][i])) 
           {
               int k = atoi(argv[1]);
               string plain = get_string("plaintext: "); 
               for (i = 0; i < strlen(plain); i++)
               {
                   if (plain[i] > 65 && plain[i] < 123)
                   {
                       plain[i] = plain[i] + k % 26;
                   }
                   else
                   {
                       plain[i] = plain [i];
                   }
               }
               printf("ciphertext: %s\n", plain);
           }
           else
           {
               printf("Usage: ./caesar key\n");
               return 1;
           }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
