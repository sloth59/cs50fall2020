#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float red, green, blue;
    int avg;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            avg = round((red + green + blue) / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float red, green, blue;
    int rtemp, gtemp, btemp;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            rtemp = round(0.393 * red + 0.769 * green + 0.189 * blue);
            gtemp = round(0.349 * red + 0.686 * green + 0.168 * blue);
            btemp = round(0.272 * red + 0.534 * green + 0.131 * blue);

            if (rtemp > 255)
            {
                rtemp = 255;
            }
            if (gtemp > 255)
            {
                gtemp = 255;
            }
            if (btemp > 255)
            {
                btemp = 255;
            }

            image[i][j].rgbtRed = rtemp;
            image[i][j].rgbtGreen = gtemp;
            image[i][j].rgbtBlue = btemp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, k;
    RGBTRIPLE temp;
    for (i = 0; i < height; i++)
    {
        j = 0;
        k = width - 1;
        while (j < k)
        {
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
            j++;
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    float average_blue, average_green, average_red;
    int rows, cols;
    int pixels;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average_blue = 0, average_green = 0, average_red = 0, pixels = 0;

            for (rows = i - 1; rows <= i + 1; rows++)
            {
                for (cols = j - 1; cols <= j + 1; cols++)
                {
                    if ((rows >= 0 && rows < height) && (cols >= 0 && cols < width))
                    {
                        average_blue += image[rows][cols].rgbtBlue;
                        average_green += image[rows][cols].rgbtGreen;
                        average_red += image[rows][cols].rgbtRed;
                        pixels++;
                    }
                }
            }

            average_blue =  round(average_blue / pixels);
            average_green = round(average_green / pixels);
            average_red = round(average_red / pixels);

            new_image[i][j].rgbtBlue = average_blue;
            new_image[i][j].rgbtGreen = average_green;
            new_image[i][j].rgbtRed = average_red;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}
