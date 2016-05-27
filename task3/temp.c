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

void freeList(List *pList);

void insertNodeToEndList(List *pList, ListNode *newNode);

BOOL isEmptyList(List *lst);

ListNode *createNodeElement(int num, ListNode *next);

List merge(List lst1, List lst2);

List getList();

void printList(List *lst);

int main() {

    List lst1, lst2, mergedList;

    lst1 = getList();
    lst2 = getList();

    mergedList = merge(lst1, lst2);

    printf("Merged list:\n");
    printList(&mergedList);

    freeList(&lst1);
    freeList(&lst2);
    freeList(&mergedList);
    return 0;
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

void insertDataToStartList(List *pList, int ch) {
    ListNode *lNode;
    lNode = createNodeElement(ch, NULL);
    insertNodeToEndList(pList, lNode);
}

List merge(List lst1, List lst2) {
    List result;
    ListNode *currLst1, *currLst2;

    makeEmptyList(&result);
    currLst1 = lst1.head;
    currLst2 = lst2.head;

    while (currLst1 != NULL && currLst2!=NULL) {
        if (*(currLst1->dataPtr) > *(currLst2->dataPtr)) {
            insertDataToEndList(&result, *(currLst1->dataPtr));
            currLst1 = currLst1->next;
        } else {
            insertDataToEndList(&result, *(currLst2->dataPtr));
            currLst2 = currLst2->next;
        }
    }

    while (currLst1 != NULL) {
        insertDataToEndList(&result, *(currLst1->dataPtr));
        currLst1 = currLst1->next;
    }

    while (currLst2 != NULL) {
        insertDataToEndList(&result, *(currLst2->dataPtr));
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

void insertDataToEndList(List *pList, int ch) {
    ListNode *lNode;
    lNode = createNodeElement(ch, NULL);
    insertNodeToEndList(pList, lNode);
}

void insertNodeToHead(List* pList, ListNode* newNode)
{
    newNode->next = pList->head;
    if (pList->tail == NULL)
        pList->tail = newNode;
    pList->head = newNode;
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