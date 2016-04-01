//
// Created by yurir on 3/6/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARAMS 50
#define MAX_OUTPUT 256

int formatBinary(int num) {
    /*
     * formatBinary - return an binary represent of @num
     * @num - positive value integer
     */
    int i = 1, binary = 0;
    while (num != 0) {
        binary += (num % 2) * i;
        num /= 2;
        i *= 10;
    }
    return binary;
}

char *romanChars(int num) {
    /*
     * return an roman Digit representing the num.
     * @str - pointer
     */
    char *str = (char *) malloc(MAX_PARAMS * sizeof(char));
    int tempNum = num;
    while (tempNum > 0) {
        char chPrint;
        int chValue = 0;
        if (tempNum - 1000 >= 0) {
            chPrint = 'M';
            chValue = 1000;
        } else if (tempNum - 500 >= 0) {
            chPrint = 'D';
            chValue = 500;
        } else if (tempNum - 100 >= 0) {
            chPrint = 'C';
            chValue = 100;
        } else if (tempNum - 50 >= 0) {
            chPrint = 'L';
            chValue = 50;
        } else if (tempNum - 10 >= 0) {
            chPrint = 'X';
            chValue = 10;
        } else if (tempNum - 9 == 0) {
            chPrint = 'I';
            chValue = 0;
            tempNum = 10;
        } else if (tempNum - 5 >= 0) {
            chPrint = 'V';
            chValue = 5;
        } else if (tempNum - 4 == 0) {
            chPrint = 'I';
            chValue = 0;
            tempNum = 5;
        } else {
            chPrint = 'I';
            chValue = 1;
        }
        tempNum = tempNum - chValue;
        strncat(str, &chPrint, 1);
    }
    return str;
}

int getArgsList(char *numbers, int args[]) {
    /*
     * Convert @numbers string to separate numbers array
     * @numbers - string of number separate by " "(whitespace)
     * @args - pointer to int array to be filled
     *
     * return - function return the real size of the array
     */
    int i = 0;
    char *token;

    token = strtok(numbers, " ");
    while (token != NULL) {
        args[i++] = atoi(token);
        token = strtok(NULL, " ");
    }

    free(token);
    return i;
}

void printFormattedIntegers(char *format, char *numbers) {
    char *pos;
    char output[MAX_OUTPUT] = "";

    int args[MAX_PARAMS];
    int i = 0;
    int j = 0;
    int bin = 0;

    getArgsList(numbers, args);
    pos = strstr(format, "%");

    while (pos != NULL) {
        char str[100] = "";
        // lets copy all chars until % sign
        strncat(output, format, pos - format);
        if (pos[1] == 'b') {
            // if binary output required we will use formatBinary helper
            bin = formatBinary(args[i++]);
            j = sprintf(str, "%d", bin);
            strncat(output, str, j);
        } else if (pos[1] == 'r') {
            // if roman numeric output required we will use rommanChars helper
            strcat(output, romanChars(args[i++]));
        } else {
            // not special format is required we will use sprinf function
            char formatToPrint[3] = "";
            // lets set formatToPrint
            strncpy(formatToPrint, pos, 2);

            j = sprintf(str, formatToPrint, args[i++]);
            strncat(output, str, j);
        }

        // we will move the pointer to memory cells to right (to skip %X)
        pos += 2;
        // will assign this pointer to @format
        format = pos;

        // make strstr search for the nex %
        pos = strstr(pos, "%");
    }
    strncat(output, format, strlen(format));
    printf("%s", output);
    free(pos);
}

int main() {
    char format[100];
    char numbers[100];

    gets(format);
    gets(numbers);
    printFormattedIntegers(format, numbers);

    return 0;
}
