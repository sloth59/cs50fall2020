#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j;
    BYTE red,green,blue;
    int avg;
    for(i=0; i < height; i++)
    {
        for(j=0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            avg = (red + green + blue)/3;
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
    int i,j,k;
    RGBTRIPLE temp;
    for(i=0; i < height; i++)
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
    int i,j;
    int r,s;
    int red,green,blue;
    for(i=0; i < height; i++)
    {
        for(j=0; j < width; j++)
        {
            red = 0, green = 0, blue = 0;
            if(i == 0)
            {
                if(j == 0)
                {
                    for(r=i; r <= i+1; r++)
                    {
                        for(s=j; s <= j+1; s++)
                        {
                            red += image[r][s].rgbtRed;
                            green += image[r][s].rgbtGreen;
                            blue += image[r][s].rgbtBlue;
                        }
                    }
                    image[i][j].rgbtRed = red/4;
                    image[i][j].rgbtGreen = green/4;
                    image[i][j].rgbtBlue = blue/4;
                }
                else if(j == width-1)
                {
                    for(r=i; r <= i+1; r++)
                    {
                        for(s=j-1; s <= j; s++)
                        {
                            red += image[r][s].rgbtRed;
                            green += image[r][s].rgbtGreen;
                            blue += image[r][s].rgbtBlue;
                        }
                    }
                    image[i][j].rgbtRed = red/4;
                    image[i][j].rgbtGreen = green/4;
                    image[i][j].rgbtBlue = blue/4;
                }
                else
                {
                    for(r=i; r <= i+1; r++)
                    {
                        for(s=j-1; s <= j+1; s++)
                        {
                            red += image[r][s].rgbtRed;
                            green += image[r][s].rgbtGreen;
                            blue += image[r][s].rgbtBlue;
                        }
                    }
                    image[i][j].rgbtRed = red/6;
                    image[i][j].rgbtGreen = green/6;
                    image[i][j].rgbtBlue = blue/6;
                }
            }
            else if(i == height-1)
            {
                if(j == 0)
                {
                    for(r=i-1; r <= i; r++)
                    {
                        for(s=j; s <= j+1; s++)
                        {
                            red += image[r][s].rgbtRed;
                            green += image[r][s].rgbtGreen;
                            blue += image[r][s].rgbtBlue;
                        }
                    }
                    image[i][j].rgbtRed = red/4;
                    image[i][j].rgbtGreen = green/4;
                    image[i][j].rgbtBlue = blue/4;
                }
                else if(j == width-1)
                {
                    for(r=i-1; r <= i; r++)
                    {
                        for(s=j-1; s <= j; s++)
                        {
                            red += image[r][s].rgbtRed;
                            green += image[r][s].rgbtGreen;
                            blue += image[r][s].rgbtBlue;
                        }
                    }
                    image[i][j].rgbtRed = red/4;
                    image[i][j].rgbtGreen = green/4;
                    image[i][j].rgbtBlue = blue/4;
                }
                else
                {
                    for(r=i-1; r <= i; r++)
                    {
                        for(s=j-1; s <= j+1; s++)
                        {
                            red += image[r][s].rgbtRed;
                            green += image[r][s].rgbtGreen;
                            blue += image[r][s].rgbtBlue;
                        }
                    }
                    image[i][j].rgbtRed = red/6;
                    image[i][j].rgbtGreen = green/6;
                    image[i][j].rgbtBlue = blue/6;
                }
            }
            else
            {
                for(r=i-1; r <= i+1; r++)
                {
                    for(s=j-1; s <= j+1; s++)
                    {
                        red += image[r][s].rgbtRed;
                        green += image[r][s].rgbtGreen;
                        blue += image[r][s].rgbtBlue;
                    }
                }
                image[i][j].rgbtRed = red/9;
                image[i][j].rgbtGreen = green/9;
                image[i][j].rgbtBlue = blue/9;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j;
    int r,s;
    int Xred,Xgreen,Xblue;
    int Yred,Ygreen,Yblue;
    int rtemp,gtemp,btemp;
    for(i=0; i < height; i++)
    {
        for(j=0; j < width; j++)
        {
            Xred=0, Xgreen=0, Xblue=0;
            Yred=0, Ygreen=0, Yblue=0;
            for(r=i-1; r <= i+1; r++)
            {
                for(s=j-1; s <= j+1; s++)
                {
                    if(r < 0 || r > height-1 || s < 0 || s > width - 1) 
                    {
                        Xred += 0;
                        Xgreen += 0;
                        Xblue += 0;
                    
                        Yred += 0;
                        Ygreen += 0;
                        Yblue += 0;
                    }

                    else
                    {
                        if(r == i)
                        {
                            Xred += image[r][s].rgbtRed * (s-j) * 2;
                            Xgreen += image[r][s].rgbtGreen * (s-j) * 2;
                            Xblue += image[r][s].rgbtBlue * (s-j) * 2;
                        }
                        else
                        {
                            Xred += image[r][s].rgbtRed * (s-j);
                            Xgreen += image[r][s].rgbtGreen * (s-j);
                            Xblue += image[r][s].rgbtBlue * (s-j);
                        }

                        if(s == j)
                        {
                            Yred += image[r][s].rgbtRed * (r-i) * 2;
                            Ygreen += image[r][s].rgbtGreen * (r-i) * 2;
                            Yblue += image[r][s].rgbtBlue * (r-i) * 2;
                        }
                        else
                        {
                            Yred += image[r][s].rgbtRed * (r-i);
                            Ygreen += image[r][s].rgbtGreen * (r-i);
                            Yblue += image[r][s].rgbtBlue * (r-i);
                        }
                    }
                }
            }

            rtemp = sqrt( pow(Xred, 2) + pow(Yred, 2) );
            gtemp = sqrt( pow(Xgreen, 2) + pow(Ygreen, 2) );
            btemp = sqrt( pow(Yblue,2) + pow(Yblue, 2) );
            //printf("%d  %d      %d\n", Xred, Yred, rtemp);
            if(rtemp > 255)
                rtemp = 255;
            if(gtemp > 255)
                gtemp = 255;
            if(btemp > 255);
                btemp = 255; 

            image[i][j].rgbtRed = rtemp;
            image[i][j].rgbtGreen = gtemp;
            image[i][j].rgbtBlue = btemp;
        }
    }
    return;
}
