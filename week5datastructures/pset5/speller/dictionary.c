// Implements a dictionary's functionality

#include <stdbool.h>

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashval = hash(word);
    node* n = table[hashval];
    while(n != NULL)
    {
        if(strcasecmp(n->word, word) == 0)
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
    //  about hash == djb2 (k=33), first reported by dan bernstein
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char currentword[LENGTH + 1];
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    while(fscanf(dict, "%s", currentword) != EOF)
    {
        node* n = malloc(sizeof(node));
        if(n == NULL)
        {
        return false;
        }
        strcpy(n->word, currentword);
        int hashval = hash(currentword);
        n->next = table[hashval];
        table[hashval] = n;
        n = NULL;
        free(n);
        count += 1;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i;
    for(i=0; i<N; i++)
    {
        node* n = table[i];
        node* tmp = table[i];
        while(tmp != NULL)
        {
            n = n->next;
            free(tmp);
            tmp = n;
        }
    }
    return true;
}
