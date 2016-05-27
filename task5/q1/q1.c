//
// Created by yurir on 5/26/16.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "q1.h"


char** readFile(char* fileName, int size) {
    /*
     * get @fileName and open the file, read the file by the define structure in the question
     */
    char** res = malloc(sizeof(char) * size);
    FILE *fp = NULL;
    int stringLength, realSize=0;
    fp  = fopen(fileName, "rb");
    assert(fp!= NULL);

    while(fread(&stringLength, sizeof(int), 1, fp) > 0) {
        res[realSize] = malloc(sizeof(char) * stringLength);
        fread(res[realSize], sizeof(char) ,sizeof(char) *stringLength, fp);
        onlyLowerCase(res[realSize]);
        realSize++;
    }

    fclose(fp);
    return res;
}

void onlyLowerCase(char *str) {
    /*
     * removing all non lower case char from @str
     */
    while(str[0] != '\0') {
        if (!(str[0] >= 'a' && str[0] <= 'z')) {
            char *p = str;
            while(str[0] != '\0') {
                str[0] = str[1];
                str++;
            }
            str = p;
        } else {
            str++;
        }
    }
    str = '\0';
}
void createFile(char* fileName, char** arr, int size) {
    /*
     * creating file with @filename+'.txt' name
     * inserting into the @arr by rows
     */
    FILE *fp = NULL;

    char *newFile = malloc(sizeof(char) * strlen(fileName) + sizeof(char) * 6);
    strcpy(newFile, fileName);
    strcat(newFile, ".txt");
    fp  = fopen(newFile, "w+");

    assert(fp!= NULL);
    for (int i=0; i< size; i++) {
        fprintf(fp, "%s \n", arr[i]);
    }
    fclose(fp);
}

void orderByLexicographicalOrder(char** arr, int size) {
    /*
     * Ordering @arr by Lexicographical Order
     * @size - array size
     */
    BOOL swapped = TRUE;

    while (swapped == TRUE) {
        swapped = FALSE;
        for (int i=0; i< size-1; i++) {
            if (strcmp(arr[i], arr[i+1]) < 0) {
                swapChars(&arr[i], &arr[i + 1]);
                swapped = TRUE;
            }
        }
    }

}
void printArray(char **arr, int size) {
    for (int i=0; i< size; i++) {
        printf("%s \n", arr[i]);
    }
}

void swapChars(char **str1, char **str2) {
    char *tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}