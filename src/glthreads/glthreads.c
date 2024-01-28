/******************************************************************************
 * @file:        glthreads.c
 * @author:      Marko Trickovic (contact@markotrickovic.com)
 * @website:     www.markotrickovic.com
 * @date:        28/01/2024 02:30 PM
 * @license:     MIT
 * @language:    C
 * @platform:    x86_64
 * @description: This file contains the functions that are invoked to do the
 *               initialization of glthread, adding new node to glthread at
 *               the first position, adding new node at the last position.
 **
 * Revision 0.1: 28/01/2024 Marko Trickovic
 * Initial version that initializes glthread, adds node to the glthread.
 *****************************************************************************/

#ifndef GLTHREADS_C
#define GLTHREADS_C

#include "glthreads.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief      Private function to add a new_node right after curr_node.
 *
 * @param      curr_node  The curr node
 * @param      new_node   The new node
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
 * @brief      Function to insert into a glthread at the first position.
 *
 * @param      lst     The list
 * @param      new_node  The new node
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
 * @brief      Initializes the glthread.
 *
 * @param      lst     The list
 * @param[in]  offset  The offset
 */
void init_glthread(glthread_t *lst, unsigned int offset)
{
    lst->head = NULL;
    lst->offset = offset;
}

#endif    // GLTHREADS_C
