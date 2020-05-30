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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        // for every pixel
        for (int j = 0; j < width; j++)
        {
            // computing the sepia value for each of the RGB
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue);
            // then the values are substituted into the pixel
            // if above 255 becomes 255
            if (sepiaRed < 256)
            {
                image[i][j].rgbtRed = sepiaRed;

            }
            else
            {
                image[i][j].rgbtRed = 255;
            };
            if (sepiaGreen < 256)
            {
                image[i][j].rgbtGreen = sepiaGreen;

            }
            else
            {
                image[i][j].rgbtGreen = 255;
            };
            if (sepiaBlue < 256)
            {
                image[i][j].rgbtBlue = sepiaBlue;

            }
            else
            {
                image[i][j].rgbtBlue = 255;
            };
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
