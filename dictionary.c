// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value
    int hash_val = hash(word);

    // Access linked list at that index in hash table
    node *n = table[hash_val];

    // Traverse linked list, looking for word (strcasecomp)
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Function should take a string and return an index
    // This hash function adds the ASCII values of all characters in the word together
    long sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;

    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictionary_pointer = fopen(dictionary, "r");

    // Check if null
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Initialise word array
    char nex_wor[LENGTH + 1];

    // Read strings from file one at a time
    while (fscanf(dictionary_pointer, "%s", nex_wor) != EOF)
    {
        // Create new node for each word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // copy word into node using strcopy
        strcpy(n->word, nex_wor);

        // Hash word to obtain hash value
        int hash_val = hash(nex_wor);

        // Insert node into hash table at that location
        n->next = table[hash_val];
        table[hash_val] = n;
        dictionary_size++;
    }

    // Close file
    fclose(dictionary_pointer);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over hash table and free nodes in each linked list
    for (int i = 0; i < N; i++)
    {
        // Assign cursor
        node *n = table[i];

        // Loop through linked list
        while (n != NULL)
        {
            // Make temp equal cursor;
            node *tmp = n;

            // Point cursor to next element
            n = n->next;

            // free temp
            free(tmp);
        }

        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }

    return false;
}
