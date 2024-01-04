#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each pixel in the image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average of green red blue
            int avg = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen) / 3.0);

            // set the value to the average
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each pixel in the image.
    for (int i = 0; i < height; i++)
    {
        // loop only half width since swapping pixels
        for (int j = 0; j < width / 2; j++)
        {
            // swap the pixel with counterparts on other side of the row.
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int blue = 0;
            int green = 0;
            int cnt = 0;
            // loop through sorounding pixels.
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int newrow = x + i;
                    int newcol = y + j;
                    // check if the sorounding pixel is within the image boundaries
                    if (newrow >= 0 && newrow < height && newcol >= 0 && newcol < width)
                    {
                        red += image[newrow][newcol].rgbtRed;
                        blue += image[newrow][newcol].rgbtBlue;
                        green += image[newrow][newcol].rgbtGreen;
                        cnt++;
                    }
                }
            }
            // calculate the average color value and store temp variable.
            temp[i][j].rgbtRed = round((float) red / cnt);
            temp[i][j].rgbtBlue = round((float) blue / cnt);
            temp[i][j].rgbtGreen = round((float) green / cnt);
        }
    }

    // copy the blur value from copy to original.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // sobel operater matrix
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    // loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxred = 0;
            int gxblue = 0;
            int gxgreen = 0;

            int gyred = 0;
            int gyblue = 0;
            int gygreen = 0;

            // loop through sorrounding pixels
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int newrow = x + i;
                    int newcol = y + j;

                    RGBTRIPLE pixel;

                    // check if the sorrounding pixel is within the image boudaries
                    if (newrow >= 0 && newrow < height && newcol >= 0 && newcol < width)
                    {
                        pixel = image[newrow][newcol];
                    }
                    else
                    {
                        pixel = (RGBTRIPLE){0, 0, 0};
                    }

                    // apply the sobel operator
                    gxred += pixel.rgbtRed * gx[x + 1][y + 1];
                    gxblue += pixel.rgbtBlue * gx[x + 1][y + 1];
                    gxgreen += pixel.rgbtGreen * gx[x + 1][y + 1];

                    gyred += pixel.rgbtRed * gy[x + 1][y + 1];
                    gyblue += pixel.rgbtBlue * gy[x + 1][y + 1];
                    gygreen += pixel.rgbtGreen * gy[x + 1][y + 1];
                }
            }
            // calculate the final edge values using the sobel formula and store it in temp variable
            temp[i][j].rgbtRed = fmin(round(sqrt(gxred * gxred + gyred * gyred)), 255);
            temp[i][j].rgbtBlue = fmin(round(sqrt(gxblue * gxblue + gyblue * gyblue)), 255);
            temp[i][j].rgbtGreen = fmin(round(sqrt(gxgreen * gxgreen + gygreen * gygreen)), 255);
        }
    }

    // copy the edge-detected value from temp to origial variable
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
