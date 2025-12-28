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
    /*
     * This does not test cases in which the root is deleted. This would be impossible to check, as we don't support that functionality
     * To support this functionality, one would have to use a fake-parent for the root node, which can actually be locked and unlocked.
     */
#pragma omp parallel for schedule(static, 6)
    for (size_t i = 1; i < 100; ++i)
    {
        if (i % 3 == 0)
        {
            deleteNode(tree, i);
        }
    }

    CUNIT_ASSERT_TRUE(is_valid_tree(tree));
    for (size_t i = 1; i < 100; ++i)
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

CUNIT_TEST(thread_safe_search)
{
    TreeNode* tree = createNode(0);
    for (size_t i = 1; i < 100; ++i)
    {
        if (i % 3 == 0)
        {
            insertNode(tree, i);
        }
    }

    size_t N = 100;
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp taskloop nogroup
            for (size_t i = 1; i < N; i++)
            {
                if (i % 3 != 0)
                {
                    insertNode(tree, i);
                }
            }

            #pragma omp taskloop nogroup
            for (size_t j = 1; j < N; j++)
            {
                deleteNode(tree, j);
            }

            #pragma omp taskloop nogroup
            for (size_t k = 1; k < N; k++)
            {
                searchNode(tree, k);
            }
        }
    }
}

CUNIT_TEST(thread_safe_find_min)
{
    TreeNode* tree = createNode(0);
    for (size_t i = 1; i < 100; ++i)
    {
        if (i % 3 == 0)
        {
            insertNode(tree, i);
        }
    }

    size_t N = 100;
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp taskloop nogroup
            for (size_t i = 1; i < N; i++)
            {
                if (i % 3 != 0)
                {
                    insertNode(tree, i);
                }
            }

            #pragma omp taskloop nogroup
            for (size_t j = 1; j < N; j++)
            {
                deleteNode(tree, j);
            }

            #pragma omp taskloop nogroup
            for (size_t k = 1; k < N; k++)
            {
                searchNode(tree, k);
            }

            #pragma omp taskloop nogroup
            for (size_t l = 1; l < N; l++)
            {
                findMin(tree);
            }
        }
    }
}

CUNIT_TEST(thread_safe_traversal)
{
    TreeNode* tree = createNode(0);
    for (size_t i = 1; i < 100; ++i)
    {
        if (i % 3 == 0)
        {
            insertNode(tree, i);
        }
    }

    size_t N = 100;
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp taskloop nogroup
            for (size_t i = 1; i < N; i++)
            {
                if (i % 3 != 0)
                {
                    insertNode(tree, i);
                }
            }

            #pragma omp taskloop nogroup
            for (size_t j = 1; j < N; j++)
            {
                deleteNode(tree, j);
            }

            #pragma omp taskloop nogroup
            for (size_t k = 1; k < N; k++)
            {
                searchNode(tree, k);
            }

            #pragma omp taskloop nogroup
            for (size_t l = 1; l < N; l++)
            {
                findMin(tree);
            }

            #pragma omp taskloop nogroup
            for (size_t b = 1; b < N; b++)
            {
                if (b % 3 == 0)
                {
                    inorderTraversal(tree);
                }
                else if (b % 3 == 1)
                {
                    preorderTraversal(tree);
                }
                else
                {
                    postorderTraversal(tree);
                }
            }
        }
    }
}