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

typedef struct listNode {
    int *dataPtr;
    struct listNode *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;


void makeEmptyList(List *pList);

void insertDataToEndList(List *pList, int ch);

void insertNodeToEndList(List *pList, ListNode *newNode);

void freeList(List *pList);

BOOL isEmptyList(List *lst);

ListNode *createNodeElement(int num, ListNode *next);

List merge(List lst1, List lst2);

List getList();

void printList(List *lst);

int main()
{

    List lst1, lst2, mergedList;

    lst1 = getList();
    lst2 = getList();

    mergedList = merge(lst1,lst2);

    printf("Merged list:\n");
    printList(&mergedList);

    freeList(&mergedList);
}

List getList() {
    List res;
    int size, num, i;

    makeEmptyList(&res);

    printf("Please enter the number of items to be entered:\n");
    scanf("%d", &size);

    printf("Please enter the numbers:\n");
    for (i = 0; i < size; i++) {
        scanf("%d", &num);
        insertDataToEndList(&res, num);
    }

    return res;

}

List merge(List lst1, List lst2) {
    List result;
    ListNode *currLst1, *currLst2;

    makeEmptyList(&result);
    currLst1 = lst1.head;
    currLst2 = lst2.head;

    while (currLst1 != NULL && currLst2!=NULL) {
        if (*(currLst1->dataPtr) > *(currLst2->dataPtr)) {
            insertNodeToEndList(&result,currLst1);
            currLst1 = currLst1->next;
        } else {
            insertNodeToEndList(&result,currLst2);
            currLst2 = currLst2->next;
        }
    }

    while (currLst1 != NULL) {
        insertNodeToEndList(&result,currLst1);
        currLst1 = currLst1->next;
    }

    while (currLst2 != NULL) {
        insertNodeToEndList(&result,currLst2);
        currLst2 = currLst2->next;
    }

    return result;
}


void printList(List *lst) {
    ListNode *curr;
    curr = lst->head;
    while (curr != NULL) {
        printf("%d ", *(curr->dataPtr));
        curr = curr->next;
    }
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


void makeEmptyList(List *pList) {
    pList->head = pList->tail = NULL;
}

BOOL isEmptyList(List *lst) {
    return (lst->head == NULL);
}

void freeList(List *lst) {
    ListNode *curr = lst->head, *saver;

    while (curr != NULL) {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
}

void insertDataToEndList(List *pList, int ch) {
    ListNode *lNode;
    lNode = createNodeElement(ch, NULL);
    insertNodeToEndList(pList, lNode);
}

ListNode *createNodeElement(int num, ListNode *next) {
    int *p;
    ListNode *pNode;
    p = (int *)malloc(sizeof(int));
    pNode = (ListNode *) malloc(sizeof(ListNode));
    *p = num;
    pNode->dataPtr = p;
    pNode->next = next;
    return pNode;
}