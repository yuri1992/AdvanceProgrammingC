//
// Created by yurir on 5/26/16.
//

#ifndef ADVANCEDPROGRAMING_Q1_H
#define ADVANCEDPROGRAMING_Q1_H

#include <stdio.h>
#include <string.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

char** readFile(char* fileName, int size);
void orderByLexicographicalOrder(char** arr, int size);
void swapChars(char **str1, char **str2);
void createFile(char* fileName, char** arr, int size);
void onlyLowerCase(char *string);
void printArray(char **arr, int size);

#endif //ADVANCEDPROGRAMING_Q1_H
