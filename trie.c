#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "trie.h"




//print an error if malloc has a problem.
void mallocErr(void){
printf("Memory error has accord, exiting now\n");
exit(1);
}

//Crates a new node, and init all his parameters.
node* newNode(char letter){
node* n;
if (!(n=(node*)malloc(sizeof(node))))
mallocErr();

int i;
n->letter = letter;
n->count = 0;
n->isEndOfWord = NO;
n->hasChild = NO;
for (i=0; i<NUM_LETTERS; i++) {
(n->children)[i] = NULL;
}
return n;
}
//This method clear the memory of a node and his kids,
// if he got any.
void freeNode(node* n){
int i;
if (n==NULL) 
return;

if (NO==(n->hasChild)){
    free(n);
}
else {
for (i=0; i<NUM_LETTERS; i++) {
freeNode((n->children)[i]);
}
}
return;
}

//This method creates a new Trie, with reset parameters.
trie* newTrie(){
   trie* t;
 if(!(t = (trie*)malloc(sizeof(trie))))
       mallocErr();

      for(int i=0 ; i<NUM_LETTERS ; i++){
      t->children[i] = NULL;
   }
   t->curr = NULL;
   t->empty = YES;
   t->MaxWordLen = 0;

   return t;
}

//This method clears the memory of a Trie.
void freeTrie(trie* t){

   if(t == NULL) return;

   for(int i=0 ; i<NUM_LETTERS ; i++){
      freeNode(t->children[i]);
   }
   free(t);
}

//Checks if a root is empty.
boolean isEmpty(trie* root){
    return root->empty;
}

//Convert char type to an index number.
int charToIndex(char c){
return c-'a';
}

//This method checks if a letter is an end of a word and closing it.
void closeWord(trie* root){
if (root->curr == NULL)
return;
root->curr->count++;
root->curr->isEndOfWord = YES;
root->curr=NULL;
}

//Insert one char to the Trie.
int insertChar(trie* root, int c){
int index;
int word_length=0;
if(!isalpha(c)) {
closeWord(root);
return word_length;
}
word_length++;
c=tolower(c);
index= charToIndex(c);
if (root->curr==NULL) { 
if (root->children[index] == NULL)
root->children[index] = newNode(c);
root->curr = root->children[index];
root->empty=NO;
} 
else {
root->curr->hasChild = YES;
if (root->curr->children[index] == NULL)
root->curr->children[index] = newNode(c);
root->curr=root->curr->children[index];
}
return word_length;
}

//print an error if malloc has a problem.
void maloccErrWord(trie* root){
free(root->word);
if (!(root->word=(char*)malloc(1+sizeof(char)*(root->MaxWordLen))) )
mallocErr();
}

//Insert some text to the Trie.
trie* insertText(){
trie* root;
int c;
int word_length;
root = newTrie();
while((c=getchar()) != EOF){
word_length=insertChar(root,c);
if (word_length>root->MaxWordLen)
root->MaxWordLen=word_length;
}
maloccErrWord(root);
return root;
}

//Prints the words of a node.
void printWords(trie* root){
static int p=0;
int i;
node* curr;
root->word[p++]=root->curr->letter;
if (root->curr->isEndOfWord) {
root->word[p]='\0';
printf("%s\t%ld\n",root->word,root->curr->count);
}
if (root->curr->hasChild) {
for(i=0; i<NUM_LETTERS; ++i) {
if (root->curr->children[i] == NULL)
continue;
curr = root->curr; /* remember */
root->curr = root->curr->children[i];
printWords(root);
root->curr = curr; /* recall */
}
} else {
--p;
return;
}
--p;
}

//Print Tthe word in reverse order.
void printWordsReverse(trie* root){
static int p=0;
int i;
node* curr;
root->word[p++]=root->curr->letter;
if (root->curr->hasChild) {
for (i=NUM_LETTERS-1; i>=0; --i){
if (root->curr->children[i] == NULL)
continue;
curr = root->curr; 
root->curr = root->curr->children[i];
printWordsReverse(root);
root->curr = curr; 
}
} else {
if (root->curr->isEndOfWord){
root->word[p]='\0';
printf("%s\t%ld\n",root->word,root->curr->count);
}
--p;
return;
}
if (root->curr->isEndOfWord){
root->word[p]='\0';
printf("%s\t%ld\n",root->word,root->curr->count);
}
--p;
}

//Prints the whole Trie.
void printTrie(trie* root){
int i;
if (root == NULL)
return;
if (isEmpty(root))
return;
for (i=0; i<NUM_LETTERS; ++i){
if (root->children[i] == NULL)
continue;
root->curr = root->children[i];
printWords(root);
}
}

//Prints the whole Trie, in reverse order.
void printTrieReverse(trie* root){
int i;
if (root == NULL)
return;
if (isEmpty(root))
return;
for (i=NUM_LETTERS-1; i>=0; --i){
if (root->children[i] == NULL)
continue;
root->curr = root->children[i];
printWordsReverse(root);
}
}

