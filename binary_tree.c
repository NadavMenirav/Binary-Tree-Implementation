#include "binary_tree.h"

#include <stdlib.h>

// Create a new binary search tree
TreeNode* createNode(const int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// This function checks whether a given value is in the tree
bool searchNode(const TreeNode* root, const int data) {

    // If we have gone over the entire tree without finding, return false
    if (root == NULL) return false;

    // If we found the value, return true
    if (root->data == data) return true;

    // We are in a search tree so if our data is smaller than root - go to left child. Otherwise, right child
    return data < root->data? searchNode(root->left, data): searchNode(root->right, data);
}

// This function returns the node with the minimal value in the tree
TreeNode* findMin(const TreeNode* root) {
    if (root == NULL) return NULL;

    // To find the minimal value in the tree we start from the root and continue to go left
    if (root->left == NULL) return (TreeNode*)root;

    return findMin(root->left);
}

// Prints the inorder traversal
void inorderTraversal(const TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}
