#include <stdio.h>
#include "trie.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    trie *root;
    root = insertText();

    if (argc == 1)
    {
        printTrie(root);
    }
    else if (argc > 1 && *(argv[1]) == 'r')
    {
        printTrieReverse(root);
    }
    else
    {
        printf("bad input\n");
        exit(1);
    }
    freeTrie(root);
}
