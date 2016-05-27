/*
 * Q3_A.c
 * by Yuri Ritvin 316961101
 * Task 3 - Linked List
 * MTA
 */
#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct XlistNode {
    int *dataPtr;
    struct Ylist *yCordList;
    struct XlistNode *next;
} XListNode;

typedef struct YlistNode {
    int *dataPtr;
    struct YlistNode *next;
} YListNode;

typedef struct Ylist {
    YListNode *head;
    YListNode *tail;
} YList;

typedef struct list {
    XListNode *head;
    XListNode *tail;
} List;


/*
 * Utils Function definition both for List and YList struct
 *
 */

void makeEmptyXList(List *pList);

void makeEmptyYList(YList *pList);

XListNode *createXListNodeElement(int num, XListNode *next);

YListNode *createYListNodeElement(int num, YListNode *next);

void insertDataToEndXList(List *pList, int ch);

void insertDataToEndYList(YList *pList, int ch);

void insertNodeToEndXList(List *pList, XListNode *newNode);

void insertNodeToEndYList(YList *pList, YListNode *newNode);

void freeXList(List *pList);

void freeYList(YList *pList);

BOOL isEmptyXList(List *lst);

BOOL isEmptyYList(YList *lst);

/*
 * End of utils function definition
 */

/*
 * start of question function definition
*/
List getCoordList();

unsigned int getPairOccurrences(List coord_list, int x, int y);

int main() {

    List coordList;

    int x, y;
    unsigned int res;

// The user will enter the number of points followed by the points.
// The pointes will be entered in a sorted fashion.
// i.e. first by the x value and then by y.
// for example (5 points): 5 1 2 1 5 2 7 3 3 3 8
// are: (1,2),(1,5),(2,7),(3,3),(3,8)
    coordList = getCoordList();

// get the (x,y) to look for
    scanf("%d%d", &x, &y);

    res = getPairOccurrences(coordList, x, y);

    printf("The point (%d,%d) appears %u times\n", x, y, res);

    freeXList(&coordList);
    return 0;
}

List getCoordList() {
    /*
     * getCoordList - handle of user coordinates input
     */
    List res;
    XListNode *currXNode = NULL;
    int size, i, lastXValue = 0;

    makeEmptyXList(&res);
    scanf("%d", &size);

    for (i = 0; i < size; i++) {
        int x,y;
        scanf("%d", &x);
        scanf("%d", &y);
        // the input is sorted, we take advantage of this
        // we will create new X node on different x value
        if (x != lastXValue) {
            insertNodeToEndXList(&res, currXNode);
            currXNode = createXListNodeElement(x, NULL);
        }
        insertDataToEndYList(currXNode->yCordList, y);
        lastXValue = x;
    }
    insertNodeToEndXList(&res, currXNode);
    return res;
}

unsigned int getPairOccurrences(List coord_list, int x, int y) {
    XListNode *curr;
    unsigned int num = 0;
    curr = coord_list.head;
    while (curr != NULL) {
        // found X coordinate lets search for Y.
        if (*(curr->dataPtr) == x) {
            YListNode *currY;
            currY = curr->yCordList->head;
            while (currY != NULL) {
                if (*(currY->dataPtr) == y)
                    num++;
                currY = currY->next;
            }
            // no point to continue search for x values
            return num;
        }
        curr = curr->next;
    }
    return num;
}

/*
 * Start of Implementation of Linked List utils functions
 */

void printList(List *lst) {
    XListNode *curr;
    curr = lst->head;
    while (curr != NULL) {
        printf("%d ", *(curr->dataPtr));
        curr = curr->next;
    }
}

void freeXList(List *lst) {
    XListNode *curr = lst->head, *saver;

    while (curr != NULL) {
        saver = curr->next;
        freeYList(curr->yCordList);
        free(curr->dataPtr);
        free(curr);
        curr = saver;
    }
}


void freeYList(YList *lst) {
    YListNode *curr = lst->head, *saver;

    while (curr != NULL) {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
}

void insertDataToStartYList(YList *pList, int ch) {
    YListNode *lNode;
    lNode = createYListNodeElement(ch, NULL);
    insertNodeToEndYList(pList, lNode);
}

void insertDataToStartXList(List *pList, int ch) {
    XListNode *lNode;
    lNode = createXListNodeElement(ch, NULL);
    insertNodeToEndXList(pList, lNode);
}

void insertDataToEndXList(List *pList, int ch) {
    XListNode *lNode;
    lNode = createXListNodeElement(ch, NULL);
    insertNodeToEndXList(pList, lNode);
}

void insertDataToEndYList(YList *pList, int ch) {
    YListNode *lNode;
    lNode = createYListNodeElement(ch, NULL);
    insertNodeToEndYList(pList, lNode);
}

void insertXNodeToHead(List *pList, XListNode *newNode) {
    newNode->next = pList->head;
    if (pList->tail == NULL)
        pList->tail = newNode;
    pList->head = newNode;
}

void insertYNodeToHead(YList *pList, YListNode *newNode) {
    newNode->next = pList->head;
    if (pList->tail == NULL)
        pList->tail = newNode;
    pList->head = newNode;
}


void insertNodeToEndXList(List *pList, XListNode *newNode) {
    if (isEmptyXList(pList)) {
        pList->head = pList->tail = newNode;
    }
    else {
        pList->tail->next = newNode;
        pList->tail = newNode;
    }
}

void insertNodeToEndYList(YList *pList, YListNode *newNode) {
    if (isEmptyYList(pList)) {
        pList->head = pList->tail = newNode;
    }
    else {
        pList->tail->next = newNode;
        pList->tail = newNode;
    }
}


XListNode *createXListNodeElement(int num, XListNode *next) {
    XListNode *pNode;
    YList *ycordinates;

    ycordinates = (YList *) malloc(sizeof(YList));
    pNode = (XListNode *) malloc(sizeof(XListNode));

    pNode->dataPtr = (int *) malloc(sizeof(int));
    *(pNode->dataPtr) = num;
    pNode->next = next;
    makeEmptyYList(ycordinates);
    pNode->yCordList = ycordinates;
    return pNode;
}

YListNode *createYListNodeElement(int num, YListNode *next) {
    YListNode *pNode;
    pNode = (YListNode *) malloc(sizeof(XListNode));
    pNode->dataPtr = (int *) malloc(sizeof(int));
    *(pNode->dataPtr) = num;
    pNode->next = next;
    return pNode;
}

void makeEmptyXList(List *pList) {
    pList->head = pList->tail = NULL;
}

void makeEmptyYList(YList *pList) {
    pList->head = pList->tail = NULL;
}

BOOL isEmptyXList(List *lst) {
    return (lst->head == NULL);
}

BOOL isEmptyYList(YList *lst) {
    return (lst->head == NULL);
}


/*
 * end of linked list utils functions
 */