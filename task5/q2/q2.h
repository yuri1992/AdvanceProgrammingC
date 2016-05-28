//
// Created by yurir on 5/27/16.
//

#ifndef ADVANCEDPROGRAMING_Q2_H
#define ADVANCEDPROGRAMING_Q2_H

#include "../q4/Q4A.h"

typedef struct employee
{
    int   name_length;
    char  *name;
    float  salary;
} Employee;

typedef int BOOL;
#define FALSE 0
#define TRUE 1

STUDENT *readFile(char *fileName, int *size);
void parseEmployeesBonus(char *fileName, Employee *employeeList, int size);
void sortEmployeesBySalary(Employee *employList, int size);
void saveEmployeesFile(char *fileName, Employee *employeeList, int size);
void printStudent(STUDENT stu);
void swap(Employee* emp1, Employee* emp2);

#endif //ADVANCEDPROGRAMING_Q2_H
