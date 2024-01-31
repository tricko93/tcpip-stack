/******************************************************************************
 * @file:        glthreads.c
 * @author:      Marko Trickovic (contact@markotrickovic.com)
 * @website:     www.markotrickovic.com
 * @date:        31/01/2024 05:30 PM
 * @license:     MIT
 * @language:    C
 * @platform:    x86_64
 * @description: This file contains functions for initializing and manipulating
 *               a generic linked list (glthread). The latest revision (0.2)
 *               introduces the glthread_remove function, enabling the removal
 *               of a specified node from the Linked List.
 *
 *               Functions in this file:
 *                 - glthread_add_next
 *                 - glthread_add
 *                 - init_glthread
 *                 - glthread_remove
 *
* @note:         This code is part of the tcpip-stack project, a course on
 *               network development.
 *
 * Revision 0.1: 28/01/2024 Marko Trickovic
 * Initial version that initializes glthread, adds node to the glthread.
 *
 * Revision 0.2: 31/01/2024 Marko Trickovic
 * Added glthread_remove function for removing a node from the Linked List.
 *****************************************************************************/

#ifndef GLTHREADS_C
#define GLTHREADS_C

#include "glthreads.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief      Adds a new node next to the current node.
 *
 * @param      curr_node  Current node in the linked list.
 * @param      new_node   New node to be added next to the current node.
 */
void glthread_add_next(glthread_node_t *curr_node, glthread_node_t *new_node)
{
    if (!curr_node || !new_node)
        return;

    if (!curr_node->right) {
        curr_node->right = new_node;
        new_node->left = curr_node;
        return;
    }

    glthread_node_t *temp = curr_node->right;
    curr_node->right = new_node;
    new_node->left = curr_node;
    new_node->right = temp;
    temp->left = new_node;
}

/**
 * @brief      Adds a node at the head of the Linked List.
 *
 * @param      lst       Pointer to the Linked List.
 * @param      new_node  New node to be added at the head of the Linked List.
 */
void glthread_add(glthread_t *lst, glthread_node_t *new_node)
{
    new_node->left = NULL;
    new_node->right = NULL;

    if (!lst->head) {
        lst->head = new_node;
        return;
    }

    glthread_node_t *head = lst->head;
    glthread_add_next(new_node, head);
    lst->head = new_node;
}

/**
 * @brief      Removes a node from the Linked List.
 *
 * @param      lst             Pointer to the Linked List.
 * @param      node_to_delete  Node to be deleted.
 */
void glthread_remove(glthread_t *lst, glthread_node_t *node_to_delete) {
    glthread_node_t *tmp = NULL;
    glthread_node_t *prev = NULL;
    void *element_ptr = NULL;

    ITERATE_GL_THREADS_BEGIN(lst, void, element_ptr)
    {
        tmp = (glthread_node_t *)((char *)element_ptr + lst->offset);

        if (tmp == node_to_delete) {
            // Found the node, remove it from the linked list
            if (prev != NULL) {
                // If the node is not the head of the list, update the previous node's 'right' pointer
                prev->right = tmp->right;
            } else {
                // If the node is the head of the list, update the list's 'head' pointer
                lst->head = tmp->right;
                if (lst->head != NULL) {
                    // If the list is not empty, update the left pointer of the new head
                    lst->head->left = NULL;
                }
            }

            break;
        }

        // Update 'prev' to keep track of the previous node
        prev = tmp;
    }
    ITERATE_GL_THREADS_ENDS;
}

/**
 * @brief      Initializes head pointer and offset value.
 *
 * @param      lst     Pointer to the Linked List.
 * @param[in]  offset  New node to be added next to the current node.
 */
void init_glthread(glthread_t *lst, unsigned int offset)
{
    lst->head = NULL;
    lst->offset = offset;
}

#endif    // GLTHREADS_C
