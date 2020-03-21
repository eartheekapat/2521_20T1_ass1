#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#include "invertedIndex.h"
#include "test_normWord.c"

#define MAXCHAR 1000

char *toLow(char *str);

int main () {
    FILE *fp;
    char collectionFilename[MAXCHAR] = "collection.txt";
    char str[MAXCHAR];
    fp = fopen (collectionFilename, "r");
    if (fp == NULL) {
        printf("Could not open file %s",collectionFilename);
        return 1;
    }
    
    while (fscanf(fp, "%s", str) != EOF) {
        printf("%s\n", str);
        fp = fopen (str, "r");
        while (fscanf(fp, "%s", str) != EOF) {
            printf("%s\n", normaliseWord(str));
            fclose(fp);
        }
    }
    fclose(fp);
    return 0;
}
