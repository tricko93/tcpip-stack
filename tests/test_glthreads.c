#include "unity.h"
#include "../src/glthreads/glthreads.h"

// Define a structure for testing purposes
typedef struct {
    int data;
    glthread_node_t glnode;
} TestData;

// Set up a linked list for testing
static glthread_t linkedList;

static unsigned int offset;

void setUp(void)
{
    // Get the offset and keep it in private variable
    offset = offset(TestData, glnode);
    // Initialize the linked list and set the offset
    init_glthread(&linkedList, offset);
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

void test_glthread_remove(void) {
    // Create three nodes for testing
    TestData node1 = {1, {NULL, NULL}};
    TestData node2 = {2, {NULL, NULL}};
    TestData node3 = {3, {NULL, NULL}};

    // Add nodes to the linked list
    glthread_add(&linkedList, &node1.glnode);
    glthread_add(&linkedList, &node2.glnode);
    glthread_add(&linkedList, &node3.glnode);

    // Test case: Remove a node from the middle of the list (node2)
    glthread_remove(&linkedList, &node2.glnode);
    TEST_ASSERT_EQUAL_INT(3,
                          ((TestData *)GLTHREAD_GET_USER_DATA_FROM_OFFSET(
                                       linkedList.head,
                                       offset
                                       )
                          )->data
                         ); // Head should be node3
    TEST_ASSERT_EQUAL_INT(1,
                          ((TestData *)GLTHREAD_GET_USER_DATA_FROM_OFFSET(
                                       linkedList.head->right,
                                       offset
                                       )
                          )->data
                         ); // Next node should be node1

    // Test case: Remove the head of the list (node1)
    glthread_remove(&linkedList, &node1.glnode);
    TEST_ASSERT_EQUAL_INT(3,
                          ((TestData *)GLTHREAD_GET_USER_DATA_FROM_OFFSET(
                                       linkedList.head,
                                       offset
                                       )
                          )->data
                         ); // Head should be node3

    // Test case: Remove the last node in the list (node3)
    glthread_remove(&linkedList, &node3.glnode);
    TEST_ASSERT_NULL(linkedList.head);  // List should be empty
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_init_glthread);
    RUN_TEST(test_glthread_add_next);
    RUN_TEST(test_glthread_add);
    RUN_TEST(test_glthread_remove);

    return UNITY_END();
}
