#include "unity.h"
#include "../src/glthreads/glthreads.h"

void setUp(void)
{
    // Set up initial state before each test
}

void tearDown(void)
{
    // Clean up after each test
}

void test_init_glthread(void)
{
    glthread_t lst;
    init_glthread(&lst, 0);

    TEST_ASSERT_NULL(lst.head);
    TEST_ASSERT_EQUAL_INT(0, lst.offset);
}

void test_glthread_add_next(void)
{
    // Create three nodes
    glthread_node_t node1, node2, node3;

    node1.left = NULL;
    node1.right = NULL;

    node2.right = NULL;

    // Call the function to add node2 next to node1
    glthread_add_next(&node1, &node2);

    // Verify that node1's right points to node2
    TEST_ASSERT_EQUAL_PTR(node1.right, &node2);

    // Verify that node2's left points to node1
    TEST_ASSERT_EQUAL_PTR(&node1, node2.left);

    // Verify that node2's right is NULL
    TEST_ASSERT_NULL(node2.right);

    // Verify that node1's left is NULL
    TEST_ASSERT_NULL(node1.left);

    // Call the function to add node3 next to node2
    glthread_add_next(&node2, &node3);

    // Verify that node2's right points to node3
    TEST_ASSERT_EQUAL_PTR(&node3, node2.right);

    // Verify that node3's left points to node2
    TEST_ASSERT_EQUAL_PTR(&node2, node3.left);
}

void test_glthread_add(void)
{
    glthread_t lst;
    init_glthread(&lst, 0);

    TEST_ASSERT_NULL(lst.head);

    glthread_node_t new_node;
    glthread_add(&lst, &new_node);

    TEST_ASSERT_NOT_NULL(lst.head);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_init_glthread);
    RUN_TEST(test_glthread_add_next);
    RUN_TEST(test_glthread_add);

    return UNITY_END();
}
