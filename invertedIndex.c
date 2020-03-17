#include <stdio.h>
#include <string.h>
#include <ctype.h>
 
#include "invertedIndex.h"

#define MAXCHAR 1000

char *toLow(char *str);

int main () {
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "collection.txt";
    fp = fopen (filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fscanf(fp, "%s", str)!=EOF) {
        fp = fopen (str, "r");
        while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s\n", normaliseWord(str));
        fclose(fp);
    }
    fclose(fp);
    return 0;
}

char *normaliseWord(char *str) {
    int i = 0;
    int p = 0;
    int len = strlen(str);
    for (i = 0; i < len; i++) {
        if (!ispunct(str[i]) && !isspace(str[i])) {
            str[p] = tolower(str[i]);
            p++;
        }
    }
    for (i = p+1; i < len; i++) {
        str[i] = ' ';
    }
    return str;
}

// converting all characters to lowercase code from https://codeforwin.org/2015/04/c-program-convert-upper-case-string-to-lower.html
char *toLow(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] = str[i] + 32;
        }
    }
    return str;
}

// remove the following punctuation marks, if they appear at the end of a word
// char *removePunc(char *str) {
//     for (int i = 0; str[i] != '\0'; i++) {
//         if (ispunct(str[i])) {

//         }
//     }
// }
