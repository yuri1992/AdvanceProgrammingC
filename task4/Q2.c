
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

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define SIZE 100


typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;


/*
 * Utilis Functions for Binary Trees
 */

void freeTreeHelper(TreeNode *root);

void freeTree(Tree tr);

TreeNode *createNewTreeNode(char data, TreeNode *left, TreeNode *right);

/*
 * Task function
 */

BOOL buildExpressionTree(char str[100], Tree *pTree);

double calcExpression(Tree tree);

TreeNode *getParentOfNode(TreeNode *pNode, Tree *pTree);

double calcExpressionHelper(TreeNode* treeNode) ;

TreeNode *getParentOfNodeHelper(TreeNode *pNode, TreeNode *pNodeNeedle) ;

int main()
{
    char str[SIZE];
    Tree tr;
    double res;
    BOOL expressionOK;
    printf("Please enter the expression: ");
    gets(str);

    expressionOK = buildExpressionTree(str, &tr);

    if(expressionOK == TRUE)
    {
        res = calcExpression(tr);
        printf("%s = %.2f", str, res);
    }
    else
        printf("The input expression is not valid\n");
    freeTree(tr);
    return 0;
}


double calcExpression(Tree tree) {
    /*
     * calcExpression - Wrapper function to implementation of recursive calculation
     */
    return calcExpressionHelper(tree.root);
}

double calcExpressionHelper(TreeNode* treeNode) {
    /*
     * calcExpressionHelper - Recursive implementation of calculation of binary tree
     * each node will be calculated base on @->data attribute
     */
    switch (treeNode->data) {
        case '+':
            return calcExpressionHelper(treeNode->left) + calcExpressionHelper(treeNode->right);
        case '-':
            return calcExpressionHelper(treeNode->left) - calcExpressionHelper(treeNode->right);
        case '*':
            return calcExpressionHelper(treeNode->left) * calcExpressionHelper(treeNode->right);
        case '/':
            return calcExpressionHelper(treeNode->left) / calcExpressionHelper(treeNode->right);
        default:
            return treeNode->data -  '0';
    }

}
BOOL buildExpressionTree(char* str, Tree *pTree) {
    /*
     * buildExpressionTree - creating @Tree from string by the requested terms.
     *
     */
    int openedBrackets = 0;
    pTree->root = createNewTreeNode(NULL, NULL,NULL);
    TreeNode *currentNode = pTree->root;
    while (*str != NULL) {
        /*
         * Iterating over each char of the string
         *  1. if '(' its start of new brackets, create TreeNode without any child
         *      1.1. if there are no left child - create new left child
         *      1.2. if there are no right child - create right child
         *      1.3. else create new node
         *
         *  2. if ')' its end of the previous brackets
         *      2.1. Check that right and left kids are not NULL  - Othewise return False
         *      2.2. Go Out to the previous parent of the node
         *
         *  3. else
         *   3.1. if the char is operator  ( + , - , / * ), save to @->data
         *   3.2. else it probably a number, the assign it to left or right children
         */

        if (*str == '(') {
            if (currentNode->left == NULL) {
                currentNode->left = createNewTreeNode(NULL, NULL, NULL);
                currentNode = currentNode->left;
            } else if (currentNode->right == NULL) {
                currentNode->right = createNewTreeNode(NULL, NULL, NULL);
                currentNode = currentNode->right;
            } else {
                currentNode = createNewTreeNode(NULL, NULL, NULL);
            }
            openedBrackets++;
        } else if(*str == ')') {
            if (currentNode->left == NULL || currentNode->right == NULL) {
                // if one of the leaves is empty the input is propably wrong
                return FALSE;
            }
            currentNode = getParentOfNode(currentNode, pTree);
            openedBrackets--;
        } else {
            if (*str == '+' || *str == '-' || *str == '*' || *str == '/') {
                // char is one of the 4 basic operators
                currentNode->data = *str;
            } else {
                // char is a probably valid number
                if (currentNode->left == NULL)
                    currentNode->left = createNewTreeNode(*str, NULL, NULL);
                else
                    currentNode->right = createNewTreeNode(*str, NULL, NULL);
            }
        }
        str++;
    }
    pTree->root = currentNode->left;
    return openedBrackets==0;
}


TreeNode *getParentOfNode(TreeNode *pNode, Tree *pTree) {
    if (pTree->root == NULL)
        return NULL;
    return getParentOfNodeHelper(pTree->root, pNode);
}

TreeNode *getParentOfNodeHelper(TreeNode *pNode, TreeNode *pNodeNeedle) {
    if (pNode == NULL || (pNode->left == NULL && pNode->right))
        return NULL;
    if (pNode->left == pNodeNeedle || pNode->right == pNodeNeedle)
        return pNode;

    TreeNode *res;
    res = getParentOfNodeHelper(pNode->left, pNodeNeedle);
    if (res != NULL)
        return res;
    else {
        res = getParentOfNodeHelper(pNode->right, pNodeNeedle);
        if (res != NULL)
            return res;
    }

    return NULL;

}


void printInorderHelper(TreeNode *node) {
    if (node == NULL)
        return;
    printInorderHelper(node->left);
    printf("%d ", node->data);
    printInorderHelper(node->right);
}

TreeNode *createNewTreeNode(char data, TreeNode *left, TreeNode *right) {
    TreeNode *res;
    res = (TreeNode *) malloc(sizeof(TreeNode));
    res->data = data;
    res->left = left;
    res->right = right;
    return res;
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