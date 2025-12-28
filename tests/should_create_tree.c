#define CUNIT_IMPLEMENTATION
#include "../external/cunit.h"

#include "../binary_tree.h"

CUNIT_TEST(create_tree)
{
    TreeNode* node_10 = createNode(10);
    node_10 = insertNode(node_10, 5);
    node_10 = insertNode(node_10, 15);
    node_10 = insertNode(node_10, 3);
    node_10 = insertNode(node_10, 7);
    node_10 = insertNode(node_10, 12);
    node_10 = insertNode(node_10, 18);
    node_10 = insertNode(node_10, 10);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10);
    CUNIT_ASSERT_INT_EQ(node_10->data, 10);

    TreeNode* node_5 = node_10->left;
    CUNIT_ASSERT_PTR_NOT_NULL(node_5);
    CUNIT_ASSERT_INT_EQ(node_5->data, 5);

    TreeNode* node_3 = node_5->left;
    CUNIT_ASSERT_PTR_NOT_NULL(node_3);
    CUNIT_ASSERT_INT_EQ(node_3->data, 3);
    CUNIT_ASSERT_PTR_NULL(node_3->left);
    CUNIT_ASSERT_PTR_NULL(node_3->right);

    TreeNode* node_7 = node_5->right;
    CUNIT_ASSERT_PTR_NOT_NULL(node_7);
    CUNIT_ASSERT_INT_EQ(node_7->data, 7);
    CUNIT_ASSERT_PTR_NULL(node_7->left);

    TreeNode* node_10_second = node_7->right;
    CUNIT_ASSERT_PTR_NOT_NULL(node_10_second);
    CUNIT_ASSERT_INT_EQ(node_10_second->data, 10);
    CUNIT_ASSERT_PTR_NULL(node_10_second->left);
    CUNIT_ASSERT_PTR_NULL(node_10_second->right);

    TreeNode* node_15 = node_10->right;
    CUNIT_ASSERT_PTR_NOT_NULL(node_15);
    CUNIT_ASSERT_INT_EQ(node_15->data, 15);

    TreeNode* node_12 = node_15->left;
    CUNIT_ASSERT_PTR_NOT_NULL(node_12);
    CUNIT_ASSERT_INT_EQ(node_12->data, 12);
    CUNIT_ASSERT_PTR_NULL(node_12->left);
    CUNIT_ASSERT_PTR_NULL(node_12->right);

    TreeNode* node_18 = node_15->right;
    CUNIT_ASSERT_PTR_NOT_NULL(node_18);
    CUNIT_ASSERT_INT_EQ(node_18->data, 18);
    CUNIT_ASSERT_PTR_NULL(node_18->left);
    CUNIT_ASSERT_PTR_NULL(node_18->right);
}

CUNIT_TEST(min_node)
{
    TreeNode* tree = createNode(10);
    TreeNode* minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 10);

    insertNode(tree, 5);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 5);

    insertNode(tree, 15);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 5);

    insertNode(tree, 3);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);

    insertNode(tree, 7);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);

    insertNode(tree, 12);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);

    insertNode(tree, 18);
    minNode = findMin(tree);
    CUNIT_ASSERT_PTR_NOT_NULL(minNode);
    CUNIT_ASSERT_INT_EQ(minNode->data, 3);
}

CUNIT_TEST(search_node)
{
    TreeNode* node_10 = createNode(10);
    node_10 = insertNode(node_10, 5);
    node_10 = insertNode(node_10, 15);
    node_10 = insertNode(node_10, 3);
    node_10 = insertNode(node_10, 7);
    node_10 = insertNode(node_10, 12);
    node_10 = insertNode(node_10, 18);

    CUNIT_ASSERT_TRUE(searchNode(node_10, 10));
    CUNIT_ASSERT_TRUE(searchNode(node_10, 15));
    CUNIT_ASSERT_TRUE(searchNode(node_10, 3));
    CUNIT_ASSERT_TRUE(searchNode(node_10, 7));
    CUNIT_ASSERT_TRUE(searchNode(node_10, 12));
    CUNIT_ASSERT_TRUE(searchNode(node_10, 18));

    CUNIT_ASSERT_FALSE(searchNode(node_10, 1));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 2));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 4));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 6));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 8));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 9));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 11));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 13));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 14));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 16));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 17));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 19));
    CUNIT_ASSERT_FALSE(searchNode(node_10, 20));
}

