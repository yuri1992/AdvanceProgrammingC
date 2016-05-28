//
// Created by yurir on 5/28/16.
//

#include "Q3A.h"

int main() {
    TextPicture testPic;
    testPic.numCols = 8;
    testPic.numRows = 5;
    PicChar t1,t2,t3,t4,t5;
    Point x1,x2,x3,x4,x5;

    // initial test data
    //(4,2,'$')
    x1.x = 2;
    x1.y = 2;
    t1.ch = '$';
    t1.position = x1;
    
    //(3,1,'#')
    x2.x = 3;
    x2.y = 1;
    t2.ch = '#';
    t2.position = x2;

    //(2,2,'$')
    x3.x = 3;
    x3.y = 2;
    t3.ch = '#';
    t3.position = x3;

    //(3,2,'#')
    x4.x = 4;
    x4.y = 2;
    t4.ch = '$';
    t4.position = x4;

    makeEmptyList(&testPic.pic);
    insertDataToEndList(&testPic.pic, t1);
    insertDataToEndList(&testPic.pic, t2);
    insertDataToEndList(&testPic.pic, t3);
    insertDataToEndList(&testPic.pic, t4);

    paintTextPicture(testPic, "out.txt");
}


