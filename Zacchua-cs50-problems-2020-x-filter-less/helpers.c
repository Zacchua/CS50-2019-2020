#include "helpers.h"
#include "math.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int ave = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/ 3;
            image[i][j].rgbtBlue = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtRed = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int k = 0; k < height; k++)
    {
        for(int l = 0; l < width; l++)
        {
            int sepiared = round(.393 * image[k][l].rgbtRed + .769 * image[k][l].rgbtGreen + .189 * image[k][l].rgbtBlue);
            int sepiagreen = round(.349 * image[k][l].rgbtRed + .686 * image[k][l].rgbtGreen + .168 * image[k][l].rgbtBlue);
            int sepiablue = round(.272 * image[k][l].rgbtRed + .534 * image[k][l].rgbtGreen + .131 * image[k][l].rgbtBlue);

            if(sepiared > 255)
            {
                sepiared = 255;
            }

            if(sepiagreen > 255)
            {
                sepiagreen = 255;
            }

            if(sepiablue > 255)
            {
                sepiablue = 255;
            }

            image[k][l].rgbtRed = sepiared;
            image[k][l].rgbtGreen = sepiagreen;
            image[k][l].rgbtBlue = sepiablue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int m = 0; m < height; m++)
    {
        for(int n = 0, w = (round(width/2)+1); n < w; n++)
        {
            //copy right hand side into temp variable
            RGBTRIPLE ref = image[m][(width - 1 - n)];

            //copy left had side to right hand side
            image[m][(width - 1 - n)] = image[m][n];

            //copy temp variable onto left hand side
            image[m][n] = ref;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //making new array to store temp values and set counter to 0
    RGBTRIPLE ogimage[height][width];

    for(int d = 0; d < height; d++)
    {
        for(int e = 0; e < width; e++)
        {
            ogimage[d][e] = image[d][e];
        }
    }

    //iterating over each pixel
    for(int o = 0; o < height; o++)
    {
        for(int p = 0; p < width; p++)
        {
            //declaring 3 variables to store sum
            int a = 0, b = 0, c = 0;
            int count = 0;
            if(o >= 0 && p >= 0)
            {
                a += ogimage[o][p].rgbtRed;
                b += ogimage[o][p].rgbtGreen;
                c += ogimage[o][p].rgbtBlue;
                count++;
            }

            if((o-1) >= 0 && (p-1) >=0)
            {
                a += ogimage[o-1][p-1].rgbtRed;
                b += ogimage[o-1][p-1].rgbtGreen;
                c += ogimage[o-1][p-1].rgbtBlue;
                count++;
            }

            if((o-1) >= 0 && p >= 0)
            {
                a += ogimage[o-1][p].rgbtRed;
                b += ogimage[o-1][p].rgbtGreen;
                c += ogimage[o-1][p].rgbtBlue;
                count++;
            }

            if((o-1) >= 0 && (p+1) < width)
            {
                a += ogimage[o][p+1].rgbtRed;
                b += ogimage[o][p+1].rgbtGreen;
                c += ogimage[o][p+1].rgbtBlue;
                count++;
            }

            if(o >= 0 && (p-1) >= 0)
            {
                a += ogimage[o][p-1].rgbtRed;
                b += ogimage[o][p-1].rgbtGreen;
                c += ogimage[o][p-1].rgbtBlue;
                count++;
            }

            if(o >= 0 && (p+1) < width)
            {
                a += ogimage[o][p+1].rgbtRed;
                b += ogimage[o][p+1].rgbtGreen;
                c += ogimage[o][p+1].rgbtBlue;
                count++;
            }

            if((o+1) < height && (p-1) >= 0)
            {
                a += ogimage[o+1][p-1].rgbtRed;
                b += ogimage[o+1][p-1].rgbtGreen;
                c += ogimage[o+1][p-1].rgbtBlue;
                count++;
            }

            if((o+1) < height && p >= 0)
            {
                a += ogimage[o+1][p].rgbtRed;
                b += ogimage[o+1][p].rgbtGreen;
                c += ogimage[o+1][p].rgbtBlue;
                count++;
            }

            if((o+1) < height && (p+1) < width)
            {
                a += ogimage[o+1][p+1].rgbtRed;
                b += ogimage[o+1][p+1].rgbtGreen;
                c += ogimage[o+1][p+1].rgbtBlue;
                count++;
            }

            image[o][p].rgbtRed = round(a / count);
            image[o][p].rgbtGreen = round(b / count);
            image[o][p].rgbtBlue = round(c / count);
        }
    }
    return;
}
