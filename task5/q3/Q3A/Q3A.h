//
// Created by yurir on 5/28/16.
//

#ifndef ADVANCEDPROGRAMING_Q3A_H
#define ADVANCEDPROGRAMING_Q3A_H

#include <stdio.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct point{
    int x;
    int y;
} Point;

typedef struct picChar{
    Point position;
    char ch;
} PicChar;

typedef struct picListNode{
    PicChar data;
    struct picListNode* next;
} PicListNode;

typedef struct picList{
    PicListNode* head;
    PicListNode* tail;
} PicList;

typedef struct textPicture{
    int numRows;
    int numCols;
    PicList pic;
} TextPicture;


void paintTextPicture(TextPicture textPic, char* filename);
void prepareForPaint(TextPicture textPic);
void sortPicListForPaint(TextPicture textPic);
void paint(TextPicture textPic, FILE *fp);


/*
 * Utils Function for linked list
 */


void makeEmptyList(PicList *pList);
void insertDataToEndList(PicList *pList, PicChar picChar);
void insertNodeToEndList(PicList *pList, PicListNode *newNode);
void freeList(PicList *pList);
BOOL isEmptyList(PicList *lst);
PicListNode *createNodeElement(PicChar picChar, PicListNode *next);
void swapNodes(PicListNode *pNode, PicListNode *pNode2);


#endif //ADVANCEDPROGRAMING_Q3A_H
