// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//  to keep track loaded words count
unsigned int numWordsLoaded = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to find the bucket index
    unsigned int index = hash(word);

    // Traverse the linked list in the bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare word (case-insensitive)
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true; // Word found in the dictionary
        }
        cursor = cursor->next;
    }

    return false; // Word not found
    // return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash += tolower(word[i]);
    }
    return hash % N;
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionally file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open dictionary file: %s\n", dictionary);
        return false;
    }
    // initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // buffer to store words
    char word[LENGTH + 1];

    // Read words from the dictionary and insert them into the hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for the word
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            return false;
        }

        // Copy the word into the new node
        strcpy(newNode->word, word);

        // Hash the word to get the bucket index
        unsigned int index = hash(word);

        // Insert the new node at the beginning of the linked list
        newNode->next = table[index];
        table[index] = newNode;

        // Increment the loaded_words count
        numWordsLoaded++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numWordsLoaded;
    // return num_words_loaded;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // free the memory
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
    // return false;
}
