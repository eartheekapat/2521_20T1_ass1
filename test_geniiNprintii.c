#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#include "test_normWord.c"
#include "invertedIndex.h"

#define MAXCHAR 1000

static InvertedIndexBST newInvertedIndexNode (char *key);
static FileList newFileListNode (char *filename);
void compareKeyRecur (InvertedIndexBST node1, InvertedIndexBST node2);
char *myStrdup(const char *s1);
InvertedIndexBST findKeyRecur (InvertedIndexBST node, char *str);
void printInvertedIndex(InvertedIndexBST tree); 
void loopThroughAllNodeRecur (InvertedIndexBST tree, FILE *fp);

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
    InvertedIndexBST head = newInvertedIndexNode("head");
    //printf("%s\n", head->word);
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
            InvertedIndexBST node = newInvertedIndexNode(normaliseWord(newstr2));
            if (head->right == NULL) {
                head->right = node;
            } else {
                compareKeyRecur (head->right, node);
            }       
        }
        fclose(fp2);
    }
    fclose(fp1);
    // loop to find node with key = mars and add fileList
    InvertedIndexBST curr = head->right;
    // printf("%lu", strlen(head->right->right->right->left->word));
    // printf("%s", head->right->right->right->left->word);
    curr = findKeyRecur(head->right, "japan");
    curr->fileList = newFileListNode("file21.txt");
    curr->fileList->next = newFileListNode("file32.txt");
    curr->fileList->next->next =newFileListNode("planet.txt");
    printInvertedIndex(head->right);
    return 0;
}

InvertedIndexBST findKeyRecur (InvertedIndexBST node, char *str) {
    printf("%s\n", node->word);
    printf("%lu\n", strlen(node->word));
    int cmp = strcmp(str, node->word);
    if (cmp == 0) {
        return node;
    } else if (cmp < 0) {
        return findKeyRecur (node->left, str);
    } else if (cmp > 0) {
        return findKeyRecur (node->right, str);
    }
    return NULL;
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

static InvertedIndexBST newInvertedIndexNode (char *key) {
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

static FileList newFileListNode (char *filename) {
    FileList node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    node->filename = filename;
    node->tf = 0; 
    node->next = NULL;
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

void printInvertedIndex(InvertedIndexBST tree) {
    FILE *fp;
    char Filename[MAXCHAR] = "invertedIndex.txt";
    fp = fopen (Filename, "w");
    loopThroughAllNodeRecur(tree, fp);
}

void loopThroughAllNodeRecur (InvertedIndexBST tree, FILE *fp) {
    if (tree == NULL) {
        return;
    }
    fprintf(fp, "%s ", tree->word);
    FileList curr = tree->fileList;
    while (curr != NULL) {
        fprintf(fp, "%s ", curr->filename);
        curr = curr->next;
    }
    fprintf(fp, "%c", '\n');
    if (tree->left == NULL && tree->right == NULL) {
        return;
    } else if (tree->left != NULL && tree->right == NULL) {
        loopThroughAllNodeRecur (tree->left, fp);
    } else if (tree->right != NULL && tree->left == NULL) {
        loopThroughAllNodeRecur (tree->right, fp);
    } else {
        loopThroughAllNodeRecur (tree->left, fp);
        loopThroughAllNodeRecur (tree->right, fp);
    }
}


