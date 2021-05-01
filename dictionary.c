// Implements a dictionary's functionality

#include <stdbool.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include <strings.h>
#include<stdlib.h>

#include "dictionary.h"
#define N 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash table
node *table[N];

int word_count=0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int n = strlen(word);
    char word_copy[n];
    for(int i=0;i<n;i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    word_copy[n]='\0';
    int h = hash(word_copy);
    
    node *point = table[h];
    
    while(point!=NULL)
    {
        if(strcasecmp(point->word,word_copy)==0)
        {
            return true;
            unload();
        }
        else
        {
            point = point->next;
        }
    }
    return false;
}

// Hashes word to a number

//the djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
//Hashing will give the index so creating a linked list for diff. words

unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    int c = *word;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary,"r");
    if(f==NULL)
    {
        return false;
    }
    char word[LENGTH+1];
    while(fscanf(f,"%s",word)!=EOF)
    {
        node *newnode = malloc(sizeof(node));
        if(newnode == NULL)
        {
            unload();
            return false;
        }
        strcpy(newnode->word,word);
        
        int h = hash(newnode->word);
        
        node *head = table[h];
        
        newnode->next=table[h];
        table[h]=newnode;
        word_count++;
    }
    fclose(f);
    return true;
    
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
   return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor =NULL;
    for(int i=0;i<N;i++)
    {
        cursor = table[i];
        while(cursor)
        {
            node *temp = cursor;
            cursor=cursor->next;
            free(temp);
        }
        if(i==N-1 && cursor==NULL)
        {
            return true;
        }
    }
    return false;
}