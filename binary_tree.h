//
// Created by Nadav Menirav on 26/12/2025.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdbool.h>

// The binary tree
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// This function will create a new binary search tree
TreeNode* createNode(int data);

// This function will insert a new node to the binary search tree
TreeNode* insertNode(TreeNode* root, int data);

// This function will delete a node from the binary search tree
TreeNode* deleteNode(TreeNode* root, int data);

// This function checks whether a value exists in the tree
bool searchTree(TreeNode* root, int data);

// The function returns the minimus value in the tree
TreeNode* findMin(TreeNode* root);

// This function prints the inorder traversal
void inorderTraversal(TreeNode* root);

// This function prints the preorder traversal
void preorderTraversal(TreeNode* root);

// This function prints the postorder traversal
void postorderTraversal(TreeNode* root);

#endif //BINARY_TREE_H
