#include "binary_tree.h"

#include <stdlib.h>

// This function checks whether a TreeNode* is a leaf. Null is not a leaf.
static inline bool isLeaf(const TreeNode* root);

// This short inline functions check whether a root has a left and right child
static inline bool hasLeftChild(const TreeNode* root);
static inline bool hasRightChild(const TreeNode* root);

// Create a new binary search tree
TreeNode* createNode(const int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// This function inserts a new node to the tree
TreeNode* insertNode(TreeNode* root, const int data) {

    // If we receive a NULL root, we will create a new root and return the new tree. The recursion will not get here.
    if (root == NULL) {
        return createNode(data);
    }


    // Now, we need to decide whether the new node should be in the left or right tree spanned by the root
    if (data <= root->data && hasLeftChild(root)) {
        insertNode(root->left, data);
    }

    else if (data > root->data && hasRightChild(root)) {
        insertNode(root->right, data);
    }

    // Here we know that we need to insert the new node as a left child of current 'root'
    else if (data <= root->data && !hasLeftChild(root)) {
        root->left = createNode(data);
    }

    // Here we know that we need to insert the new node as a right child of current 'root'
    else if (data > root->data && !hasRightChild(root)) {
        root->right = createNode(data);
    }

    return root;
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

// Prints the preorder traversal
void preorderTraversal(const TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Prints the post order traversal
void postorderTraversal(const TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

// Free the tree
void freeTree(TreeNode* root) {
    if (root == NULL) return;

    if (isLeaf(root)) {
        free(root);
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
}

// This function checks whether a TreeNode* is a leaf
static inline bool isLeaf(const TreeNode* root) {
    if (root == NULL) return false;
    return root->left == NULL && root->right == NULL;
}

// This function checks whether a root has a left child
static inline bool hasLeftChild(const TreeNode* root) {
    return root != NULL && root->left != NULL;
}

// This function checks whether a root has a right child
static inline bool hasRightChild(const TreeNode* root) {
    return root != NULL && root->right != NULL;
}