CUNIT_TEST(delete_root_two_descendants)
{
    TreeNode* node_10 = createNode(10);
    node_10 = insertNode(node_10, 5);
    node_10 = insertNode(node_10, 15);
    node_10 = insertNode(node_10, 3);
    node_10 = insertNode(node_10, 7);
    node_10 = insertNode(node_10, 12);
    node_10 = insertNode(node_10, 18);

    TreeNode* updated_root = deleteNode(node_10, 10);
    CUNIT_ASSERT_PTR_NOT_NULL(updated_root);
    CUNIT_ASSERT_INT_EQ(updated_root->data, 12);

    CUNIT_ASSERT_PTR_NOT_NULL(updated_root->left);
    CUNIT_ASSERT_INT_EQ(updated_root->left->data, 5);

    CUNIT_ASSERT_PTR_NOT_NULL(updated_root->left->left);
    CUNIT_ASSERT_INT_EQ(updated_root->left->left->data, 3);
    CUNIT_ASSERT_PTR_NULL(updated_root->left->left->left);
    CUNIT_ASSERT_PTR_NULL(updated_root->left->left->right);

    CUNIT_ASSERT_PTR_NOT_NULL(updated_root->left->right);
    CUNIT_ASSERT_INT_EQ(updated_root->left->right->data, 7);
    CUNIT_ASSERT_PTR_NULL(updated_root->left->right->left);
    CUNIT_ASSERT_PTR_NULL(updated_root->left->right->right);

    CUNIT_ASSERT_PTR_NOT_NULL(updated_root->right);
    CUNIT_ASSERT_INT_EQ(updated_root->right->data, 15);

    CUNIT_ASSERT_PTR_NULL(updated_root->right->left);

    CUNIT_ASSERT_PTR_NOT_NULL(updated_root->right->right);
    CUNIT_ASSERT_INT_EQ(updated_root->right->right->data, 18);

    CUNIT_ASSERT_PTR_NULL(updated_root->right->right->right);
    CUNIT_ASSERT_PTR_NULL(updated_root->right->right->left);
}

CUNIT_TEST(delete_root_single_descendant)
{
    TreeNode* node_10 = createNode(10);
    node_10 = insertNode(node_10, 5);
    node_10 = insertNode(node_10, 3);
    node_10 = insertNode(node_10, 7);

    TreeNode* updated_root = deleteNode(node_10, 10);
    CUNIT_ASSERT_PTR_NOT_NULL(updated_root);
    CUNIT_ASSERT_INT_EQ(updated_root->data, 5);

    CUNIT_ASSERT_PTR_NOT_NULL(updated_root->left);
    CUNIT_ASSERT_INT_EQ(updated_root->left->data, 3);
    CUNIT_ASSERT_PTR_NULL(updated_root->left->left);
    CUNIT_ASSERT_PTR_NULL(updated_root->left->right);

    CUNIT_ASSERT_PTR_NOT_NULL(updated_root->right);
    CUNIT_ASSERT_INT_EQ(updated_root->right->data, 7);
    CUNIT_ASSERT_PTR_NULL(updated_root->right->left);
    CUNIT_ASSERT_PTR_NULL(updated_root->right->right);
}

CUNIT_TEST(delete_non_root_two_descendants)
{
    TreeNode* node_10 = createNode(10);
    node_10 = insertNode(node_10, 5);
    node_10 = insertNode(node_10, 15);
    node_10 = insertNode(node_10, 3);
    node_10 = insertNode(node_10, 7);
    node_10 = insertNode(node_10, 12);
    node_10 = insertNode(node_10, 18);

    node_10 = deleteNode(node_10, 5);
    CUNIT_ASSERT_PTR_NOT_NULL(node_10);
    CUNIT_ASSERT_INT_EQ(node_10->data, 10);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->left);
    CUNIT_ASSERT_INT_EQ(node_10->left->data, 7);
    CUNIT_ASSERT_PTR_NULL(node_10->left->right);
    CUNIT_ASSERT_PTR_NOT_NULL(node_10->left->left);
    CUNIT_ASSERT_INT_EQ(node_10->left->left->data, 3);
    CUNIT_ASSERT_PTR_NULL(node_10->left->left->left);
    CUNIT_ASSERT_PTR_NULL(node_10->left->left->right);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->right);
    CUNIT_ASSERT_INT_EQ(node_10->right->data, 15);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->right->left);
    CUNIT_ASSERT_INT_EQ(node_10->right->left->data, 12);
    CUNIT_ASSERT_PTR_NULL(node_10->right->left->left);
    CUNIT_ASSERT_PTR_NULL(node_10->right->left->right);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->right->right);
    CUNIT_ASSERT_INT_EQ(node_10->right->right->data, 18);
    CUNIT_ASSERT_PTR_NULL(node_10->right->right->left);
    CUNIT_ASSERT_PTR_NULL(node_10->right->right->right);
}

