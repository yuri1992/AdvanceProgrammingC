//
// Created by yurir on 5/27/16.
//

#ifndef ADVANCEDPROGRAMING_Q4A_H
#define ADVANCEDPROGRAMING_Q4A_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct student{
    char* name;
    int average;
    long offsetOrgFile;
} STUDENT;

typedef int BOOL;
#define FALSE 0
#define TRUE 1

STUDENT *readAndCreateIndFile(char *fileName, int *size);
void makeIndFile(char *fileName, STUDENT* stuList, int size);
void printStudent(STUDENT stu);
void readIndexesFile(char *fileName);
STUDENT* readStudentDetails(FILE* fp1) ;

void mergeSortStudents(STUDENT *stuList, int size);
void partition(STUDENT* stuList, int low, int high);
void mergeSort(STUDENT* stuList, int low, int mid, int high);


#endif //ADVANCEDPROGRAMING_Q4A_H
