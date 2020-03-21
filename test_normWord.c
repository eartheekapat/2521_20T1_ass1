#include <stdio.h>
#include <string.h>
#include <ctype.h>

// #include "invertedIndex.h"
// #include "invertedIndex.c"

char *normaliseWord(char *str);
char *toLow(char *str);

// int main () {
//     char text[20] = "Sydney!";

//     printf("%s\n", normaliseWord(text));
//     //printf("%c\n", text[3]);

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
