// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int first_letter = hash(word);
    //node *checker = malloc(sizeof(node));
    node *checker = table[first_letter];
    while (checker != NULL)
    {
        if (strcasecmp(checker->word, word) ==0)
        {
            return true;
        }
        checker=checker->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO - load dictionary into a hash table
    //open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (dictionary==NULL)
    {
        return false;
    }
    char new_word[LENGTH+1];
    //read strings from file one at a time
    while (fscanf(file, "%s", new_word)!=EOF) //fscanf returns EOF at the end
    {
        //making a node, will make a series of nodes
        node *n = malloc(sizeof(node));
        //if we can't allocate more memory, free the node and exit
        if(n==NULL)
        {
            return false;
        }
        //copy the scanned word into the node
        strcpy(n->word, new_word);
        //add word to table based on first letter
        //check first letter of word ('a' = 97), dictionary is all lower
        int letter = hash(new_word);
        //temporary copy of hashtable
        n->next=table[letter];
        //add new word to hashtable letter linked-list
        table[letter]=n;
        dict_size++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //free the linked list, going through the hash table
    for (int i=0; i<N; i++)
    {
        while (table[i]!=NULL)
        {
            //store next in temp variable
            node *x = table[i]->next;
            free(table[i]);
            //replace from temp variable
            table[i]=x;
        }
    }
    return true;
}
