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
    omp_init_lock(&node->lock);

    return node;
}

// This function inserts a new node to the tree
TreeNode* insertNode(TreeNode* root, const int data) {

    TreeNode* parent = root;

    // If we receive a NULL root, we will create a new root and return the new tree.
    if (root == NULL) {
        return createNode(data);
    }

    // First, we try to set the lock
    omp_set_lock(&parent->lock);
    omp_lock_t* lock_to_free = NULL;
    while (parent) {

        // First we unset the lock of the previous parent
        if (lock_to_free) omp_unset_lock(lock_to_free);

        lock_to_free = &parent->lock;

        // Now, we need to decide whether the new node should be in the left or right tree spanned by the root
        if (data <= parent->data && hasLeftChild(parent)) {
            omp_set_lock(&parent->left->lock);
            parent = parent->left;
        }

        else if (data > parent->data && hasRightChild(parent)) {
            omp_set_lock(&parent->right->lock);
            parent = parent->right;
        }

        // Here we know that we need to insert the new node as a left child of current 'root'
        else if (data <= parent->data && !hasLeftChild(parent)) {
            parent->left = createNode(data);
            break;
        }

        // Here we know that we need to insert the new node as a right child of current 'root'
        else if (data > parent->data && !hasRightChild(parent)) {
            parent->right = createNode(data);
            break;
        }
    }
    if (lock_to_free) omp_unset_lock(lock_to_free);

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

    if (root == NULL) return NULL;

    // Locking the node
    omp_set_lock(&node->lock);
    omp_lock_t* lock_to_free = NULL;

    // Finding the place to delete from
    while (node != NULL) {
        // Optimization: If we found the node, we stop immediately.
        // We hold 'lock_to_free' (Parent) and 'node->lock' (Target).
        // By setting lock_to_free = NULL, we ensure Parent stays locked.
        if (node->data == data) {
            lock_to_free = NULL;
            break;
        }

        if (lock_to_free) omp_unset_lock(lock_to_free);
        lock_to_free = &node->lock;

        // We didn't yet found the node to delete, but we know that it is in the left subtree
        if (data <= node->data && hasLeftChild(node)) {
            omp_set_lock(&node->left->lock);
            parent = node;
            node = node->left;
        }
        // We didn't yet found the node to delete, but we know that it is in the right subtree
        else if (data > node->data && hasRightChild(node)) {
            omp_set_lock(&node->right->lock);
            parent = node;
            node = node->right;
        }
        else {
            // Path doesn't exist (Data not found)
            node = NULL; // Force loop exit
        }
    }

    // If the given value is not in the tree
    if (node == NULL) {
        if (lock_to_free) omp_unset_lock(lock_to_free);
        return root;
    }

    // Case 1: the deleted node is a leaf.
    if (isLeaf(node)) {
        if (!parent) {
            omp_destroy_lock(&node->lock);
            free(node);
            return NULL;
        }

        if (parent->left == node) parent->left = NULL;
        else parent->right = NULL;

        omp_unset_lock(&parent->lock);
        omp_destroy_lock(&node->lock);
        free(node);
        return root;
    }

    // Case 2: the deleted node has only one child.
    isOnlyLeft = hasLeftChild(node) && !hasRightChild(node);
    isOnlyRight = hasRightChild(node) && !hasLeftChild(node);
    if (isOnlyLeft || isOnlyRight) {

        if (!parent) {
            TreeNode* child = isOnlyLeft ? node->left : node->right;

            // Promote child data to root
            node->data = child->data;
            node->left = child->left;
            node->right = child->right;

            omp_set_lock(&child->lock); //
            omp_unset_lock(&child->lock); // Unlock (just to ensure no one else is holding it)
            omp_destroy_lock(&child->lock);
            free(child);

            omp_unset_lock(&node->lock);
            return root;
        }

        // Standard Case 2
        if (parent->left == node) {
            parent->left = isOnlyLeft ? node->left : node->right;
        }
        else {
            parent->right = isOnlyLeft ? node->left : node->right;
        }

        omp_unset_lock(&parent->lock);
        omp_destroy_lock(&node->lock);
        free(node);
        return root;
    }

    // Case 3: the deleted node has two children. In this case we find the minimal value in right subtree and replace
    if (hasLeftChild(node) && hasRightChild(node)) {

        // // We don't need the parent anymore
        if (parent) omp_unset_lock(&parent->lock);

        TreeNode* min_node_in_right_subtree = node->right, *parent_min_node = node;

        // We catch the lock of the min_node
        omp_set_lock(&min_node_in_right_subtree->lock);
        omp_lock_t* lock_to_free = NULL;

        while (min_node_in_right_subtree != NULL) {

            if (lock_to_free) omp_unset_lock(lock_to_free);

            if (min_node_in_right_subtree->left == NULL) break;

            omp_set_lock(&min_node_in_right_subtree->left->lock);

            lock_to_free = &min_node_in_right_subtree->lock;
            if (min_node_in_right_subtree->left->left == NULL) lock_to_free = NULL;

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
        }
        if (parent_min_node != node) omp_unset_lock(&parent_min_node->lock);
        omp_destroy_lock(&min_node_in_right_subtree->lock);
        free(min_node_in_right_subtree);

        // Replace 'node' with the min node
        node->data = replacement;
        omp_unset_lock(&node->lock);

    }
    return root;
}

