#include <stdio.h>

int numberOfDigits(int num) {
    int digits = 0;
    while (num > 0) {
        digits++;
        num = num / 10;
    }
    return digits;
}

void printMultTable(int maxMult) {
    int i, y;
    int maxWidth;
    for (i = 1; i <= maxMult; i++) {
        for (y = 1; y <= maxMult; y++) {
            maxWidth = numberOfDigits(y * maxMult);
            if (maxMult == y)
                printf("%*d", maxWidth, y * i);
            else
                printf("%*d ", maxWidth, y * i);
        }
        printf("\n");
    }
}

int main() {
    int maxMult;
    printf("Please enter number:\n");
    scanf("%d", &maxMult);
    printMultTable(maxMult);
    return 0;
}