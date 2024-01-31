/* -----------------------------------------------------------------------------
 * @file:        glthreads.h
 * @author:      Marko Trickovic (contact@markotrickovic.com)
 * @website:     www.markotrickovic.com
 * @date:        31/01/2024 05:30 PM
 * @license:     MIT
 * @description: This header file encapsulates declarations for managing a
 *               doubly linked list, referred to as glthreads. The contents are
 *               organized into three groups:
 *
 *                 1. Structs:
 *                    - struct glthread_node_t
 *                    - struct glthread_t
 *
 *                 2. Functions:
 *                    - glthread_add_next
 *                    - glthread_add
 *                    - init_glthread
 *                    - glthread_remove
 *
 *                 3. Macros:
 *                    - ITERATE_GL_THREADS_BEGIN
 *                    - offset
 *                    - glthread_node_init
 *                    - GLTHREAD_GET_USER_DATA_FROM_OFFSET
 *
 * @note:        This code is part of the tcpip-stack project, which is a course
 *               on network development.
 *
 * Revision History:
 *
 * Revision 0.1: 28/01/2024 Marko Trickovic
 * Initial version that declares structures and function for doubly linked list.
 *
 * Revision 0.2: 31/01/2024 Marko Trickovic
 * Added glthread_remove function, ITERATE_GL_THREADS_BEGIN, offset,
 * GLTHREAD_GET_USER_DATA_FROM_OFFSET and glthread_node_init macros.
 */

#ifndef GLTHREADS_H
#define GLTHREADS_H

#include <stdint.h>

/**
 * @brief      The structure representing a generic linked list node.
 *
 * @struct                glthread_node_t
 *
 * @param[in]  left       Pointer to the left node in the linked list.
 * @param[in]  right      Pointer to the right node in the linked list.
 */
typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node_ *right;
} glthread_node_t;

/**
 * @brief      The structure represeting linked list.
 *
 * @struct                glthread_t
 *
 * @param[in] head        Pointer to the beginning of the Linked List.
 * @param[in] offset      Offset for each element in the list.
 */
typedef struct glthread_ {
    glthread_node_t *head;
    unsigned int offset;
} glthread_t;

/**
 * @brief      Adds a new node next to the current node.
 *
 * @param[in]  curr_node  Current node in the linked list.
 * @param[in]  new_node   New node to be added next to the current node.
 */
void glthread_add_next(glthread_node_t *curr_node, glthread_node_t *new_node);

/**
 * @brief      Adds a node at the head of the Linked List.
 *
 * @param[in]  lst       Pointer to the Linked List.
 * @param[in]  new_node  New node to be added at the head of the Linked List.
 */
void glthread_add(glthread_t *lst, glthread_node_t *new_node);

/**
 * @brief      Removes a node from the Linked List.
 *
 * @param      lst             Pointer to the Linked List.
 * @param      node_to_delete  Node to be deleted.
 */
void glthread_remove(glthread_t *lst, glthread_node_t *node_to_delete);

/**
 * @brief      Initializes head pointer and offset value.
 *
 * @param[in]  lst     Pointer to the Linked List.
 * @param[in]  offset  New node to be added next to the current node.
 */
void init_glthread(glthread_t *lst, unsigned int offset);

/**
 * @brief      Macro to iterate over a Generic Linked List.
 *
 * @param[in]  lstptr       Pointer to the Linked List.
 * @param[in]  struct_type  The type of the structure containing the linked list
 *                          node.
 * @param[out] ptr          Pointer to iterate over each element in the linked
 *                          list.
 */
#define ITERATE_GL_THREADS_BEGIN(lstptr, struct_type, ptr)                \
{                                                                         \
    glthread_node_t *_current_node = NULL, *_next_node = NULL;            \
    for (_current_node = lstptr->head;                                    \
         _current_node;                                                   \
         _current_node = _next_node)                                      \
    {                                                                     \
        _next_node = _current_node->right;                                \
        ptr = (struct_type *)((char *)_current_node - lstptr->offset);
#define ITERATE_GL_THREADS_ENDS }}

/**
 * @brief      Calculate the offset of a specific field within a structure.
 *
 * @details    This macro takes the name of a structure and the name of a field
 *             within that structure and computes the offset of the field in
 *             bytes. It achieves this by casting a null pointer to a pointer
 *             of the specified structure type and then obtaining the address
 *             of the specified field within the structure.
 *
 * @param[in]  struct_name  The name of the structure.
 * @param[in]  field_name   The name of the field within the structure.
 *
 * @return     The offset of the specified field within the structure in bytes,
 *             cast to uintptr_t.
 */
#define offset(struct_name, field_name)   \
    (uintptr_t)&(((struct_name *)0)->field_name)

/**
 * @brief      Retrieves the user data pointer from a glthread node pointer and
 *             offset.
 *
 * @details    This macro calculates the user data pointer by subtracting the
 *             specified offset from the given glthread node pointer.
 *
 * @param[in]  glthreadptr  Pointer to the glthread node.
 * @param[in]  offset       Offset value used to compute the user data pointer.
 *
 * @return     A void pointer to the user data associated with the glthread
 *             node.
 */
#define GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthreadptr, offset)  \
    (void *)((char *)(glthreadptr) - offset)

/**
 * @brief      Initialize a Generic Linked List node.
 *
 * @details    This macro sets the left and right pointers of a given Generic
 *             Linked List node (`node`) to NULL, effectively initializing it
 *             for use in a linked list.
 *
 * @param[in]  node  Pointer to the Generic Linked List node to be initialized.
 */
#define glthread_node_init(node)    \
    node->left = NULL;              \
    node->right = NULL;

#endif    // GLTHREADS_H