// This function checks whether a given value is in the tree
bool searchNode(const TreeNode* root, const int data) {

    TreeNode* node = (TreeNode*)root;

    // Locking the current node
    omp_set_lock(&node->lock);
    omp_lock_t* lock_to_free = NULL;
    while (node) {

        if (lock_to_free) omp_unset_lock(lock_to_free);

        lock_to_free = &node->lock;

        // If we found the data
        if (node->data == data) {
            omp_unset_lock(&node->lock);
            return true;
        }

        // We should go left
        if (data <= node->data) {

            // If we should go left, but we cannot go left anymore -> return false
            if (!node->left) {
                omp_unset_lock(&node->lock);
                return false;
            }

            omp_set_lock(&node->left->lock);
            node = node->left;
        }

        // We should go right
        else if (data > node->data) {

            // If we should go right, but we cannot go right anymore-> return false
            if (!node->right) {
                omp_unset_lock(&node->lock);
                return false;
            }

            omp_set_lock(&node->right->lock);
            node = node->right;
        }
    }

    return false;
}

// This function returns the node with the minimal value in the tree
TreeNode* findMin(const TreeNode* root) {

    // If the tree is non-existent we return null
    if (root == NULL) return NULL;

    TreeNode* node = (TreeNode*)root;

    // Locking the initial node
    omp_set_lock(&node->lock);
    omp_lock_t* lock_to_free = NULL;
    while (node->left != NULL) {

        if (lock_to_free) omp_unset_lock(lock_to_free);

        lock_to_free = &node->lock;

        omp_set_lock(&node->left->lock);
        node = node->left;
    }

    if (lock_to_free) omp_unset_lock(lock_to_free);
    omp_unset_lock(&node->lock);
    return (TreeNode*)node;
}

// Prints the inorder traversal
void inorderTraversal(const TreeNode* root) {
    if (root == NULL) return;

    TreeNode* node = (TreeNode*)root;
    omp_set_lock(&node->lock);

    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);

    omp_unset_lock(&node->lock);
}

// Prints the preorder traversal
void preorderTraversal(const TreeNode* root) {
    if (root == NULL) return;

    TreeNode* node = (TreeNode*)root;
    omp_set_lock(&node->lock);
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
    omp_unset_lock(&node->lock);
}

// Prints the post order traversal
void postorderTraversal(const TreeNode* root) {
    if (root == NULL) return;
    TreeNode* node = (TreeNode*)root;
    omp_set_lock(&node->lock);
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
    omp_unset_lock(&node->lock);
}

// Free the tree
void freeTree(TreeNode* root) {
    // 1. Base case: if the node is NULL, there's nothing to do
    if (root == NULL) return;

    // 2. Recursively free the left subtree
    freeTree(root->left);

    // 3. Recursively free the right subtree
    freeTree(root->right);

    // 4. Finally, free the current node
    omp_destroy_lock(&(root->lock));
    free(root);
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
