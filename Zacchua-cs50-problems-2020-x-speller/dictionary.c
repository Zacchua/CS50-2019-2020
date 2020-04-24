// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char check[LENGTH + 1];
    strcpy(check, word);
    check[0] = tolower(check[0]);
    //hash word
    int i = hash(check);

    //set temp pointer to that linked list
    node *cursor = table[i];

    //traverse linked list to check
    while(cursor != NULL)
    {
        int j = strcasecmp(check, cursor->word);
        if(j == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char lower = tolower(word[0]);
    int i = lower - 'a';
    return i;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char *words = malloc(46 * sizeof(char));

    //open dictionary file
    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        printf("File does not exist/n");
        return false;
    }

    //scans words from dictionary into words
    for(int w = fscanf(file, "%s", words); w != EOF; w = fscanf(file, "%s", words))
    {
        //allocate space for a node
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }

        //copy word into node
        strcpy(n->word, words);

        //hash word
        int i = hash(words);

        //insert into hash table
        if(table[i] == NULL)
        {
            table[i] = n;
            table[i]->next = NULL;
        }

        else
        {
            n->next = table[i];
            table[i] = n;
        }
        //keep track of how many words
        count++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterate over each letter in the hash table
    for (int i = 0; i < N; i++)
    {
        //declare 2 temp pointers
        node *cursor = table[i];
        node *tmp = table [i];

        while(cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}
