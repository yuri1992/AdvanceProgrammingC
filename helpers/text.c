#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE_LEN 256
#define INIT_SIZE 1

typedef int BOOL;
#define FALSE 0
#define TRUE 1

int readText(char ***ptext);

char *findMaxLen(char **text, int size);

void myFree(char **text, int size);

int main() {
    char **text;
    int size;
    char *maxRow;
    printf("%p \n",text);
    printf("%p \n",&text);
    size = readText(&text);

    maxRow = findMaxLen(text, size);

    printf("The longest row is: \"%s\"\n", maxRow);

    myFree(text, size);

    return 0;
}

int readText(char ***ptext) {
    printf("%p \n",ptext);
    char **text;
    int logSize, phsSize;
    BOOL endOfInput;
    char line[MAXLINE_LEN + 1];

    text = (char **) malloc(INIT_SIZE * sizeof(char *));
    logSize = 0;
    phsSize = INIT_SIZE;
    endOfInput = FALSE;

    while (endOfInput == FALSE) {
        gets(line);
        if (line[0] == '\0')
            endOfInput = TRUE;
        else {
            if (logSize == phsSize) {
                phsSize *= 2;
                text = (char **) realloc(text, phsSize * sizeof(char *));
            }
            text[logSize] = strdup(line); //duplicates a string
            logSize++;
        }
    }

    if (logSize < phsSize)
        text = (char **) realloc(text, logSize * sizeof(char *));

    *ptext = text;
    return logSize;
}

char *findMaxLen(char **text, int size) {
    int max = 0, i;

    for (i = 1; i < size; i++)
        if (strlen(text[i]) > strlen(text[max]))
            max = i;

    return text[max];
}

void myFree(char **text, int size) {
    int i;

    for (i = 0; i < size; i++) {
        free(text[i]);
    }
    free(text);
}