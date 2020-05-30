#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average; // I used floats so that the average is rounded nicely
    for (int i = 0; i < height; i++)
    {
        // for every pixel
        for (int j = 0; j < width; j++)
        {
            // getting average of the RGB values of the pixel
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Changes value of every pixel to the average value
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        // for every pixel
        for (int j = 0; j < width / 2; j++)
        {
            // swap every pixel with the pixel from the back
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float total[3];
    int count;
    // Temp stores the new values
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        // for every pixel
        for (int j = 0; j < width; j++)
        {
            // total sums up the RGB values
            total[0] = 0;
            total[1] = 0;
            total[2] = 0;
            // checking the number of pixels taken
            count = 0;
            // Get the 3 neares rows
            for (int p = i - 1; p <= i + 1; p++)
            {
                // If not satisfies means it's either corner or edge
                if (p >= 0 && p < height)
                {
                    // Columns
                    for (int q = j - 1; q <= j + 1; q++)
                    {
                        if (q >= 0 && q < width)
                        {
                            count ++;
                            total[0] += image[p][q].rgbtRed;
                            total[1] += image[p][q].rgbtGreen;
                            total[2] += image[p][q].rgbtBlue;
                        }
                    }
                }
            }
            temp[i][j].rgbtRed = round(total[0] / count);
            temp[i][j].rgbtGreen = round(total[1] / count);
            temp[i][j].rgbtBlue = round(total[2] / count);
        }
    }

    for (int i = 0; i < height; i++)
    {

        // replace back the pixels from temp into image
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float Gx[3], Gy[3]; // stores the total of Gx and Gy
    float tempx[3][3][3], tempy[3][3][3]; // stores the matrix produced for each RGB
    float g[3]; // stores the final g values for each of RGB
    // Below are the two matrix from the question
    float GXm[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float GYm[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Stores the final values
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        // for every pixel
        for (int j = 0; j < width; j++)
        {
            // initialise the values in Gx and Gy to zero
            for (int x = 0; x < 3; x++)
            {
                Gx[x] = 0;
                Gy[x] = 0;
            }
            // For every column
            for (int p = i - 1, countc = 0; p <= i + 1; p++, countc++)
            {
                // for every pixel
                for (int q = j - 1, countr = 0; q <= j + 1; q++, countr++)
                {

                    // check if it's edge block or corner block or not, if pass then calculate
                    if ((p >= 0 && p < height) && (q >= 0 && q < width))
                    {
                        // Matrix multiplication
                        tempx[0][countc][countr] = GXm[countc][countr] * image[p][q].rgbtRed;
                        tempx[1][countc][countr] = GXm[countc][countr] * image[p][q].rgbtGreen;
                        tempx[2][countc][countr] = GXm[countc][countr] * image[p][q].rgbtBlue;
                        tempy[0][countc][countr] = GYm[countc][countr] * image[p][q].rgbtRed;
                        tempy[1][countc][countr] = GYm[countc][countr] * image[p][q].rgbtGreen;
                        tempy[2][countc][countr] = GYm[countc][countr] * image[p][q].rgbtBlue;

                    }
                    else
                    {
                        // sets RGB to zero
                        for (int x = 0; x < 3; x++)
                        {
                            tempx[x][countc][countr] = 0;
                            tempy[x][countc][countr] = 0;
                        }
                    }
                }
            }
            // summing up all the elements in the matrix
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    for (int z = 0; z < 3; z++)
                    {
                        Gx[x] += tempx[x][y][z];
                        Gy[x] += tempy[x][y][z];
                    }
                }
            }
            for (int x = 0; x < 3; x ++)
            {
                g[x] = pow((Gx[x] * Gx[x] + Gy[x] * Gy[x]), 0.5);
                g[x] = round(g[x]);
            }
            if (g[0] < 256)
            {
                temp[i][j].rgbtRed = g[0];
            }
            else
            {
                temp[i][j].rgbtRed = 255;
            }
            if (g[1] < 256)
            {
                temp[i][j].rgbtGreen = g[1];
            }
            else
            {
                temp[i][j].rgbtGreen = 255;
            }
            if (g[2] < 256)
            {
                temp[i][j].rgbtBlue = g[2];
            }
            else
            {
                temp[i][j].rgbtBlue = 255;
            }
        }

    }
    for (int i = 0; i < height; i++)
    {

        // replace back the pixels from temp into image
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
