#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //input variable (initial population size from the user)
    int start;
    //the variale that store number of years we reach threshold
    int n = 0;
    //the variable for end size  (end > start)
    int end;

    // TODO: Prompt for start size
    do
    {
        printf("Start size: ");
        scanf("%i", &start);
    }
    while (start < 9);

    // TODO: Prompt for end size
    do
    {
        printf("End size: ");
        scanf("%i", &end);
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    while (start < end)
    {
        start = start + start / 3 - start / 4;
        n++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", n);

}
