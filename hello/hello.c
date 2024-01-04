#include <stdio.h>
#include <cs50.h>
int main(void)
{
    //get user input (name)
    string name = get_string("What is your name? ");

    //print out the result
    printf("hello, %s\n", name);
}
