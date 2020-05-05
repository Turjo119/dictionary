// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <ctype.h>

#include <stdio.h>

#include <string.h>

#include <strings.h>

#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash word
    unsigned int i = hash(word);

    // Declare cursor
    node* cursor = table[i];

    while (cursor != NULL)
    {
        //Do something
        if(strcasecmp(word,cursor->word) == 0)
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
    // Dummy hash functuon
     if (isalpha(word[0]))
        {
            unsigned int hash_num;

            if(isupper(word[0]))
            {
                hash_num = word[0] - 65;

            }

            if(islower(word[0]))
            {
                hash_num = word[0] - 97;

            }
            return hash_num;
        }
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    // Open dictionary
    FILE* file_0 = fopen(dictionary, "r");
    if (file_0 == NULL)
    {
        return false;
    }

    // Create variable new_node
    node *new_node;

    // CHARACTER ARRAY FOR STORING WORDS READ FROM DICTIONARY.
    char WORD[LENGTH + 1];

    // Scan through files one word at a time until EOF is reached
    while (fscanf(file_0, "%s", WORD) == !EOF)
    {
        // Allocate space to new node REMEMBER TO FREE LATER
        new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        // Copy string from WORD to new_node
        strcpy(new_node->word, WORD);
        new_node->next = NULL;

        // Implement hash function
        unsigned int i = hash(new_node->word);

        // Point new_node's next to starting of link list
        new_node->next = table[i];

        // Point/Insert node to link list
        table[i] = new_node;

    }

    fclose(file_0);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Counter for total number of words
    unsigned int word_counter = 0;

    // For every bucket
    for (node *tmp = table[0]; tmp > table[N - 1]; tmp ++)
    {
      // Traverse through linked list NOTE THIS NEEDS SOME ADJUSTMENT
      for (node *trav = tmp; trav != NULL; trav = trav->next)
      {
          word_counter ++;
      }
    }
    return word_counter ++;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    // Declare cursor and tmp
    node* cursor;
    node* tmp;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
