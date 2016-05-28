//
// Created by yurir on 5/28/16.
//

#include <stdlib.h>
#include <assert.h>
#include "Q3A.h"


void paintTextPicture(TextPicture textPic, char *filename) {
    FILE *fp = NULL;
    prepareForPaint(textPic);

    fp = fopen(filename, "w+");
    assert(fp != NULL);
    paint(textPic, fp);
    fclose(fp);

}

void prepareForPaint(TextPicture textPic) {
    /*
     * preparing @textPic for print, first of all we need to sort it by ASC order of points
     */

    sortPicListForPaint(textPic);
}

void sortPicListForPaint(TextPicture textPic) {

    PicListNode *prevCurr = NULL, *curr, *prevCurrSort = NULL, *currSort;
    curr = textPic.pic.head;

    // sort by X value
    BOOL sorted = FALSE;
    while (sorted == FALSE) {
        sorted = TRUE;
        while (curr != NULL) {
            currSort = curr->next;
            if (currSort != NULL && curr->data.position.y > currSort->data.position.y) {
                swapNodes(curr, currSort);
                sorted = FALSE;
            }
            curr = curr->next;
        }
        curr = textPic.pic.head;
    }

    curr = textPic.pic.head;
    // sort by Y value

    sorted = FALSE;
    while (sorted == FALSE) {
        sorted = TRUE;
        while (curr != NULL) {
            currSort = curr->next;
            if (currSort != NULL &&
                (currSort->data.position.y == curr->data.position.y) &&
                (curr->data.position.x > currSort->data.position.x)) {
                swapNodes(curr, currSort);
                sorted = FALSE;
            }
            curr = curr->next;
        }
        curr = textPic.pic.head;
    }

}

void swapNodes(PicListNode *pNode, PicListNode *pNode2) {
    PicChar temp = pNode->data;
    pNode->data = pNode2->data;
    pNode2->data = temp;

}

void paint(TextPicture textPic, FILE *fp) {
    PicListNode *curr;
    curr = textPic.pic.head;

    for (int y = 0; y < textPic.numRows; y++) {
        if (curr == NULL || curr->data.position.y != y) {
            // not points for @currRow, lets fill all with blank spaces
            fprintf(fp, "%*s\n", textPic.numRows, "");
            printf("%*s\n", textPic.numRows, "");
        } else {
            for (int x = 0; x < textPic.numCols; x++) {
                if (curr == NULL || curr->data.position.x != x || curr->data.position.y != y) {
                    fprintf(fp, " ");
                    printf(" ");
                } else {
                    fprintf(fp, "%c", curr->data.ch);
                    printf("%c", curr->data.ch);
                    curr = curr->next;
                }
            }
            fprintf(fp, "\n");
            printf("\n");
        }
    }
}

void insertNodeToEndList(PicList *pList, PicListNode *newNode) {
    if (isEmptyList(pList)) {
        pList->head = pList->tail = newNode;
    }
    else {
        pList->tail->next = newNode;
        pList->tail = newNode;
    }
}


void makeEmptyList(PicList *pList) {
    pList->head = pList->tail = NULL;
}

BOOL isEmptyList(PicList *lst) {
    return (lst->head == NULL);
}

void freeList(PicList *lst) {
    PicListNode *curr = lst->head, *saver;
    while (curr != NULL) {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
}

void insertDataToEndList(PicList *pList, PicChar picChar) {
    PicListNode *lNode;
    lNode = createNodeElement(picChar, NULL);
    insertNodeToEndList(pList, lNode);
}

PicListNode *createNodeElement(PicChar picChar, PicListNode *next) {
    PicListNode *pNode;
    pNode = malloc(sizeof(PicListNode));
    pNode->data = picChar;
    pNode->next = next;
    return pNode;
}

