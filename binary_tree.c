#include "binary_tree.h"

#include <stdlib.h>

TreeNode* createNode(const int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

bool searchNode(TreeNode* root, int data) {
    if (root == NULL) return false;
    if (root->data == data) return true;

    return data < root->data? searchNode(root->left, data): searchNode(root->right, data);
}