CUNIT_TEST(delete_non_root_min_in_right_subtree_is_not_null)
{
    TreeNode* node_10 = createNode(10);
    node_10 = insertNode(node_10, 5);
    node_10 = insertNode(node_10, 15);
    node_10 = insertNode(node_10, 3);
    node_10 = insertNode(node_10, 7);
    node_10 = insertNode(node_10, 12);
    node_10 = insertNode(node_10, 18);
    node_10 = insertNode(node_10, 8);

    node_10 = deleteNode(node_10, 5);
    CUNIT_ASSERT_PTR_NOT_NULL(node_10);
    CUNIT_ASSERT_INT_EQ(node_10->data, 10);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->left);
    CUNIT_ASSERT_INT_EQ(node_10->left->data, 7);
    CUNIT_ASSERT_PTR_NOT_NULL(node_10->left->right);
    CUNIT_ASSERT_INT_EQ(node_10->left->right->data, 8);
    CUNIT_ASSERT_PTR_NULL(node_10->left->right->left);
    CUNIT_ASSERT_PTR_NULL(node_10->left->right->right);
    CUNIT_ASSERT_PTR_NOT_NULL(node_10->left->left);
    CUNIT_ASSERT_INT_EQ(node_10->left->left->data, 3);
    CUNIT_ASSERT_PTR_NULL(node_10->left->left->left);
    CUNIT_ASSERT_PTR_NULL(node_10->left->left->right);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->right);
    CUNIT_ASSERT_INT_EQ(node_10->right->data, 15);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->right->left);
    CUNIT_ASSERT_INT_EQ(node_10->right->left->data, 12);
    CUNIT_ASSERT_PTR_NULL(node_10->right->left->left);
    CUNIT_ASSERT_PTR_NULL(node_10->right->left->right);

    CUNIT_ASSERT_PTR_NOT_NULL(node_10->right->right);
    CUNIT_ASSERT_INT_EQ(node_10->right->right->data, 18);
    CUNIT_ASSERT_PTR_NULL(node_10->right->right->left);
    CUNIT_ASSERT_PTR_NULL(node_10->right->right->right);
}

static int is_valid_tree(TreeNode* root)
{
    int is_valid = true;
    if (root == NULL)
    {
        return true;
    }
    if (root->left != NULL)
    {
        is_valid = is_valid && root->left->data <= root->data && is_valid_tree(root->left);
    }
    if (root->right != NULL)
    {
        is_valid = is_valid && root->right->data > root->data && is_valid_tree(root->right);
    }

    return is_valid;
}

CUNIT_TEST(insertion_large)
{
    TreeNode* tree = createNode(0);
    for (size_t i = 1; i < 100; ++i)
    {
        tree = insertNode(tree, i);
    }

    CUNIT_ASSERT_TRUE(is_valid_tree(tree));
    int did_insert_everything = 1;
    for (size_t i = 0; i < 100; ++i)
    {
        did_insert_everything = did_insert_everything && searchNode(tree, i);
    }
}

CUNIT_TEST(deletion_large)
{
    TreeNode* tree = createNode(0);
    for (size_t i = 1; i < 100; ++i)
    {
        tree = insertNode(tree, i);
    }
    for (size_t i = 0; i < 100; ++i)
    {
        if (i % 3 == 0)
        {
            tree = deleteNode(tree, i);
        }
    }

    CUNIT_ASSERT_TRUE(is_valid_tree(tree));
    preorderTraversal(tree);
    for (size_t i = 0; i < 100; ++i)
    {
        if (i % 3 == 0)
        {
            CUNIT_ASSERT_FALSE(searchNode(tree, i));
        }
        else
        {
            CUNIT_ASSERT_TRUE(searchNode(tree, i));
        }
    }
}