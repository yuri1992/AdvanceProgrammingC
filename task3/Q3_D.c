/*
 * Q3_B.c
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

int insertCoordinate(List *coord_list, int x, int y);

void insertYNode(int y, YList *curr, YListNode *currY, YListNode *prevY);

void insertXNode(List *coord_list, int x, int y, XListNode *curr, XListNode *prev);

int main() {

    List coordList;

    int x, y;
    int res;

    coordList = getCoordList();

    // get the (x,y) to insert
    scanf("%d%d", &x, &y);

    res = insertCoordinate(&coordList, x, y);

    if (res == 0)
        printf("The point (%d,%d) didn't appear\n", x, y);
    else
        printf("The point (%d,%d) already appeared\n", x, y);

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

int insertCoordinate(List *coord_list, int x, int y) {
    XListNode *curr;
    YListNode *currY = NULL;
    XListNode *prev = NULL;
    BOOL isFound = FALSE;
    BOOL isFoundY = FALSE;

    curr = coord_list->head;

    while (curr != NULL) {
        if (*(curr->dataPtr) == x) {
            // found X coordinate lets search for Y.
            currY = curr->yCordList->head;
            isFound = TRUE;
            break;
        } else if (*(curr->dataPtr) > x) {
            // our linked list is sorted if we found x coordinate bigger then @x, we can assume @x not exists
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    YListNode *prevY = NULL;
    while (currY != NULL) {
        if (*(currY->dataPtr) == y)
            isFoundY = TRUE;
        if (*(currY->dataPtr) > y) {
            break;
        }
        prevY = currY;
        currY = currY->next;
    }

    if (curr != NULL && isFound == TRUE) {
        // we found @x Coordinate already exists
        insertYNode(y, curr->yCordList, currY, prevY);
    } else {
        // we didn't found @x coordinate both, we know where to insert the new one.
        insertXNode(coord_list, x, y, curr, prev);
    }

    return isFoundY && isFound;
}

void insertXNode(List *coord_list, int x, int y, XListNode *curr, XListNode *prev) {
    /*
     * insertXNode -
     * @x - X coordinate value
     * @Y - Y coordinate value
     * @XList - Pointer to Xlist to be modified
     * @curr - Pointer to Node where new node need to insert before
     * @prev - Pointer to Node where new node need to insert after
     *
     * currY == NULL - we need to insert in the end of list
     * prevY == NULL - we need to insert in the head of list
     * prevY and curr Y != NULL - we should insert @y between them
     */
    XListNode *newXNode = NULL;
    newXNode = createXListNodeElement(x, NULL);
    insertDataToEndYList(newXNode->yCordList, y);
    if (prev == NULL) {
        // insert in the start
        insertNodeToHeadXList(coord_list, newXNode);
    } else if (curr == NULL) {
        // insert in end
        insertNodeToEndXList(coord_list, newXNode);
    } else {
        // insert between @prev and @curr
        newXNode->next = curr;
        prev->next = newXNode;
    }
}

void insertYNode(int y, YList *yList, YListNode *currY, YListNode *prevY) {
    /*
     * insertYNode -
     * @y - Y coordiante value
     * @yList - Pointer to Ylist to be modified
     * @currY - Pointer to Node where new node need to insert before
     * @prevY - Pointer to Node where new node need to insert after
     *
     * currY == NULL - we need to insert in the end of list
     * prevY == NULL - we need to insert in the head of list
     * prevY and curr Y != NULL - we should insert @y between them
     */
    if (currY == NULL) {
        // insert in the end
        insertDataToEndYList(yList, y);
    } else if (prevY == NULL) {
        // insert in the start
        insertDataToStartYList(yList, y);
    } else {
        // insert between @prevY and @currY
        YListNode *lNode;
        lNode = createYListNodeElement(y, NULL);
        lNode->next = currY;
        prevY->next = lNode;
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