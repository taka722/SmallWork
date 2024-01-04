#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //variable for height from the user input.
    int height;
    //step1: checking the minimum and maximum height.
    do
    {
        printf("Height: ");
        scanf("%i", &height);

    }
    while (height < 1 || height > 8);
    //check the height (1 ~ 8)
    //printf("Height: %i\n", height);

    //step 2: space and #.

    for (int i = 0; i < height; i++)
    {
        //height == 3
        //     #      0  left space 2 == height - 1 height - i - 1
        //    ##      1  left space 1 == height - 2
        //   ###      2  left space 0 == height - 3

        //create the space for the left
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        //create left side pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //create space between two pyramid (2 spaces == ##)
        printf("  ");

        //create right side pyramid
        //ex.  height == 3
        //do not need space for the right side.
        //just increment the hashes by 1 for each lines.
        // #
        // ##
        // ###
        //i < height i++ 0, 1, 2
        //j, 0, 1, 2
        //j <= i
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //change lines.
        printf("\n");
    }
}