/*
 * CPS 305 Assignment 3
 * Created By Matthew Francis 
 * PLEASE COMPILE MY CODE TO THE c99 STANDARD
 * use gcc -o trie.c complete.c -std=c99  to compile
 * General Overview: Program autocompletes words from the dictionary using 
 * input from terminal utilising a trie data structure. Provide your own dictionary
 * and modify line 15 of complete.c for testing
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#define ASCII_apostrophe 58

//initalizes trie for use allocating memory and creating variables
TrieNode* initTrie(){
    TrieNode *trie =(TrieNode*)calloc(1,sizeof(TrieNode));
    for(int i=0;i<size;i++){
        trie->children[i]=NULL;
    }
    trie->terminal=0;
    trie->key=(char*)malloc(sizeof(char)*26);
    trie->key=NULL;
    return trie;
}

/* inserts string into trie in the appropriate spot
 * apostrophes are considered after all other chars because my indexing method results in a negative index for apostrophe
 * by putting them at the end memory usage reduced significantly(from 0to60 indexes instead of -26to60) */
void insert(TrieNode *initial, char *entry){
    TrieNode *current=initial;
    size_t length= strlen(entry);
    int index=0;
    for(int i=0;i<length;i++) {
        if(entry[i]=='\''){
            index=ASCII_apostrophe;
        }
        else if(entry[i]=='\n'){    //if end of word is reached mark the leaf as terminal, attach word and return to caller
            current->terminal=1;
            current->key =entry;
            return;
        }
        else{
            index= entry[i] -'A' ;  //create a sensible index by subtracting A (it is the first in ASCII table)
        }

        if(current->children[index]== NULL) //if there is no existing node at the index make a new one
            current->children[index]= initTrie();

        current= current->children[index]; //advance node to next letter
    }
}

//searches trie, checking if a string is present in the trie as a word or prefix
TrieNode* search(TrieNode *initial, char *lookup) {
    TrieNode *current=initial;
    size_t length = strlen(lookup);
    int index;
    for(int i=0;i < length;i++) {   //index calculated identically to insert
        if(lookup[i]=='\'')
            index=ASCII_apostrophe;
        else
            index= lookup[i]-'A';

        if(current->children[index] != NULL)   //if a leaf is found traverse to it
            current = current->children[index];
        else
            return NULL;    //if letter does not correspond to a subtree then the string is not in the dictionary
    }
        return current; //if the input has fully traversed the tree then it is part of the dictionary somehow
}

//traverses a tree for all possible words given a known present prefix
void traversal(TrieNode *stub,char *lookup){
    char storage[buffer];
    int nextLetter;
    if(stub==NULL)
        return;
    if(stub->terminal==1)
        printf("%s\n",lookup);

    for(int i=0;i<size;i++){
        if(i==ASCII_apostrophe)
            i=-26;  //when added to A gives the ASCII character '
        strcpy(storage,lookup);
        nextLetter='A'+i;   //calculate next letter of word, and add it to the string found already
        size_t length=strlen(storage);
        storage[length]=(char)nextLetter;
        storage[length+1]='\0';
        if(i==-26)
            i=ASCII_apostrophe;
        traversal(stub->children[i],storage);   //recursive call moving to subtree with calculated string
    }
}

