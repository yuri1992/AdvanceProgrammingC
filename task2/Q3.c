/*
 * Q3  - Sudoko Solver
 * by Yuri Ritvin 316961101
 * MTA
 */

#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1
#define SUDOKO_SIZE 81
#define EMPTY_CELL -1

// values to mapp sudoko by rows/columns/box
static short rowValues[10][10] = {};
static short columnValues[10][10] = {};
static short boxValues[10][10] = {};

typedef struct _Array {
    short *arr;
    unsigned short size;
} Array;

Array ***PossibleDigits(short **sudokuBoard);

Array *getPossibleDigitsByIndex(unsigned int cellIndex, short **sudokuBoard);

unsigned int getRowByIndex(unsigned int cellIndex);

unsigned int getColByIndex(unsigned int cellIndex);

unsigned int getBoxByIndex(unsigned int cellIndex);

void mapSudoko(short **sudokuBoard);

int FillBoard(short **sudokuBoard, Array ***possibilities);

void sudokoPrintBoard(short **sudokuBoard);


int main() {
    short board[SUDOKO_SIZE] = {5, -1, 4, -1, 7, -1, -1, 1, -1, 6, -1, 2, 1, -1, -1, 3, -1, -1, 1, -1, 8, -1, 4, -1, -1,
                                6, -1,
                                -1, 5, -1, -1, 6, -1, -1, 2, -1, -1, 2, -1, 8, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, 4,
                                -1, 5,
                                6, -1, 6, 1, 5, 3, 7, 2, 8, 4, -1, 8, 7, -1, 1, 9, -1, 3, -1, -1, -1, -1, 2, 8, -1, -1,
                                -1, 9};
    short *sudoko_board = board;
    Array ***possible_solutions;

    printf("Initial board\n");
    sudokoPrintBoard(&sudoko_board);

    printf("Press enter to start playing...\n");
    getchar();

    possible_solutions = PossibleDigits(&sudoko_board);

    if (FillBoard(&sudoko_board, possible_solutions) == -1)
        printf("User's selections led to duplications\n");
    else {
        sudokoPrintBoard(&sudoko_board);
        printf("Board filled successfully\n");
    }
    return 0;
}

void mapSudoko(short **sudokuBoard) {
    /*
     * mapSudoko
     * mapping sudoko board by logic structure for better performance and more logic code
     * this function using static variables
     * Args:
     * @**sudokuBoard - short board[SUDOKO_SIZE]
     */
    unsigned short firstCellIndex = 0;

    for (unsigned short i = 0; i < 9; i++) {
        firstCellIndex = (unsigned short) (((i / 3) * 18) + i * 3);

        // mapping each row to array of indexes by number,
        // each index contains the number of occurs.
        // rowValues[rowIndex][cellValue(1-9)]
        for (unsigned short r = 0; r < 9; r++) {
            short indexCell = (short) (i * 9 + r);
            short cellValue = (*sudokuBoard)[indexCell];
            if (cellValue != EMPTY_CELL)
                rowValues[i][cellValue]++;
        }

        // mapping each column to array of indexes by number,
        // each index contains the number of occurs.
        // columnValues[columnIndex][cellValue(1-9)]
        for (unsigned short r = 0; r < 9; r++) {
            short indexCell = (short) (i + 9 * r);
            short cellValue = (*sudokuBoard)[indexCell];
            if (cellValue != EMPTY_CELL)
                columnValues[i][cellValue]++;
        }

        // mapping each box to array of indexes by number,
        // each index contains the number of occurs.
        // boxValues[boxIndex][cellValue(1-9)]
        for (unsigned short y = 0; y < 9; y++) {
            unsigned cellIndex = (unsigned int) (firstCellIndex + ((y / 3) * 9) + y % 3);
            short cellValue = (*sudokuBoard)[cellIndex];
            if (cellValue != EMPTY_CELL)
                boxValues[i][cellValue]++;
        }
    }
}

unsigned int getRowByIndex(unsigned int cellIndex) {
    /*
     * getRowByIndex - return the row of the cellIndex
     */
    return cellIndex / 9;
}

unsigned int getColByIndex(unsigned int cellIndex) {
    /*
     * getColByIndex - return the column of the cellIndex
     */
    return cellIndex % 9;
}

unsigned int getBoxByIndex(unsigned int cellIndex) {
    /*
     * getBoxByIndex - return the box of the cellIndex
     */
    return (cellIndex / 27) * 3 + (cellIndex % 9) / 3;
}

Array *getPossibleDigitsByIndex(unsigned int cellIndex, short **sudokuBoard) {
    /*
     *  getPossibleDigitsByIndex
     *  @cellIndex - unsigned int represent value inedx in sudoku grid
     *
     *  return - all possible digits you can enter to the specific cell
     */
    short cellValue = (*sudokuBoard)[cellIndex];

    // Allocating memory in HEAP for ptr
    Array *ptr;
    ptr = malloc(sizeof(Array));

    // initialize ptr with null values
    ptr->arr = NULL;
    ptr->size = 0;

    if (cellValue == EMPTY_CELL) {
        unsigned short realSize = 0;
        unsigned short pyhSize = 2;

        // allocating memory
        short *possValues = malloc(sizeof(short) * pyhSize);

        unsigned rowIndex = getRowByIndex(cellIndex);
        unsigned columnIndex = getColByIndex(cellIndex);
        unsigned boxIndex = getBoxByIndex(cellIndex);

        // iterate over all possiable values 1-9,
        // checking if number not occur in row, column and box
        for (unsigned short x = 1; x < 10; x++) {
            if (boxValues[boxIndex][x] == 0 &&
                rowValues[rowIndex][x] == 0 &&
                columnValues[columnIndex][x] == 0) {

                // allocating more memory
                if (pyhSize == realSize) {
                    pyhSize *= 2;
                    possValues = realloc(possValues, sizeof(short) * pyhSize);
                }
                // inserting value that didnt occur in row,column and box
                possValues[realSize++] = x;
            }
        }

        ptr->arr = possValues;
        ptr->size = realSize;
    }
    return ptr;
}

