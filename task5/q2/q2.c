//
// Created by yurir on 5/27/16.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "q2.h"


STUDENT *readFile(char *fileName, int *size) {
    Employee ptr;
    FILE *fp1 = NULL;
    int stringLength;
    int realSize = 0, phySize=2;

    fp1 = fopen(fileName, "rb");
    assert(fp1 != NULL);

    Employee *employeeList = malloc(sizeof(Employee) * phySize);

    while(fread(&stringLength, sizeof(int), 1, fp1) > 0) {
        if (phySize == realSize) {
            phySize *=2;
            employeeList = realloc(employeeList, sizeof(employeeList) *  phySize);
        }
        //employeeList[realSize] = malloc(sizeof(Employee));
        ptr = employeeList[realSize];
        ptr.name = malloc(sizeof(char) * (stringLength + 1));
        fread(ptr.name, sizeof(char) , (size_t) stringLength, fp1);
        ptr.name[stringLength] =  '\0';
        ptr.name_length = stringLength;
        fread(&ptr.salary, sizeof(float) , 1 , fp1);
        employeeList[realSize] = ptr;
        realSize++;
    }
    fclose(fp1);

    parseEmployeesBonus(salaryBonusFile, employeeList, realSize);
    *size = realSize;
    return employeeList;
}

void parseEmployeesBonus(char *fileName, Employee *employeeList, int size) {
    float bonus = 0;
    int currentEmployee = 0;
    FILE *fp1 = NULL;

    fp1 = fopen(fileName, "rb");
    assert(fp1 != NULL);

    while(fread(&bonus, sizeof(float), 1, fp1) >0) {
        employeeList[currentEmployee].salary = employeeList[currentEmployee].salary + bonus;
        currentEmployee++;
    }
    fclose(fp1);
}

void printEmployee(Employee emp) {
    printf("Employee name : %s \n", emp.name);
    printf("Employee name length: %d \n", emp.name_length);
    printf("Employee salary : %f \n", emp.salary);
}

void sortEmployeesBySalary(Employee *employList, int size) {
    /*
     * sorting @employList By salary
     */
    BOOL swapped = TRUE;
    while (swapped == TRUE) {
        swapped = FALSE;
        for (int i=0; i< size-1; i++) {
            if (employList[i].salary < employList[i+1].salary) {
                swap(&employList[i], &employList[i+1]);
                swapped = TRUE;
            }
        }
    }
}

void swap(Employee *emp1, Employee *emp2) {
    Employee tmp = *emp1;
    *emp1 = *emp2;
    *emp2 = tmp;
}

void saveEmployeesFile(char *fileName, Employee *employeeList, int size) {
    FILE *fp1 = NULL;

    fp1 = fopen(fileName, "w+b");
    assert(fp1 != NULL);
    for (int i=0;i<size;i++) {
        // writing the length of the following string
        printEmployee(employeeList[i]);
        fwrite(&employeeList[i].name_length, sizeof(int), 1, fp1);
        fwrite(employeeList[i].name, sizeof(char), sizeof(char) * employeeList[i].name_length, fp1);
        fwrite(&employeeList[i].salary, sizeof(float), 1, fp1);
    }
    fclose(fp1);
}