/* -----------------------------------------------------------------------------
 * @file:        glthreads.h
 * @author:      Marko Trickovic (contact@markotrickovic.com)
 * @website:     www.markotrickovic.com
 * @date:        28/01/2024 01:30 PM
 * @license:     MIT
 * @description: This header file contains the declarations of the struct-s
 *               and functions related to doubly linked list (called glthreads).
 *
 *               Linked List is a basic data structure used in CS. Especially
 *               in the network development domain.
 *
 *               Header file contains:
 *               ---------------------
 *
 *               struct glthread_node_t
 *               struct glthread_t
 *
 *               glthread_add_next
 *               glthead_add
 *               init_glthread
 *
 * @note:        This code is part of the tcpip-stack project, which is a course
 *               on network development.
 *
 * Revision History:
 *
 * Revision 0.1: 28/01/2024 Marko Trickovic
 * Initial version that declares structures and function for doubly linked list.
 */

#ifndef GLTHREADS_H
#define GLTHREADS_H

/**
 * @brief:                The structure representing a generic linked list node.
 *
 * @struct:               glthread_t
 *
 * @param[in]: left       Pointer to the left node in the linked list.
 * @param[in]: right      Pointer to the right node in the linked list.
 */
typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node_ *right;
} glthread_node_t;

/**
 * @brief:                The structure represeting linked list.
 *
 * @struct:               glthread_t
 *
 * @param[in] head:       Pointer to the beginning of the Linked List.
 * @param[in] offset:     Offset for each element in the list.
 */
typedef struct glthread_ {
    glthread_node_t *head;
    unsigned int offset;
} glthread_t;

/**
 * @brief:                Adds a new node next to the current node.
 *
 * @param[in] curr_node:  Current node in the linked list.
 * @param[in] new_node:   New node to be added next to the current node.
 */
void glthread_add_next(glthread_node_t *curr_node, glthread_node_t *new_node);

/**
 * @brief:                Adds a node at the head of the Linked List.
 *
 * @param[in] lst:        Pointer to the Linked List.
 * @param[in] new_node:   New node to be added at the head of the Linked List.
 */
void glthread_add(glthread_t *lst, glthread_node_t *new_node);

/**
 * @brief:                Initializes head pointer and offset value.
 *
 * @param[in] lst:        Pointer to the Linked List.
 * @param[in] glnode:     New node to be added next to the current node.
 */
void init_glthread(glthread_t *lst, unsigned int offset);

#endif    // GLTHREADS_H
