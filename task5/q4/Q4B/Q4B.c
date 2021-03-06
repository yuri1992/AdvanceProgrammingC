//
// Created by yurir on 5/27/16.
//

#include "Q4B.h"

STUDENT *readAndCreateIndFile(char *fileName, int *size) {
    /*
     * reading the @fileName and parsing to STUDENT array
     * setting @size to the size of the array
     * the array is sorted by ASC order using merge sort algo
     * return array of STUDENTS
     */
    STUDENT* stuList;
    FILE *fp1 = NULL;
    int n = 0;

    fp1 = fopen(fileName, "rb");
    assert(fp1 != NULL);

    // parsing number of lines to be parsed
    fread(&n, sizeof(short int), 1, fp1);
    stuList = malloc(sizeof(STUDENT) * n);

    for (int i=0;i<n;i++) {
        stuList[i] = *readStudentDetails(fp1);
    }
    fclose(fp1);

    mergeSortStudents(stuList, n);
    makeIndFile(fileName, stuList, n);

    *size = n;
    return stuList;
}


char **findAverageGrade(char *fileName, int avg, int *size) {
    /*
     * findAverageGrade - returning array of chars with names of students that have avg more then @avg
     * reading the .ind file from end to begging because of the ind file is sorted by ASC order
     * stop reading on first student that have avg less then @avg
     */
    FILE *studentFp = NULL, *indFp= NULL;
    char **arr = malloc(sizeof(char) * 2);
    char file[FILENAME_MAX];
    int offset = 0, pySize = 8;
    *size=0;

    strcpy(file, fileName);
    strcat(file, ".ind");
    indFp = fopen(file, "rb");
    assert(indFp != NULL);

    studentFp = fopen(fileName, "rb");
    assert(studentFp != NULL);

    fseek( indFp, 0, SEEK_END );
    fseek( indFp, -(sizeof(int)), SEEK_CUR );

    while( ftell( indFp ) >= 0 ) {
        // read all indexes from the end, the first lower grade and we can exit the read
        fread(&offset, sizeof(int), 1, indFp);

        fseek(studentFp, offset, SEEK_SET);
        STUDENT *student = readStudentDetails(studentFp);
        if ((*student).average >= avg) {
            if (*size == pySize) {
                pySize *= 2;
                arr = realloc(arr, sizeof(char) * pySize);
            }
            arr[*size] = malloc(sizeof(char) * strlen((*student).name));
            strcpy(arr[*size], (*student).name);
            (*size)++;
        } else {
            break;
        }
        free(student);

        fseek( indFp, -(sizeof(int) * 2), SEEK_CUR);
        if (ftell(indFp) - (sizeof(int) * 2)  < 0) {
            break;
        }
    }

    fclose(studentFp);

    if (*size == 0) {
        return NULL;
    }
    return arr;
}

void makeIndFile(char *fileName, STUDENT *stuList, int size) {
    /*
     * creating "ind" file that including the @offset of each student from the start of fileName.
     */
    FILE *fp1 = NULL;
    char file[FILENAME_MAX];
    strcpy(file, fileName);
    strcat(file, ".ind");
    fp1 = fopen(file, "rb");

    assert(fp1 != NULL);
    for (int i=0; i<size;i++) {
        fwrite(&stuList[i].offsetOrgFile, sizeof(int), 1, fp1);
    }
    fclose(fp1);
}

STUDENT* readStudentDetails(FILE* fp1) {
    /*
     * getting a *fp1 and parsing from him single student struct
     */
    int len;
    STUDENT* st1 = malloc(sizeof(STUDENT));
    st1->offsetOrgFile = ftell(fp1);
    fread(&len, sizeof(short int), 1, fp1);

    st1->name = malloc(sizeof(char) * (len + 1));
    fread(st1->name, sizeof(char), (size_t) len, fp1);
    st1->name[len] = '\0';

    fread(&st1->average, sizeof(int), 1, fp1);
    return st1;
}

void readIndexesFile(char *fileName) {
    /*
     *
     */
    FILE *fp1 = NULL;
    int n;

    fp1 = fopen(fileName, "rb");
    assert(fp1 != NULL);
    while(fread(&n, sizeof(int), 1, fp1) > 0 ) {
        printf("%d \t", n);
    }
    fclose(fp1);
}

void printStudent(STUDENT stu) {
    printf("Student name : %s \n", stu.name);
    printf("Student salary : %d \n", stu.average);
    printf("Student salary : %li \n", stu.offsetOrgFile);
}
//
void mergeSortStudents(STUDENT *stuList, int size) {
    /*
     */
    partition(stuList, 0, size-1);
}

void partition(STUDENT* stuList, int low, int high) {
    /*
     */
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        partition(stuList, low, mid);
        partition(stuList, mid + 1, high);
        mergeSort(stuList, low, mid, high);
    }
}

void mergeSort(STUDENT* stuList, int low, int mid, int high) {
    /*
     * Implement of merge sort algorithm
     */
    int i, m, k, l;
    STUDENT temp[high];

    l = low;
    i = 0;
    m = mid + 1;

    while ((l <= mid) && (m <= high)) {
        if (stuList[l].average <= stuList[m].average) {
            temp[i] = stuList[l];
            l++;
        } else {
            temp[i] = stuList[m];
            m++;
        }
        i++;
    }


    while (l <= mid)
        temp[i++] = stuList[l++];

    while (m <= high)
        temp[i++] = stuList[m++];

    for (k = low; k <= high; k++) {
        stuList[k] = temp[k];
    }

    i--;
    while (i >= 0) {
        stuList[low + i] = temp[i];
        i--;
    }

}