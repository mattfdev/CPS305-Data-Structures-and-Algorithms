/*
 * CPS 305 Assignment 3
 * Created By Matthew Francis
 * PLEASE COMPILE MY CODE TO THE c99 STANDARD
 */
#define size 60
#define buffer 25

//Trie ADT
typedef struct Node{
    char *key;
    int terminal;
    struct Node* children[size];
}TrieNode;

TrieNode* initTrie();
void insert(TrieNode *initial, char *entry);
TrieNode* search(TrieNode *initial, char *entry);
void traversal(TrieNode *stub,char *lookup);
