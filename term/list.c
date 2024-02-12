/*
 * File Name: list.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 03-15-2023
 * 
 * Description: This file defines functions that combines a linked list and array to implement stack and queue operations. 
 *              These functions include createNode, createList, destroyList, numItems, addFirst, addLast, removeFirst, removeLast,
 *              getItem, and setItem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct node
{
    void** data;       //* array for storing elements
    struct node* next; //* next node
    struct node* prev; //* previous node
    int length;        //* length of the array
    int count;         //* count of how many items are in the array
    int first;         //* first item in the array, not always 0 due to circular queue
}NODE;

typedef struct list
{
    int count;         //* count of number of nodes
    struct node* head; //* sentinel node
    int total;         //* count of number of total elements across all nodes
}LIST;

/* 
 * Function: createNode
 * 
 * Description: creates a node with an array of void elements
 * 
 * Big-O: O(1)
*/

static NODE *createNode(int length)
{
    NODE *np = malloc(sizeof(NODE));
    assert(np != NULL);
    np -> length = length;
    np -> count = 0;
    np -> first = 0;
    np -> data = malloc(sizeof(void*) * length);

    return np;
}

/* 
 * Function: createList
 * 
 * Description: creates a circular linked list with nodes
 * 
 * Big-O: O(1)
*/

LIST *createList(void)
{
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp -> head = createNode(8);
    lp -> count = 0;
    lp -> total = 0;
    lp -> head -> next = lp -> head;
    lp -> head -> prev = lp -> head;

    return lp;
}

/* 
 * Function: destroyList
 * 
 * Description: destroys a given linked list
 * 
 * Big-O: O(n)
*/

void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE* pDel;
    NODE* pPrev = lp -> head -> prev;

    while (pDel != lp -> head)
    {
        pDel = pPrev;
        pPrev = pDel -> prev;
        free(pDel);
    }

    free(lp);

    return;
}

/* 
 * Function: numItems
 * 
 * Description: returns the number of elements in the linked list
 * 
 * Big-O: O(1)
*/

int numItems(LIST *lp)
{
    assert(lp != NULL);

    return lp -> total;
}

/* 
 * Function: addFirst
 * 
 * Description: inserts an item into the first node or creates a new one if the node is full
 * 
 * Big-O: O(1)
*/

void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE* temp = lp -> head -> next;

    //* if the list is empty or the first node is full, create a new node
    if (lp -> count == 0 || temp -> count == temp -> length)
    {
        NODE* pNew = malloc(sizeof(NODE));
        pNew = createNode(((temp -> next -> length) * 2));
        pNew -> next = temp;
        pNew -> prev = temp -> prev;
        temp -> prev -> next = pNew;
        temp -> prev = pNew;
        lp -> count++;
        pNew -> data[0] = item;
        pNew -> count++;
        lp -> total++;

        return;
    }

    //* else add the item to the first node
    temp -> first = (temp -> first - 1 + temp -> length) % temp -> length;
    temp -> data[temp -> first] = item;
    temp -> count++;
    lp -> total++; 

    return;
}

/* 
 * Function: addlast
 * 
 * Description: inserts an item into the last node or creates a new one if the node is full
 * 
 * Big-O: O(n)
*/

void addLast(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE* temp = lp -> head -> prev;

    //* if the list is empty, create a new node
    if (lp -> count == 0)
    {
        NODE* pNew = malloc(sizeof(NODE));
        pNew = createNode(((temp -> prev -> length) * 2));
        pNew -> prev = temp -> prev;
        pNew -> next = temp;
        temp -> prev -> next = pNew;
        temp -> prev = pNew;
        lp -> count++;
        pNew -> data[0] = item;
        pNew -> count++;
        lp -> total++;
        return;
    }

    while(temp -> count == temp -> length)
    {
        temp = temp -> prev;
    }

    //* if the last node is full, create a new node
    if (temp == lp -> head)
    {
        NODE* pNew = malloc(sizeof(NODE));
        pNew = createNode(((temp -> prev -> length) * 2));
        pNew -> prev = temp -> prev;
        pNew -> next = temp;
        temp -> prev -> next = pNew;
        temp -> prev = pNew;
        lp -> count++;
        pNew -> data[0] = item;
        pNew -> count++;
        lp -> total++;
        return;
    }

    temp -> data[(temp -> first + temp -> count++) % temp -> length] = item;
    lp -> total++;
    return;
}

/* 
 * Function: removeFirst
 * 
 * Description: removes the first element in the node or deletes the node if it is empty
 * 
 * Big-O: O(1)
*/

void *removeFirst(LIST *lp)
{
    assert(lp != NULL);

    NODE* pDel = lp -> head -> next;
    void* localData = pDel -> data[pDel -> first % pDel -> length];

    pDel -> first++;
    pDel -> first = pDel -> first % pDel -> length;
    pDel -> count--;
    lp -> total--;

    if(pDel -> count == 0)
    {
        pDel -> prev -> next = pDel -> next;
        pDel -> next -> prev = pDel -> prev;
        free(pDel);
        lp -> count--;
    }

    return localData;
}

/* 
 * Function: removeLast
 * 
 * Description: removes the last element in the node or deletes the node if it is empty
 * 
 * Big-O: O(1)
*/

void *removeLast(LIST *lp)
{
    assert(lp != NULL);

    NODE* pDel = lp -> head -> prev;
    void* localData = pDel -> data[(pDel -> first + pDel -> count - 1) % pDel -> length];

    lp -> total--;
    pDel -> count--;

    if(pDel -> count == 0)
    {
        pDel -> next -> prev = pDel -> prev;
        pDel -> prev -> next = pDel -> next;
        free(pDel);
        lp -> count--;
    }

    return localData;
}

/* 
 * Function: getFirst
 * 
 * Description: returns the first element in the node
 * 
 * Big-O: O(1)
*/

void *getFirst(LIST *lp)
{
    assert(lp != NULL);

    NODE* pGet = lp -> head -> next;
    void* localData = pGet -> data[pGet -> first % pGet -> length];

    return localData;
}

/* 
 * Function: getLast
 * 
 * Description: returns the last element in the node
 * 
 * Big-O: O(1)
*/

void *getLast(LIST *lp)
{
    assert(lp != NULL && lp -> count > 0);

    NODE* pGet = lp -> head -> prev;
    void* localData = pGet -> data[(pGet -> first + pGet -> count - 1) % pGet -> length];

    return localData;
}

/* 
 * Function: getItem
 * 
 * Description: returns the element at the index given
 * 
 * Big-O: O(n)
*/

void *getItem(LIST *lp, int index)
{
    assert(lp != NULL);

    NODE* pGet = lp -> head -> next;

    while (pGet != lp -> head && pGet -> count <= index)
    {
        index = index - pGet -> count;
        pGet = pGet -> next;
    }

    void* localData = pGet -> data[(pGet -> first + index) % pGet -> length];

    return localData;
}

/* 
 * Function: setItem
 * 
 * Description: sets the element in the index given to the item given
 * 
 * Big-O: O(n)
*/

void setItem(LIST *lp, int index, void *item)
{
    assert(lp != NULL && item != NULL);

    NODE* pSet = lp -> head -> next;

    while(pSet != lp -> head && pSet -> count <= index)
    {
        index = index - pSet -> count;
        pSet = pSet -> next;
    }

    pSet -> data[(pSet -> first + index) % pSet -> length] = item;

    return;
}