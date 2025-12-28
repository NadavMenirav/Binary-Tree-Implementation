#include <omp.h>
#include <stdio.h>

#include "../external/cunit.h"
#include "../binary_tree.h"

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

CUNIT_TEST(thread_safe_insertion)
{
    TreeNode* tree = createNode(0);
#pragma omp parallel for schedule(static, 6)
    for (size_t i = 1; i < 100; ++i)
    {
        insertNode(tree, i);
    }

    CUNIT_ASSERT_TRUE(is_valid_tree(tree));
    int did_insert_everything = 1;
#pragma omp parallel for schedule(static, 6) reduction(&&:did_insert_everything)
    for (size_t i = 0; i < 100; ++i)
    {
        did_insert_everything = did_insert_everything && searchNode(tree, i);
    }
}

CUNIT_TEST(thread_safe_deletion)
{
    TreeNode* tree = createNode(0);
    for (size_t i = 1; i < 100; ++i)
    {
        insertNode(tree, i);
    }
#pragma omp parallel for schedule(static, 6)
    for (size_t i = 0; i < 100; ++i)
    {
        if (i % 3 == 0)
        {
            deleteNode(tree, i);
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
            printf("i = %lu\n", i);
            CUNIT_ASSERT_TRUE(searchNode(tree, i));
        }
    }
}