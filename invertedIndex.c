#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#include "invertedIndex.h"

#define MAXCHAR 1000

//converting all characters to lowercase code from https:
//codeforwin.org/2015/04/c-program-convert-upper-case-string-to-lower.html
char *toLow(char *str);
// create new node
static InvertedIndexBST newNode (char *key);
// compare key of node1 and node2 recursively to put the node in the right place
void compareKeyRecur (InvertedIndexBST node1, InvertedIndexBST node2);
// code for strdup from // code from https://stackoverflow.com/questions/37132549/implementation-of-strdup-in-c-programming
char *myStrdup(const char *s1);

// int main () {
//     FILE *fp;
//     fp = fopen (collectionFilename, "r");
//     if (fp == NULL) {
//         printf("Could not open file %s",filename);
//         return 1;
//     }
//     while (fscanf(fp, "%s", str)!=EOF) {
//         fp = fopen (str, "r");
//         while (fscanf(fp, "%s", str) != NULL)
//         printf("%s\n", normaliseWord(str));
//         fclose(fp);
//     }
//     fclose(fp);
//     return 0;
// }

char *normaliseWord(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len+1; i++) {
        // check if str[i] is the 4 punc and is at the end of the word
        if ((str[i] == '.' || str[i] == ',' || str[i] == ';' || str[i] == '?')
        && i == len - 1) 
        {
            str[i] = ' ';
        }
    }
    return toLow(str);
}

//converting all characters to lowercase code from https:
//codeforwin.org/2015/04/c-program-convert-upper-case-string-to-lower.html
char *toLow(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
    return str;
}

void compareKeyRecur (InvertedIndexBST node1, InvertedIndexBST node2) {
    if (strcmp(node1->word, node2->word) < 0) {
        if (node1->right == NULL) {
            node1->right = node2;
        } else {
            compareKeyRecur (node1->right, node2);
        }
    } else if (strcmp(node1->word, node2->word) > 0) {
        if (node1->left == NULL) {
            node1->left = node2;
        } else {
            compareKeyRecur (node1->left, node2);
        }
    } else {
        return;
    }
}

static InvertedIndexBST newNode (char *key) {
    InvertedIndexBST node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->word = key;
    node->fileList = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// code from https://stackoverflow.com/questions/37132549/implementation-of-strdup-in-c-programming
char *myStrdup(const char *s1) {
  char *str;
  size_t size = strlen(s1) + 1;

  str = malloc(size);
  if (str) {
    memcpy(str, s1, size);
  }
  return str;
}


