#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

#include <math.h>
#include <string.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);

int main(void)
{
    // The Coleman-Liau index of a text is designed to output that (U.S.) grade level that is needed to understand some text
    // index = 0.0588 * L - 0.296 * S - 15.8
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text

    // counting letters
    // counting words
    // counting sentences

    // output should be us reading level (grade)

    string text = get_string("Text: ");

    int letters = countLetters(text);
    int words = countWords(text);
    int sentences = countSentences(text);

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int countLetters(string text)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

int countWords(string text)
{
    int count = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int countSentences(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }
    return count;
}
