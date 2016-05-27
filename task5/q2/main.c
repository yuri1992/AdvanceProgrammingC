//
// Created by yurir on 5/27/16.
//
#include "q2.c"

int main(int argc, char **argv) {

    Employee *employeeList;
    int size = 0;
    employeeList = parseEmployeesFromFile(argv[1],
                                          argv[2],
                                          &size);
    sortEmployeesBySalary(employeeList, size);
    saveEmployeesFile(argv[2], employeeList, size);

    printf("File Saved Succesfully");

    return 0;
}