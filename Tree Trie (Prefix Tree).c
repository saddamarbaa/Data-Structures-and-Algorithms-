/**
    [PROGRAM] : Trie(Prefix Tree) Data Structure Implementation
    [AUTHOR]  :  Saddam Arbaa
    [Email]   :  <saddamarbaas@gmail.com>

    C Program to Implement Trie data structure
     Tries is also known as A prefix tree.

     Reference in future :---->
     1. https://youtu.be/bxO-LIYQWqs
     2. https://youtu.be/7KQNGgk-Sik
     3. https://youtu.be/uhAUk63tLRM
     4. https://youtu.be/MC-iQHFdEDI
     5. https://youtu.be/sAErv97lfIM
     6. https://youtu.be/_rjW8w89ju8
     7. https://youtu.be/ks7rs5fqPws
     8. https://www.cs.usfca.edu/~galles/visualization/Trie.html*/

#include <stdio.h>
#include <stdlib.h>

/* Globally define ALPHABETS and initialization to 26 */
#define ALPHABETS 26

/*
  Globally declare constant Case and initialized to 'a'
  here Am working with lower case letters */
const int CASE = 'a';

/* A structure to represent TrieNode*/
typedef struct TrieNode
{
   /*
    parent filed
    pointer to the nodes parent node */
   struct TrieNode * parent;

    /*
     children filed
    (children is pointer to array of char) */
    struct TrieNode * children[ALPHABETS];

    /* Occurrences filed
    (Occurrences is how many time specific node is the last node in a word */
    int occurrences;

} TrieNode;

/*  Function to create new TrieNode */
TrieNode* getNewNode();

/* function to insert Word into Trie*/
void Insert_Node(TrieNode*, char*);

/* function to Remove Word from Trie*/
void removeWord(TrieNode*, char*);

/*  Function to search for word in Trie */
TrieNode* searchWord(TrieNode*, char*);

int main() /* the river Code */
{
    /* pointer to Head TrieNode */
    TrieNode * head = getNewNode();

     /* inserting words */
	Insert_Node(head, "hello");
	Insert_Node(head, "this trie");
    Insert_Node(head, "prefix tree");

    /* searching for words  */
    if(searchWord(head, "this trie"))
      printf("found\n");
    else printf("not found\n");
    if(searchWord(head, "trie"))
      printf("found\n");
    else printf("not found\n");

    /* removing words  */
    removeWord(head, "hello");
    removeWord(head, "helloo");

    /* searching for words again  */
    if(searchWord(head, "hello"))
      printf("found\n");
    else printf("not found\n");

    return 0;// signal to operating system everything works fine

}/** End of main function */


/**
    A utility function to create TrieNode
    Returns new TrieNode(initialized to NULLs) */

TrieNode* getNewNode()
{
    TrieNode* newNode; /* first create node */

    // allocate memory dynamically for node using malloc C function
    newNode = (TrieNode*) malloc(sizeof (TrieNode));
    if(newNode == NULL) /* Error handling */
       printf("Error in allocating memory\n");

    /* adding information to node */
    newNode -> parent = NULL;
    newNode -> occurrences = 0;
    /* iterate over the character array and initialized to null */
    for (int i = 0; i < ALPHABETS; i++)
		 newNode -> children [i] = NULL;

     return newNode;  // return newly created node to place where it been be called

} /** END of getNewNode() */


/** A utility function Function to insert word int Trie tree */

void Insert_Node(TrieNode* head, char* word)
{
    // local variable of type TrieNode declaration */
     TrieNode* currentNode = head;

    /*  iterate over the given word character by character */
     while(*word != '\0')
     {
         int index = *word - CASE; /* Calculate the current index */

         // create a new node if path doesn't exists
         if(currentNode -> children[index] == NULL)
         {
             currentNode -> children[index] = getNewNode(); // call getNewNode function to create new nod and added
             currentNode -> children[index] -> parent = currentNode; // update the  parent
         }
         currentNode = currentNode -> children[index];  // move currentNode to next node(next character)
         ++word; // increment word to move to next character
     }

    /* increment occurrences by one to indicate that this last character of word */
    ++currentNode -> occurrences;

    printf("\nWord has been inserted \n");  // inform user the element is been inserted

 } /** END of Insert_Node() */


/**
   Function to remove a word from trie tree
   Searches the word first, if not found, do nothing
   if found, then delete the word

    How do we delete a word
    1. search for the word in trie
    2. if the word exists , then we start at the ending node
    3. the first thing we do is decrement the occurrence of the node by 1
    Delete the node if
    1. has no children
    2. its occurrence is 0
    3. move to the parent node and repeat */

void removeWord(TrieNode* head, char* word)
{
    /* first step search for the word in Trie */
    TrieNode* currentNode = searchWord(head, word); // call searchWord function
    if (currentNode == NULL) /* cases when the word is not found */
    {
        printf("This word does not exist in Trie!!!\n");
        return ;//  we are done
    }
    /** deleting word process start from here */

    --currentNode -> occurrences;  // decrement currentNode -> occurrences by one

    // local variables
    TrieNode* parent = NULL;
    int isLeaf = 1; // flag variable

    // loop throw all the children
    for(int i = 0; i < ALPHABETS; i++)
    {
        if (currentNode -> children[i] != NULL) // check if the node has any children
        {
            isLeaf = 0;
            break;
        }
    }
    while(currentNode -> parent != NULL && isLeaf && currentNode -> occurrences == 0)
    {
        /* go from down to up until reach root node */
        parent = currentNode -> parent;
        for(int i = 0; i < ALPHABETS; i++)
        {
            if(parent -> children[i] == currentNode)
            {
                parent -> children[i] = NULL; // set parent null first
                free(currentNode);      // delete the currentNode
                currentNode = parent; // go one step up save in currentNode the address of parent
            }
            else if(parent -> children[i] != NULL) // parent have others children
            {
                isLeaf = 0;
                break;
            }
        }
    }
    printf("\nWord HAS been Removed \n"); // inform user the job is done

 } /** END of removeWord() */


/** Function to search for the given word  word in trie */

TrieNode* searchWord(TrieNode* head, char* word)
{
    // local variable of type TrieNode declaration */
    TrieNode* currentNode = head;

     /* iterate over the given word character by character */
     while(*word != '\0')
     {
         int index = *word - CASE; /* Calculate the current index */

         // as long as as we have node go ahead and search
         if(currentNode -> children[index] != NULL)
         {
             currentNode = currentNode -> children[index];  // move currentNode to next node(next character)
             ++word; // increment word to move to the next character
         }
         else  // word is not found just return null
           return NULL;
     }

     if(currentNode -> occurrences != 0)
        return currentNode;  // return the address of final node in current word

     return NULL;  // if reach this line return  null

 } /** END of searchWord() */
