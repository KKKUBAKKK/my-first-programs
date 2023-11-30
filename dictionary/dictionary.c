// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Variable to keep track of size
unsigned int *dictionary_size = NULL;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Set a node pointer to the right row in table, hash the word given to obtain the row
    node *n = table[hash(word)];

    // Loop until n == NULL
    while (n)
    {
        // STRCASECMP DOESN'T WORK FOR SOME REASON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // If the word is found return true
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        // Otherwise set n to n->next
        else
        {
            n = n->next;
        }
    }
    // If we got to the end of the row and didn't find the word return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int value = 0;
    unsigned int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        value += word[i] + length;
    }

    // Limit the value from 0 to N-1
    value = value % 1000;

    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open file and create buffer and temp
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        return false;
    }
    char buffer[LENGTH + 1] = "0";
    unsigned int temp;

    // Allocate memory for dictionary_size
    dictionary_size = (unsigned int *) malloc(sizeof(int));
    *dictionary_size = 0;

    // Read strings one by one into buffer, stop when buffer == EOF
    temp = fscanf(dict, "%s", buffer);
    while (temp != EOF)
    {
        // Allocate memory for new node and copy the buffer
        node *n = (node *) malloc(sizeof(node));
        if (!n)
        {
            fclose(dict);
            return false;
        }
        strcpy(n->word, buffer);
        n->next = NULL;

        // Run hash function on the word
        temp = hash(n->word);

        // Insert (prepend) node into the hash table at the right index
        n->next = table[temp];
        table[temp] = n;

        // Update dictionary_size
        (*dictionary_size)++;

        // Load next value to buffer
        temp = fscanf(dict, "%s", buffer);
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // If load function hasn't been called before return 0 (dictionary_size == NULL so we can't return it)
    if (!dictionary_size)
    {
        return 0;
    }

    // Return dictionary_size (equals 0 when load doesn't load any words)
    return *dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *temp, *cursor;

    // Loop for every row of the hash table
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the first node in the i row and loop until cursor == NULL
        cursor = table[i];
        while (cursor)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    free(dictionary_size);

    return true;
}
