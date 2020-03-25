#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#include "test_normWord.c"
#include "invertedIndex.h"

#define MAXCHAR 1000

static InvertedIndexBST newNode (char *key);
void compareKeyRecur (InvertedIndexBST node1, InvertedIndexBST node2);
char *myStrdup(const char *s1);

int main () {
    FILE *fp1, *fp2;
    char collectionFilename[MAXCHAR] = "collection.txt";
    char str1[MAXCHAR], str2[MAXCHAR];
    fp1 = fopen (collectionFilename, "r");
    if (fp1 == NULL) {
        printf("Could not open file %s",collectionFilename);
        return 1;
    }
    // declare first to store the value of the first node
    InvertedIndexBST head = newNode("head");
    //printf("%s\n", head->word);
    InvertedIndexBST temp = newNode("temp");
    //printf("%s\n", temp->word);
    // InvertedIndexBST curr = newNode("current"); 
    while (fscanf(fp1, "%s", str1) != EOF) {
        char *newstr1 = myStrdup(str1);
        fp2 = fopen (str1, "r");
        if (fp2 == NULL) {
        printf("Could not open file %s", collectionFilename);
        return 1;
        }
        while (fscanf(fp2, "%s", str2) != EOF) { 
            char *newstr2 = myStrdup(str2);
            //printf("%s\n", normaliseWord(str2));
            // printf("%s\n", node->);
            InvertedIndexBST node = newNode(normaliseWord(newstr2));
            if (head->right == NULL) {
                head->right = node;
            } else {
                compareKeyRecur (head->right, node);
            }       
        }
        fclose(fp2);
    }
    fclose(fp1);
    InvertedIndexBST curr = head->right;
    return 0;
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

