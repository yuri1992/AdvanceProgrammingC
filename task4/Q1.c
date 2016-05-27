/*
 * Q1
 * by Yuri Ritvin 316961101
 * Task 4 - Binary Trees
 * MTA
 */

#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define SIZE 100

typedef struct treeNode {
    unsigned int data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;


/*
 * Utilis Functions for Binary Trees
 */

TreeNode *createNewTreeNode(unsigned int data, TreeNode *left, TreeNode *right);

void freeTreeHelper(TreeNode *root);

void freeTree(Tree tr);

/*
 * Task function
 */

Tree BuildTreeFromArray(int *arr, int size);

TreeNode *BuildTreeFromArrayHelper(int *arr, int start, int end) ;

void printTreeInorder(Tree tree);

void printInorderHelper(TreeNode *node);


int main() {
    //3 2 11 15 -1 4 -1 55 -1 -1 -1 3 -1 17 -1
    int size, i;
    int arr[SIZE];
    Tree tr;

    printf("Please enter the number of items: ");
    scanf("%d", &size);
    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    tr = BuildTreeFromArray(arr, size);
    // tests not excpecting this line
    printf("The tree in inorder (LDR) format:\n");
    printTreeInorder(tr); //Print the tree in-order (LDR)
    freeTree(tr);
}

void printInorderHelper(TreeNode *node) {
    /*
     * Actual Inorder Print function
     * @node - TreeNode Element
     */
    if (node == NULL)
        return;
    printInorderHelper(node->left);
    printf("%d ", node->data);
    printInorderHelper(node->right);
}

void printTreeInorder(Tree tree) {
    /*
     * recursive implementation of inorder print
     * @tree - Binary Tree
     */
    printInorderHelper(tree.root);
}

Tree BuildTreeFromArray(int *arr, int size) {
    /*
     * Convert an Array of int to Binary Tree Structure @Tree
     * @arr - Pointer to int array
     * @size - size of @arr
     */

    Tree tr;
    int ind;
    ind = size / 2;
    tr.root = createNewTreeNode((unsigned int) arr[ind],
                                BuildTreeFromArrayHelper(arr, 0, ind-1),
                                BuildTreeFromArrayHelper(arr, ind+1, size));
    return tr;
}

TreeNode *BuildTreeFromArrayHelper(int *arr, int start, int end) {
    /*
     * recursive implement of arr to @TreeNode
     * @arr - pointer to array
     * @start - from where the array start
     * @end - till what index
     */
    int ind = (start + end) / 2;
    if (arr[ind] == -1) {
        return NULL;
    }

    if (start == ind || end == ind) {
        return createNewTreeNode((unsigned int) arr[ind], NULL, NULL);
    } else {
        return createNewTreeNode((unsigned int) arr[ind],
                                 BuildTreeFromArrayHelper(arr, start, ind-1),
                                 BuildTreeFromArrayHelper(arr, ind+1, end));
    }

}

TreeNode *createNewTreeNode(unsigned int data, TreeNode *left, TreeNode *right) {
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