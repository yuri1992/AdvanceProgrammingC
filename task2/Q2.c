/*
 * Q2 - polygon summary and multiple
 * by Yuri Ritvin 316961101
 * MTA
 */
#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct monom {
    int coefficient;
    int power;
} Monom;

Monom *getPolynom(unsigned int *size);

void printPoly(Monom *monom1, unsigned int size);

void printPolyMul(Monom *polynom1, unsigned int size, Monom *polynom2, unsigned int size2);

void printPolySum(Monom *polynom1, unsigned int size, Monom *polynom2, unsigned int size2);

int findPowerIndex(Monom *monom1, int power, unsigned int size);

void orderPolynom(Monom *monom1, unsigned int size);

void swap(Monom *T1, Monom *T2);

int main() {
    // 2   4   7   3
    //-5   1   6   4
    Monom *polynom1, *polynom2;             // The input polynoms
    unsigned int polynom1Size, polynom2Size; // The size of each polynom

    printf("Please enter the first polynom:\n");
    polynom1 = getPolynom(&polynom1Size);   // get polynom 1

    printf("Please enter the second polynom:\n");
    polynom2 = getPolynom(&polynom2Size);   // get polynom 2

    printf("The multiplication of the polynoms is:\n"); // print the multiplication
    printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    printf("The sum of the polynoms is:\n"); // print the sum
    printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    free(polynom1); // releasing all memory allocations
    free(polynom2);
    return 0;
}

Monom *getPolynom(unsigned int *size) {
    /*
     * getPolynom
     * handle all process of get polynom form standard input form user
     * return point to array Monom and change in memory @*size
     */
    int coefficient;
    int power;
    int pyhSize = 2;
    int realSize = 0;
    Monom *polynom;
    polynom = malloc(sizeof(Monom) * pyhSize);
    BOOL endOfLine = FALSE;
    while (endOfLine == FALSE) {
        coefficient = 0;
        power = 0;
        scanf("%d %d", &coefficient, &power);
        if (coefficient != 0) {
            Monom tmp;
            int powerIndex = findPowerIndex(polynom, power, realSize);
            if (powerIndex != -1) {
                // power already exists in our trinom
                polynom[powerIndex].coefficient += coefficient;
            } else {
                // New place for Monom
                if (pyhSize == realSize) {
                    pyhSize *= 2;
                    polynom = realloc(polynom, sizeof(Monom) * pyhSize);
                }
                tmp.coefficient = coefficient;
                tmp.power = power;
                polynom[realSize++] = tmp;
            }
        }
        if (getchar() == '\n')
            endOfLine = TRUE;
    }
    *size = realSize;
    return polynom;
}

void swap(Monom *T1, Monom *T2) {
    /*
     * memory swap @*T1 and @*T2
     */
    Monom tmp;
    tmp = *T1;
    *T1 = *T2;
    *T2 = tmp;
}


void orderPolynom(Monom *monom1, unsigned int size) {
    /*
     * ordering *monom1 using bubblesort algo
     */
    BOOL swapped = TRUE;
    while (swapped == TRUE) {
        swapped = FALSE;
        for (unsigned int i = 0; i < size - 1; i++) {
            if (monom1[i + 1].power > monom1[i].power) {
                swap(&monom1[i], &monom1[i + 1]);
                swapped = TRUE;
            }
        }
    }
}

void printPoly(Monom *monom1, unsigned int size) {
    /*
     * printing @*monom1
     */
    for (unsigned int i = 0; i < size; i++) {
        int p = monom1[i].power;
        int co = monom1[i].coefficient;
        if (p > 1) {
            if (co > 0 && i == 0) {
                printf("%dx^%d ", co, p);
            } else {
                printf("%+dx^%d ", co, p);
            }
        } else if (p == 1) {
            printf("%dx", co);
        } else {
            printf("%+d", co);
        }
    }
}

void printPolyMul(Monom *polynom1, unsigned int size, Monom *polynom2, unsigned int size2) {
    /*
     * printPolyMul - multipli @*polynom1 and @*polynom2
     * @*polynom1 - pointer to array of Monom strcut
     * @*polynom2 - pointer to array of Monom strcut
     * @size - size of @polynom1
     * @size2 - size of @polynom2
     */
    int power = 0, coefficient = 0;
    int pyhSize = 2;
    int realSize = 0;
    Monom *polynom;
    polynom = malloc(sizeof(Monom) * pyhSize);
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int x = 0; x < size2; x++) {
            power = polynom1[i].power + polynom2[x].power;
            coefficient = polynom1[i].coefficient * polynom2[x].coefficient;
            int powerIndex = findPowerIndex(polynom, power, realSize);
            if (powerIndex != -1) {
                // power already exists in our trinom
                polynom[powerIndex].coefficient += coefficient;
            } else {
                Monom tmp;
                if (pyhSize == realSize) {
                    pyhSize *= 2;
                    polynom = realloc(polynom, sizeof(Monom) * pyhSize);
                }
                tmp.coefficient = coefficient;
                tmp.power = power;
                polynom[realSize++] = tmp;
            }
        }
    }
    orderPolynom(polynom, realSize);
    printPoly(polynom, realSize);

}

void printPolySum(Monom *polynom1, unsigned int size, Monom *polynom2, unsigned int size2) {
    /*
     * printPolySum - summarize @*polynom1 and @*polynom2 together
     * @*polynom1 - pointer to array of Monom strcut
     * @*polynom2 - pointer to array of Monom strcut
     * @size - size of @polynom1
     * @size2 - size of @polynom2
     */
    int power = 0, coefficient = 0;
    unsigned int pyhSize = 2;
    unsigned int realSize = 0;
    Monom *polynom;
    polynom = malloc(sizeof(Monom) * pyhSize);

    for (unsigned int i = 0; i < size; i++) {
        Monom tmp;
        if (pyhSize == realSize) {
            pyhSize *= 2;
            polynom = realloc(polynom, sizeof(Monom) * pyhSize);
        }
        tmp.coefficient = polynom1[i].coefficient;
        tmp.power = polynom1[i].power;
        polynom[realSize++] = tmp;
    }

    for (unsigned int i = 0; i < size2; i++) {
        int power = polynom2[i].power;
        int coefficient = polynom2[i].coefficient;
        int powerIndex = findPowerIndex(polynom, power, realSize);
        if (powerIndex != -1) {
            // power already exists in our trinom
            polynom[powerIndex].coefficient += coefficient;
        } else {
            Monom tmp;
            if (pyhSize == realSize) {
                pyhSize *= 2;
                polynom = realloc(polynom, sizeof(Monom) * pyhSize);
            }
            tmp.coefficient = coefficient;
            tmp.power = power;
            polynom[realSize++] = tmp;
        }
    }
    orderPolynom(polynom, realSize);
    printPoly(polynom, realSize);
}


int findPowerIndex(Monom *monom1, int power, unsigned int size) {
    /*
     * findPowerIndex - return the index of the power in @monom1
     * @*monom1 - pointer to Monom struct
     */
    for (unsigned int i = 0; i < size; i++) {
        if (monom1[i].power == power) {
            return i;
        }
    }
    return -1;
}