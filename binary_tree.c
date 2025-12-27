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

/*
 * This function deletes a node from the tree.
 * If the node we want to delete is a leaf we just delete it by freeing the memory and setting the parent child to NULL
 * If the node we want to delete has only 1 child we delete it and replace and set the parent to point at this  child
 * If the node we want to delete has two children we replace it with the minimal value in the right tree and delete
 */
TreeNode* deleteNode(TreeNode* root, const int data) {

    TreeNode* node = root, *parent = NULL;
    bool isOnlyLeft = false, isOnlyRight = false;

    // If we received a NULL we don't delete anything
    if (root == NULL) {
        return NULL;
    }

    // Finding the place to delete from
    while (node != NULL) {

        // If we found the node to delete
        if (data == node->data) break;

        // We didn't yet found the node to delete, but we know that it is in the left subtree of current 'node'
        if (data <= node->data && hasLeftChild(node)) {
            parent = node;
            node = node->left;
        }

        // We didn't yet found the node to delete, but we know that it is in the right subtree of current 'node'
        else if (data > node->data && hasRightChild(node)) {
            parent = node;
            node = node->right;
        }
    }

    // If the given value is not in the tree
    if (node == NULL) return root;

    // Now we distinguish between 3 cases
    // Case 1: the deleted node is a leaf. In this case we need to just make the parent point to null and free the node
    if (isLeaf(node)) {

        // If the given node is the root, it means this tree is only one node and we should return null
        if (!parent) {
            free(node);
            return NULL;
        }

        if (parent->left == node) parent->left = NULL;
        else parent->right = NULL;
        free(node);
        return root;
    }

    // Case 2: the deleted node has only one child. in this case we just make the parent point to the child and free
    isOnlyLeft = hasLeftChild(node) && !hasRightChild(node);
    isOnlyRight = hasRightChild(node) && !hasLeftChild(node);
    if (isOnlyLeft || isOnlyRight) {

        // If the deleted node is the root, we just make the child the new root
        if (!parent) {
            if (isOnlyLeft) {
                root = node->left;
            }

            else {
                root = node->right;
            }

            free(node);
            return root;
        }

        if (parent->left == node) {
            if (isOnlyLeft) {
                parent->left = node->left;
            }
            else {
                parent->left = node->right;
            }
        }
        else {
            if (isOnlyLeft) {
                parent->right = node->left;
            }
            else {
                parent->right = node->right;
            }
        }
        free(node);
        return root;

    }



    // Case 3: the deleted node has two children. In this case we find the minimal value in right subtree and replace
    if (hasLeftChild(node) && hasRightChild(node)) {
        TreeNode* min_node_in_right_subtree = node->right, *parent_min_node = node;
        while (min_node_in_right_subtree != NULL) {
            if (min_node_in_right_subtree->left == NULL) break;

            parent_min_node = min_node_in_right_subtree;
            min_node_in_right_subtree = min_node_in_right_subtree->left;
        }

        // We keep the value of the min node, it will replace 'node'
        const int replacement = min_node_in_right_subtree->data;

        // Delete the replacement node
        if (parent_min_node->left == min_node_in_right_subtree) {
            parent_min_node->left = min_node_in_right_subtree->right;
        }

        else {
            parent_min_node->right = min_node_in_right_subtree->right;
        }        free(min_node_in_right_subtree);

        // Replace 'node' with the min node
        node->data = replacement;

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
