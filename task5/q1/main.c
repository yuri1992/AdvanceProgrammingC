//
// Created by yurir on 5/26/16.
//

#include <stdio.h>
#include <unistd.h>
#include "q1.h"

int main(int argc, char **argv) {
    /*
     * Question 1 - task 5 files and arguments
     *
     */

    int size;
    char **arr;

    size = atoi(argv[2]);
    arr = readFile(argv[1], size);
    orderByLexicographicalOrder(arr, size);
    printArray(arr, size);
    createFile(argv[1], arr, size);
    return 0;
}