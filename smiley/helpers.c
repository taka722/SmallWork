#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // check the pixcel is black
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0)
            {
                // change the color to the red
                image[i][j].rgbtRed = 255;
                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtGreen = 0;
            }
        }
    }
}
