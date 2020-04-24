#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //check if one command line argument
    if(argc != 2)
    {
        printf("incorrect usage/n");
        return 1;
    }

    //open file and check that it can be opened
    FILE *f = fopen(argv[1], "r");
    if(f == NULL)
    {
        printf("file cannot be opened/n");
        return 1;
    }

    //read the files
    uint8_t buffer[512];
    FILE *img;
    char filename[10];
    int count = 0;
    while (&free)
    {
        int n = fread(buffer, 512, 1, f);
        if( n == 0)
        {
            fclose(img);
            break;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                count++;
            }

            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                count++;
            }
        }
        else
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(f);
}