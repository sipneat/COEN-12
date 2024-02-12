/*
 * File Name: table.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 02-26-2023
 * 
 * Description: This file defines functions that modify an list of unknown types in a variety of 
 *              ways defined by radix.c and maze.c. It contains two structs, createList,
 *              destroyList, numItems, addFirst, addLast, removeFirst, removeLast, getFirst, getLast, removeItem, findItem, and getItems.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

typedef struct node
{
    void* data;
    struct node* next;
    struct node* prev;
}NODE;

typedef struct list
{
    int count;
    struct node* head;
    int (*compare)();
}LIST;

/*
 * Function:    createList
 * 
 * Complexity:  O(1)
 *
 * Description: Creates a list that returns a LIST pointer and takes a compare function.
 */

LIST *createList(int (*compare)())
{
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp -> count = 0;
    lp -> compare = compare;
    lp -> head = malloc(sizeof(NODE));
    assert(lp -> head != NULL);
    lp -> head -> prev = lp -> head;
    lp -> head -> next = lp -> head;

    return lp;
}

/*
 * Function:    destroyList
 * 
 * Complexity:  O(n)
 *
 * Description: Destroys a given list via freeing the pointer.
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
 * Function:    numElements
 *
 * Complexity:  O(1)
 *
 * Description: Returns the number of items in a given list.
 */

int numItems(LIST *lp)
{
    assert(lp != NULL);

    return lp -> count;
}

/*
 * Function:    addFirst
 *
 * Complexity:  O(1)
 *
 * Description: Adds a given item to a given list and places it at the front of the list.
 */

void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);

    NODE* pNew = malloc(sizeof(NODE));
    assert(pNew != NULL);

    pNew -> data = item;
    lp -> head -> next -> prev = pNew;
    pNew -> next = lp -> head -> next;
    pNew -> prev = lp -> head;
    lp -> head -> next = pNew;
    lp -> count++;

    return;
}

/*
 * Function:    addLast
 *
 * Complexity:  O(1)
 *
 * Description: Adds a given item to a given list and places it at the back of the list.
 */

void addLast(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);

    NODE* pNew = malloc(sizeof(NODE));
    assert(pNew != NULL);

    pNew -> data = item;
    lp -> head -> prev -> next = pNew;
    pNew -> next = lp -> head;
    pNew -> prev = lp -> head -> prev;
    lp -> head -> prev = pNew;
    lp -> count++;

    return;
}

/*
 * Function:    removeFirst
 *
 * Complexity:  O(1)
 *
 * Description: Removes a node from a given list at the front
 */

void *removeFirst(LIST *lp)
{
    assert(lp != NULL && lp -> count > 0);

    NODE* pDel = lp -> head -> next;
    void* localData = pDel -> data;

    lp -> head -> next = pDel -> next;
    pDel -> next -> prev = lp -> head;
    free(pDel);
    lp -> count--;

    return localData;
}

/*
 * Function:    removeLast
 *
 * Complexity:  O(1)
 *
 * Description: Removes a node from a given list at the back
 */

void *removeLast(LIST *lp)
{
    assert(lp != NULL && lp -> count > 0);

    NODE* pDel = lp -> head -> prev;
    void* localData = pDel -> data;

    lp -> head -> prev = pDel -> prev;
    pDel -> prev -> next = lp -> head;
    free(pDel);
    lp -> count--;

    return localData;
}

/*
 * Function:	getFirst
 *
 * Complexity:  O(1)
 *
 * Description: Returns the first item of the list
*/


void *getFirst(LIST *lp)
{
    assert(lp != NULL && lp -> count > 0);

    return lp -> head -> next -> data;
}

/*
 * Function:	getLast
 *
 * Complexity:  O(1)
 *
 * Description: Returns the last item of the list
*/


void *getLast(LIST *lp)
{
    assert(lp != NULL && lp -> count > 0);

    return lp -> head -> prev -> data;
}

/*
 * Function:    removeItem
 *
 * Complexity:  O(n)
 *
 * Description: Removes a given item from a given list
 */

void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL && (*lp -> compare) != NULL);

    NODE* pCur = lp -> head -> next;

    while (pCur != lp -> head)
    {
        if ((*lp -> compare)(pCur -> data, item) == 0)
        {
            pCur -> prev -> next = pCur -> next;
            pCur -> next -> prev = pCur -> prev;
            free(pCur);
            lp -> count--;
            break;
        }
        else
        {
            pCur = pCur -> next;
        }
    }

    return;
}

/*
 * Function:	findItem
 *
 * Complexity:  O(n)
 *
 * Description: Finds a given item in a given list. Returns NULL if it was not found.
 */

void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL && (*lp -> compare) != NULL);

    NODE* pCur = lp -> head -> next;

    while (pCur != lp -> head)
    {
        if ((*lp -> compare)(pCur -> data, item) == 0)
        {
            return pCur -> data;
        }
        else
        {
            pCur = pCur -> next;
        }
    }

    return NULL;
}

/*
 * Function:	getItems
 *
 * Complexity:  O(n)
 *
 * Description: Allocates an array of items in a list and returns it.
*/

void *getItems(LIST *lp)
{
    assert(lp != NULL);

    int i = 0;
    void** arr = malloc(sizeof(void*) * lp -> count);
    assert(arr != NULL);

    NODE* pCur = lp -> head -> next;

    while (pCur != lp -> head)
    {
        arr[i] = pCur -> data;
        pCur = pCur -> next;
        i++;
    }

    return arr;
}