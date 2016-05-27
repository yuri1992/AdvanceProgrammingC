/*
 * Q2
 * by Yuri Ritvin 316961101
 * Task 4 - Binary Trees
 * MTA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEFT 0
#define RIGHT 1
#define SIZE 100

typedef int BOOL;
#define FALSE 0
#define TRUE 1

typedef struct listNode {
    int data;
    struct listNode *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;

typedef struct treeNode {
    int data;
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct tree {
    TreeNode *root;
    List leafList;
} Tree;


/*
 * Utilis Functions for Binary Trees
 */

void freeTreeHelper(TreeNode *root);

void freeTree(Tree tr);

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right);

ListNode *createNodeElement(int num, ListNode *next) ;

void insertNodeToEndList(List *pList, ListNode *newNode) ;

BOOL isEmptyList(List *lst) ;

void createLinkedListOfLeafs(TreeNode *pNode, List * lst);

void insertDataToEndList(List *pList, int ch) ;

void printLeafList(Tree tree) ;

void printInorderHelper(TreeNode *node) ;

void printTreeInorder(Tree tree) ;

void makeEmptyList(List *pList) ;
/*
 * Task function
 */

TreeNode *findParent(Tree pNode, int pTree, int i);

TreeNode *BuildTreeFromArrayHelper(int *arr, int start, int end) ;

Tree BuildTreeFromArrayWithLeafList(int *arr, int size) ;

Tree AddLeaf(Tree tree, TreeNode *pNode, int select, int data);

int main() {
    int size, i;
    int arr[SIZE];
    Tree tr;
    TreeNode *p;
    int parentData, data, branchSelect;

    printf("Please enter the number of items: ");

    scanf("%d", &size);

    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    scanf("%d%d%d", &parentData, &data, &branchSelect);

    tr = BuildTreeFromArrayWithLeafList(arr, size);//the array is given as described in question 1
    //scan the tree inorder (LDR) and find the first parent
    //(a node with parentData as data) that has no child in branchSelect

    p = findParent(tr, parentData, branchSelect);
    tr = AddLeaf(tr, p, branchSelect, data);

    printTreeInorder(tr); //Print the tree in-order (LDR)
    printLeafList(tr); //Print the leaves from left to right

    freeTree(tr);
    return 0;
}

Tree AddLeaf(Tree tree, TreeNode *pNode, int select, int data) {
    if (select == RIGHT)
        pNode->right = createNewTreeNode(data,NULL,NULL);
    else
        pNode->left = createNewTreeNode(data,NULL,NULL);

    makeEmptyList(&tree.leafList);
    createLinkedListOfLeafs(tree.root, &tree.leafList);
    return tree;
}

void printLeafList(Tree tree) {
    ListNode *curr = tree.leafList.head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
}

TreeNode *findParentHelper(TreeNode *pNode, int data) {
    if (pNode == NULL)
        return NULL;
    if (pNode->data == data)
        return pNode;

    TreeNode *res;
    res = findParentHelper(pNode->left, data);
    if (res != NULL)
        return res;
    else {
        res = findParentHelper(pNode->right, data);
        if (res != NULL)
            return res;
    }
    return NULL;
}

TreeNode *findParent(Tree pTree, int data, int i) {
    if (pTree.root == NULL)
        return NULL;
    return findParentHelper(pTree.root, data);
}

Tree BuildTreeFromArrayWithLeafList(int *arr, int size) {
    int ind;
    Tree tr;
    ind = size / 2;
    tr.root = createNewTreeNode((unsigned int) arr[ind],
                                BuildTreeFromArrayHelper(arr, 0, ind - 1),
                                BuildTreeFromArrayHelper(arr, ind + 1, size));
    makeEmptyList(&tr.leafList);
    createLinkedListOfLeafs(tr.root, &tr.leafList);
    return tr;
}

void makeEmptyList(List *pList) {
    pList->head = pList->tail = NULL;
}

void createLinkedListOfLeafs(TreeNode *pNode, List* lst) {
    if (pNode->left == NULL && pNode->right == NULL)
        insertDataToEndList(lst,pNode->data);

    if (pNode->left != NULL)
        createLinkedListOfLeafs(pNode->left, lst);

    if (pNode->right != NULL)
        createLinkedListOfLeafs(pNode->right, lst);

    return;
}

void printTreeInorder(Tree tree) {
    printInorderHelper(tree.root);
    printf("\n");
}

TreeNode *BuildTreeFromArrayHelper(int *arr, int start, int end) {
    int ind = (start + end) / 2;
    if (arr[ind] == -1) {
        return NULL;
    }

    if (start == ind || end == ind) {
        return createNewTreeNode((unsigned int) arr[ind], NULL, NULL);

    } else {
        return createNewTreeNode((unsigned int) arr[ind],
                                 BuildTreeFromArrayHelper(arr, start, ind - 1),
                                 BuildTreeFromArrayHelper(arr, ind + 1, end));
    }

}

void printInorderHelper(TreeNode *node) {
    if (node == NULL)
        return;
    printInorderHelper(node->left);
    printf("%d ", node->data);
    printInorderHelper(node->right);
}


TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right) {
    TreeNode *res;
    res = (TreeNode *) malloc(sizeof(TreeNode));
    res->data = data;
    res->left = left;
    res->right = right;
    return res;
}

void insertDataToEndList(List *pList, int ch) {
    ListNode *lNode;
    lNode = createNodeElement(ch, NULL);
    insertNodeToEndList(pList, lNode);
}

BOOL isEmptyList(List *lst) {
    return (lst->head == NULL);
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
    ListNode *pNode;
    pNode = (ListNode *) malloc(sizeof(ListNode));
    pNode->data = num;
    pNode->next = next;
    return pNode;
}

/* free all memory of a tree */

void freeTree(Tree tr) {
    freeTreeHelper(tr.root);
    tr.root = NULL;
}

void freeTreeHelper(TreeNode *root) {
    if (root == NULL)
        return;
    else {
        freeTreeHelper(root->left);
        freeTreeHelper(root->right);
        free(root);
    }
}