//
// Created by Nadav Menirav on 26/12/2025.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

// The binary tree
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    omp_lock_t lock;
} TreeNode;

// This function will create a new binary search tree
TreeNode* createNode(const int data);

// This function will insert a new node to the binary search tree
TreeNode* insertNode(TreeNode* root, const int data);

// This function will delete a node from the binary search tree
TreeNode* deleteNode(TreeNode* root, const int data);

// This function checks whether a value exists in the tree
bool searchNode(const TreeNode* root, const int data);

// The function returns the minimus value in the tree
TreeNode* findMin(const TreeNode* root);

// This function prints the inorder traversal
void inorderTraversal(TreeNode* root);

// This function prints the preorder traversal
void preorderTraversal(TreeNode* root);

// This function prints the postorder traversal
void postorderTraversal(TreeNode* root);

// This function free the tree
void freeTree(TreeNode* root);

#endif //BINARY_TREE_H
