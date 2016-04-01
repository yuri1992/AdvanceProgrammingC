/*
 * Q1_B
 * by Yuri Ritvin 316961101
 * MTA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void pointerSort(int *arr, unsigned int size, char ascend_flag, int*** arrPointers);
void partition(int **arr, int low, int high, char ascend_flag);
void mergeSort(int **arr, int low, int mid, int high, char ascend_flag);
void printPointers(int **arr, unsigned int size);

int main() {
    unsigned int size, i;
    int arr[SIZE];
    int **pointers;
    char ascend_flag;

    scanf("%u", &size);
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);
    getchar();
    scanf("%c", &ascend_flag);

    pointerSort(arr, size, ascend_flag, &pointers);
    printPointers(pointers, size);

    return 0;
}


void printPointers(int **arr, unsigned int size) {
    /*
     * printPointers - printing array of pointer
     */
    for (unsigned int i=0;i < size; i++ ){
        printf("%d ", *arr[i]);
    }
}

void pointerSort(int* arr, unsigned int size, char ascend_flag, int*** arrPointers) {
    /*
     * **pointerSort
     * @*arr - array of int to be sorted
     * @size -  size of arr
     * @ascend_flag - 1 for ascending order else descending
     *
     * printing array
     */
    *arrPointers = (int **) malloc(sizeof(int) * size);
    for (unsigned int i = 0; i < size; i++) {
        (*arrPointers)[i] = &arr[i];
    }
    partition(*arrPointers, 0, size-1, ascend_flag);
}

void partition(int **arr, int low, int high, char ascend_flag) {
    /*
     * partition
     * @**arr - pointer to array of pointers
     */
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        partition(arr, low, mid, ascend_flag);
        partition(arr, mid + 1, high, ascend_flag);
        mergeSort(arr, low, mid, high, ascend_flag);
    }
}

void mergeSort(int **arr, int low, int mid, int high, char ascend_flag) {
    /*
     * Implement of merge sort algorithm
     */
    int i, m, k, l, **temp[SIZE];

    l = low;
    i = low;
    m = mid + 1;

    while ((l <= mid) && (m <= high)) {
        if (ascend_flag == '1' && (*arr[l] <= *arr[m]))  {
            temp[i] = (int **) arr[l];
            l++;
        } else if (ascend_flag != '1' && (*arr[l] >= *arr[m])) {
            temp[i] = (int **) arr[l];
            l++;
        } else {
            temp[i] = (int **) arr[m];
            m++;
        }
        i++;
    }

    if (l > mid) {
        for (k = m; k <= high; k++) {
            temp[i] = (int **) arr[k];
            i++;
        }
    }
    else {
        for (k = l; k <= mid; k++) {
            temp[i] = (int **) arr[k];
            i++;
        }
    }

    for (k = low; k <= high; k++) {
        arr[k] = (int *) temp[k];
    }
}