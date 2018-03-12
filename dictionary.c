/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int noOfWords = 0;


/**
 * Returns true if word is in dictionary else false.
 */
 
void freenode(node* root)
{
    for(int i=0; i<27; i++)
    {   
        if(root->children[i] != NULL)
            freenode(root->children[i]);
    }
    free(root);
    
    return;
}

bool check(const char *word)
{
    node *currentNode = NULL;
    currentNode = root;
    int n=strlen(word);
    for(int i=0; i<n ;i++)
    {
        char ch = word[i];
        if(word[i] == '\'')
            ch = 'z' + 1;
            
        int childIndex = tolower(ch) - 'a';
            
        if(currentNode->children[childIndex] != NULL )
            currentNode = currentNode->children[childIndex];   
        else
            return false;
    }
    
    if(currentNode->is_word == true )
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{

    root = (node*)malloc(sizeof(node));
    if(root == NULL)
        return 1;
        
    node *currentNode;
    currentNode = (node*)malloc(sizeof(node));
    if(currentNode == NULL)
        return 1;
    
    FILE *fp = fopen(dictionary,"r");
    
    if (fp == NULL)
    {
        return false;
    }
    
    int location = 0;
    
    while((location = fgetc(fp) ) != EOF)
    {
        currentNode = root;
        
        for(;location != '\n'; location = fgetc(fp))
        {
            if(location == '\'')
                location = 'z' + 1;
            
            if(currentNode->children[location - 'a'] == NULL)
            {
                currentNode->children[location - 'a'] = (node*)malloc(sizeof(node));
                currentNode = currentNode->children[location - 'a'];
            }
            else
            {
                currentNode = currentNode->children[location - 'a'];
            }
            
        }
        currentNode->is_word = true;
        noOfWords++;
        
    }
    
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return noOfWords;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
   node* currentNode = root;
   freenode(currentNode);
   return true;
}
