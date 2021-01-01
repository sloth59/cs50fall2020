#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    int i, j;
    int r, s;
    float Xred, Xgreen, Xblue;
    float Yred, Ygreen, Yblue;
    int rtemp, gtemp, btemp;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            Xred = 0, Xgreen = 0, Xblue = 0;
            Yred = 0, Ygreen = 0, Yblue = 0;
            for (r = i - 1; r <= i + 1; r++)
            {
                for (s = j - 1; s <= j + 1; s++)
                {
                    if (r < 0 || r > height - 1 || s < 0 || s > width - 1)
                    {
                        continue;
                    }

                    else
                    {
                        if (r == i)
                        {
                            Xred += image[r][s].rgbtRed * (s - j) * 2;
                            Xgreen += image[r][s].rgbtGreen * (s - j) * 2;
                            Xblue += image[r][s].rgbtBlue * (s - j) * 2;
                        }
                        else
                        {
                            Xred += image[r][s].rgbtRed * (s - j);
                            Xgreen += image[r][s].rgbtGreen * (s - j);
                            Xblue += image[r][s].rgbtBlue * (s - j);
                        }

                        if (s == j)
                        {
                            Yred += image[r][s].rgbtRed * (r - i) * 2;
                            Ygreen += image[r][s].rgbtGreen * (r - i) * 2;
                            Yblue += image[r][s].rgbtBlue * (r - i) * 2;
                        }
                        else
                        {
                            Yred += image[r][s].rgbtRed * (r - i);
                            Ygreen += image[r][s].rgbtGreen * (r - i);
                            Yblue += image[r][s].rgbtBlue * (r - i);
                        }
                    }
                }
            }

            rtemp = round(sqrt(pow(Xred, 2) + pow(Yred, 2)));
            gtemp = round(sqrt(pow(Xgreen, 2) + pow(Ygreen, 2)));
            btemp = round(sqrt(pow(Xblue, 2) + pow(Yblue, 2)));

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

            new_image[i][j].rgbtRed = rtemp;
            new_image[i][j].rgbtGreen = gtemp;
            new_image[i][j].rgbtBlue = btemp;
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
