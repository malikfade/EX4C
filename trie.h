#define NUM_LETTERS ((int)26)

#ifndef Node
#define Node


typedef enum {NO=0, YES=1} boolean; 

typedef struct node{ 
  
   char letter; 
   long unsigned int count; 
   struct node* children[NUM_LETTERS];
   boolean isEndOfWord;
   boolean hasChild;
   
} node; 
#endif

#ifndef Trie
#define Trie
typedef struct trie{
   
   node* children[NUM_LETTERS];
   node* curr;
   char* word;
   int MaxWordLen;
   boolean empty;

} trie;
#endif

//used in main
void freeTrie(trie* t);
trie* insertText();
void printTrie(trie* root);
void printTrieReverse(trie* root);

//used in functions
void mallocErr(void);
void maloccErrWord(trie* root);
node* newNode(char ch);
void freeNode(node* n);
trie* newTrie();
int charToIndex(char c);
void closeWord(trie* root);
boolean isEmpty(trie* root);
int insertChar(trie* root, int c);
void printWords(trie* root);
void printWordsReverse(trie* root);



