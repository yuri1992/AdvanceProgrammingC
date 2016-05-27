/*
 * Q3_E.c
 * by Yuri Ritvin 316961101
 * Task 3 - Linked List
 * MTA
 */
#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define POINT_NOT_EXISTS 1
#define POINT_EXISTS_ONLY_ONCE 3
#define POINT_EXISTS_MORE_THEN_ONCE 2
#define OTHER 4
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
 * Utils Function definition both for List and YList structs
 */

void makeEmptyXList(List *pList);

void makeEmptyYList(YList *pList);

XListNode *createXListNodeElement(int num, XListNode *next);

YListNode *createYListNodeElement(int num, YListNode *next);

void insertDataToEndXList(List *pList, int ch);

void insertDataToEndYList(YList *pList, int ch);

void insertDataToStartYList(YList *pList, int ch);

void insertNodeToEndXList(List *pList, XListNode *newNode);

void insertNodeToEndYList(YList *pList, YListNode *newNode);

void insertNodeToHeadXList(List *pList, XListNode *newNode);

void insertNodeToHeadYList(YList *pList, YListNode *newNode);

void freeXList(List *pList);

void freeYList(YList *pList);

BOOL isEmptyXList(List *lst);

BOOL isEmptyYList(YList *lst);

unsigned int getYListLength(YList *lst);

/*
 * End of utils function definition
 */


List getCoordList();

int removeCoordinate(List *coord_list, int x, int y);

XListNode *getXNode(List *coord_list, int x);

void deleteXNode(List *coord_list, XListNode *x);

int removeYNode(List *coord_list, int y, XListNode *curr, YList *ylist, YListNode *currY, YListNode *prevY);

int main() {
    List coordList;

    int x, y;
    int res;

    coordList = getCoordList();

// get the (x,y) to remove
    scanf("%d%d", &x, &y);

    res = removeCoordinate(&coordList, x, y);

    if (res == 1)
        printf("The point (%d,%d) didn't appear\n", x, y);
    else if (res == 2)
        printf("The point (%d,%d) has another occurrence\n", x, y);
    else if (res == 3)
        printf("The point (%d,%d) was the only point with this x\n", x, y);
    else
        printf("Other\n");

    freeXList(&coordList);
}


List getCoordList() {
    List res;
    XListNode *currXNode = NULL;
    int size, i, lastXValue = 0;

    makeEmptyXList(&res);
    scanf("%d", &size);

    for (i = 0; i < size; i++) {
        int x, y;
        scanf("%d", &x);
        scanf("%d", &y);
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

int removeCoordinate(List *coord_list, int x, int y) {
    /*
     * removeCoordinate - remove (@x,@y) from @coord_list
     * 5 1 2 1 5 2 7 3 3 3 8 1 5
     */
    XListNode *curr;
    // return pointer to found XNode of value @x
    curr = getXNode(coord_list, x);
    if (curr != NULL) {
        YList *ylist = curr->yCordList;
        YListNode *currY = ylist->head;
        YListNode *prevY = NULL;
        while (currY != NULL) {
            if (*(currY->dataPtr) == y) {
                return removeYNode(coord_list, y, curr, ylist, currY, prevY);
            }
            prevY = currY;
            currY = currY->next;
        }
    }
    return POINT_NOT_EXISTS;
}

int removeYNode(List *coord_list, int y, XListNode *curr, YList *ylist, YListNode *currY,
                YListNode *prevY) {
    /*
     * removeYNode - remove @y value from @ylist
     * @coord_list - pointer to linked list of x values - that can be removed if we remove all @y values
     * @y - Y coordiante value
     * @curr - pointer to @x value XNode
     * @ylist - Pointer to Ylist values
     * @currY - Pointer to will be removed @y Node
     * @prevY - Pointer to previous Node before @currY
     */
    YListNode *saver = currY;
    int res = OTHER;
    if (ylist->head == ylist->tail) {
        // ylist contains only one point, we need to remove also XNode
        deleteXNode(coord_list, curr);
        res = POINT_EXISTS_ONLY_ONCE;
    } else if (prevY != NULL && currY->next != NULL) {
        // we removing node in middle of list, @currY located in middle of the list (not head or tail)
        prevY->next = currY->next;
        if (*(currY->next->dataPtr) == y) {
            res = POINT_EXISTS_MORE_THEN_ONCE;
        }
    } else if (prevY == NULL && currY != NULL) {
        // removing node in start of list
        ylist->head = currY->next;
        if (*(currY->next->dataPtr) == y) {
            res = POINT_EXISTS_MORE_THEN_ONCE;
        }
    } else {
        // removing node in end of list
        ylist->tail = prevY;
    }
    free(saver);
    return res;
}

XListNode *getXNode(List *coord_list, int x) {
    /*
     * getXNode - Return Pointer of Null to first found @x value node
     */
    XListNode *curr;
    curr = coord_list->head;
    while (curr != NULL) {
        if (*(curr->dataPtr) > x)
            return NULL;
        if (*(curr->dataPtr) == x)
            return curr;
        curr = curr->next;
    }
    return curr;
}

void deleteXNode(List *coord_list, XListNode *x) {
    /*
     * deleteXNode - delete @*x node from coord_list
     */
    XListNode *curr;
    XListNode *prev = NULL;
    XListNode *saver = NULL;
    curr = coord_list->head;
    while (curr != NULL) {
        if (curr == x) {
            saver = curr;
            if (prev == NULL) {
                coord_list->head = curr->next;
            } else if (curr->next == NULL) {
                coord_list->tail = prev;
            } else {
                prev->next = curr->next;
            }
            free(saver);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
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

void insertNodeToHeadXList(List *pList, XListNode *newNode) {
    newNode->next = pList->head;
    if (pList->tail == NULL)
        pList->tail = newNode;
    pList->head = newNode;
}

void insertNodeToHeadYList(YList *pList, YListNode *newNode) {
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

unsigned int getYListLength(YList *lst) {
    YListNode *curr;
    unsigned int num = 0;
    curr = lst->head;
    while (curr != NULL) {
        num++;
        curr = curr->next;
    }
    return num;
}

/*
 * end of linked list utils functions
 */