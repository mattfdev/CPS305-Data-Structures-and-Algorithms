#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
/*
 * CPS 305 Assignment 3
 * Created By Matthew Francis 
 * PLEASE COMPILE MY CODE TO THE c99 STANDARD
 */

//function that reads dictionary entries into trie line by line
void insertDict(TrieNode *trie){
    char line[buffer];
    FILE *fp;
    fp=fopen("/usr/courses/cps305/assign/assign3/american-english-no-accents","r");//modify for testing
    if(fp==NULL){
        exit(-1);
    }
    while(1){
        if(fgets(line,buffer,fp)==NULL) //if EOF stop reading from file
            break;
        insert(trie,line);
    }
    fclose(fp);
}

//autocomplete function implemented in complete.c as required by A3 instructions
//recieves user input, runs search to see if in trie, and traversal to print autocompleted words
void autocomplete(TrieNode *trie, char *lookup) {
    TrieNode *stub=search(trie,lookup);
    traversal(stub,lookup);
}

//main fuction that initilizes trie, receives user input, and runs the autocomplete function
int main(void){
    TrieNode *trie=initTrie();
    char word[buffer];
    insertDict(trie);
    while(1){
        printf("Enter a word to autocomplete\n");
        //reads user input into word unless CTRL-D is entered which will send EOF to fgets resulting in NULL therefore ending program
        if(fgets(word,buffer,stdin)== NULL)
            break;
        size_t length = strlen(word) - 1;
        if (word[length] == '\n')   //replaces troublesome /n from fgets with more appropriate /0 to indicate word end
            word[length] = '\0';
        autocomplete(trie,word);
    }

}