Array ***PossibleDigits(short **sudokuBoard) {
    unsigned short realSizeArray = 0;
    mapSudoko(sudokuBoard);
    Array ***res = malloc(1);
    *res = (Array **) malloc(sizeof(Array) * SUDOKO_SIZE);
    for (unsigned short cellIndex = 0; cellIndex < SUDOKO_SIZE; cellIndex++) {
        (*res)[realSizeArray++] = getPossibleDigitsByIndex(cellIndex, sudokuBoard);
    }
    return res;
}

int sudokoSolved(short **sudokuBoard) {
    unsigned short firstCellIndex = 0;

    for (unsigned short i = 0; i < 9; i++) {
        firstCellIndex = (unsigned short) (((i / 3) * 18) + i * 3);

        BOOL duplication = FALSE;
        for (unsigned short x = 1; x < 10; x++) {
            BOOL isFound = FALSE;
            // iterate over rows verifying no duplication are occur
            for (unsigned short r = 0; r < 9; r++) {
                short indexCell = (short) (i + 9 * r);
                short cellValue = (*sudokuBoard)[indexCell];

                if (isFound == TRUE && cellValue == x) {
                    duplication = TRUE;
                }

                if (cellValue == x) {
                    isFound = TRUE;
                }
            }

            if (duplication == TRUE)
                return -1;
        }

        duplication = FALSE;
        for (unsigned short x = 1; x < 10; x++) {
            BOOL isFound = FALSE;
            // iterate over columns verifing no duplication are occur
            for (unsigned short y = 0; y < 9; y++) {
                unsigned cellIndex = (unsigned int) (firstCellIndex + ((y / 3) * 9) + y % 3);
                short cellValue = (*sudokuBoard)[cellIndex];

                if (isFound == TRUE && cellValue == x) {
                    duplication = TRUE;
                }

                if (cellValue == x) {
                    isFound = TRUE;
                }
            }

            if (duplication == TRUE)
                return -1;
        }
    }
    return 0;
}


int FillBoard(short **sudokuBoard, Array ***possibilities) {
    /*
     * FillBoard
     * @ **sudokoBoard - pointer to sudoko grid
     * @ ***possibilities - pointer to Array pointer of possibilities for each cell
     */

    BOOL isSolved = FALSE;
    BOOL isAutomaticChoose;
    Array *poss;
    while (isSolved == FALSE) {
        isSolved = TRUE;
        isAutomaticChoose = FALSE;
        unsigned short minPossibilities = 10;
        unsigned short minIndex = 0;

        // iterate over all empty cells and checking
        // if there only one option could be insert to this cell
        for (unsigned short cellIndex = 0; cellIndex < SUDOKO_SIZE; cellIndex++) {
            short cellValue = (*sudokuBoard)[cellIndex];
            if (cellValue == EMPTY_CELL) {
                isSolved = FALSE;
                poss = (*possibilities)[cellIndex];
                if (poss->size == 1) {
                    // Cell have only one option to this cell, lets insert it
                    isAutomaticChoose = TRUE;
                    poss->size = 0;
                    (*sudokuBoard)[cellIndex] = poss->arr[0];
                } else if (poss->size == 0) {
                    // empty field have no option, this mean that we couldn't solve the soduko
                    return -1;
                } else if (poss->size > 0 && poss->size < minPossibilities) {
                    // mark the Cell with minimum possibilities
                    minPossibilities = poss->size;
                    minIndex = cellIndex;
                }
            }
        }


        // requireUserInput(int minIndex);
        if (isAutomaticChoose == FALSE && isSolved == FALSE) {
            // Using user input to continue sudoko solving
            unsigned rowIndex = getRowByIndex(minIndex);
            unsigned columnIndex = getColByIndex(minIndex);
            short input;
            poss = (*possibilities)[minIndex];
            sudokoPrintBoard(sudokuBoard);

            printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n",
                   rowIndex, columnIndex);
            for (unsigned short i = 0; i < poss->size; i++) {
                printf("%d.%*d\n", i + 1, 2, poss->arr[i]);
            }
            scanf("%hi", &input);
            printf("Updating cell %d with value %d \n", minIndex, input);

            // updating sudoko board with user input
            poss->size = 0;
            poss->arr = NULL;
            (*sudokuBoard)[minIndex] = input;
        }

        // Validating that the board isn't
        // get vaiolated by two same values in same row or column
        int sudokoStatus = sudokoSolved(sudokuBoard);
        if (sudokoStatus == -1) {
            return -1;
        }

        // recalculating the Possible Values for the new sudoko grid
        possibilities = PossibleDigits(sudokuBoard);
    }
    return 0;
}

void sudokoPrintBoard(short **sudokuBoard) {
    /*
     * sudokoPrintBoard  - printing the sudoko board
     */
    printf("\n\n");
    printf("  ");
    for (unsigned int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printf("|");
        }
        printf("%*d", 2, i);
    }
    for (unsigned int i = 0; i < SUDOKO_SIZE; i++) {
        if (i % 9 == 0) {
            if (i % 27 == 0) {
                printf("\n-----------------------");
            }

            printf("\n %d", i / 9);

        }
        if (i % 3 == 0) {
            printf("|");
        }

        short cellValue = (*sudokuBoard)[i];

        if (cellValue == EMPTY_CELL) {
            printf("  ");
        } else {
            printf("%*d", 2, cellValue);
        }
    }
    printf("\n-----------------------");
    printf("\n\n\n");
}

