#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
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
    size = readText(&text);
//    maxRow = findMaxLen(___________, ___________);
//    printf("The longest row is: \"%s\"\n", maxRow);
//    myFree(__________, __________);
    return 0;
}

int readText(char ***ptext) {
    char line[MAX_LINE_LEN];
    int row = 0;
    BOOL isEOF = FALSE;
    char **input = malloc(MAX_LINE_LEN * sizeof(char *));
    while (isEOF == FALSE) {
        gets(line);
        if (line[0] == '\0') {
            isEOF = TRUE;
        } else {
            input[row] = malloc(MAX_LINE_LEN);
            input[row] = strdup(line);
            row++;
        }
    }

    for (int y=0;y<row;y++) {
        printf("%s \n", input[y]);
    }
    return 0;
}

char *findMaxLen(char **text, int size) {

}

void myFree(char **text, int size) {

}