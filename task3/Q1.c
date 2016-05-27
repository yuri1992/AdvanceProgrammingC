/*
 * Q1
 * by Yuri Ritvin 316961101
 * Task 3 - Linked List
 * MTA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct list_node {
    char *dataPtr;
    struct list_node *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;

} List;

typedef struct student {
    List first;
    int grade;
} Student;

Student unScramble(List lst);

void makeEmptyList(List *pList);

void insertDataToEndList(List *pList, char ch);

void printStudent(Student *pStudent);

void freeList(List *pList);

void insertNodeToEndList(List *pList, ListNode *newNode);

BOOL isEmptyList(List *lst);

ListNode *createNodeElement(char *ch, ListNode *next);


int main() {
    List lst;
    Student student;
    char ch;
    makeEmptyList(&lst);
    printf("Please enter the scrambled student:\n");
    ch = (char) getchar();
    while (ch != '\n') {
        insertDataToEndList(&lst, ch);
        ch = (char) getchar();
    }
    student = unScramble(lst);
    printStudent(&student);
    freeList(&student.first);
    return 0;
}

void printStudent(Student *pStudent) {
    printf("First name: ");
    ListNode *curr;
    curr = (pStudent->first).head;
    while (curr != NULL) {
        printf("%c", *(curr->dataPtr));
        curr = curr->next;
    }
    printf("\nGrade: %d", pStudent->grade);
}

Student unScramble(List lst) {
    Student res;
    int grade = 0;
    ListNode *curr, *prev;
    curr = lst.head;
    prev = NULL;
    while (curr != NULL) {
        if (isdigit(*(curr->dataPtr))) {
            grade = grade * 10 + atoi(curr->dataPtr);
            if (prev != NULL) {
                prev->next = curr->next;
            } else {
                lst.head = curr->next;
            }
            free(curr);
        }
        prev = curr;
        curr = curr->next;
    }
    res.grade = grade;
    res.first = lst;
    return res;
}

void insertDataToEndList(List *pList, char ch) {
    ListNode *lNode;
    char *c = malloc(sizeof(ch) + 1);
    c = strcpy(c, &ch);
    lNode = createNodeElement(c, NULL);
    insertNodeToEndList(pList, lNode);
}

void insertNodeToEndList(List *pList, ListNode *newNode) {
    if (isEmptyList(pList)) {
        pList->head = pList->tail = newNode;
    }
    else {
        pList->tail->next = newNode;
        pList->tail = newNode;
    }
}

ListNode *createNodeElement(char *ch, ListNode *next) {
    ListNode *pNode;
    pNode = (ListNode *) malloc(sizeof(ListNode));
    pNode->dataPtr = ch;
    pNode->next = next;
    return pNode;
}

void makeEmptyList(List *pList) {
    pList->head = pList->tail = NULL;
}

BOOL isEmptyList(List *lst) {
    return (lst->head == NULL);
}

void freeList(List* lst) {
    ListNode *curr = lst->head, *saver;

    while (curr != NULL) {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
}