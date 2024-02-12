/*
 * File Name: table.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 02-26-2023
 * 
 * Description: This file defines functions that modify an set of unknown types in a hash table in a variety of 
 *              ways defined by unique.c and parity.c. It contains a struct, createSet,
 *              destroySet, numElements, addElement, removeElement, findElement, and getElement.
 *              Note: Decided to use an int flag called copy instead of a boolean flag for determining if
 *              an element is already in this list, hence why it is missing. Uses functions from list.c so each
 *              element in the hash table is a linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"
#include "set.h"
#define alpha 20

struct set
{
    LIST **lists;
    int length;
    int count;
    int copy;
    int (*compare)();
    unsigned (*hash)();
};

/*
 * Function:    createSet
 * 
 * Complexity:  O(n)
 *
 * Description: Creates a set that returns a set pointer and takes a max number of elements.
 */

SET *createSet(int n, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *sp = malloc(sizeof(SET));
    assert(sp);
    sp -> compare = compare;
    sp -> hash = hash;
    sp -> length = n / alpha;
    sp -> count = 0;
    sp -> copy = 0;
    sp -> lists = malloc(sizeof(LIST*) * sp -> length);
    assert(sp -> lists);
    for (i = 0; i < sp -> length; i++)
    {
        sp -> lists[i] = createList(sp -> compare);
    }


    return sp;
}

/*
 * Function:    destroySet
 *
 * Complexity:  O(n)
 *
 * Description: Destroys a given set via freeing the pointer.
 */

void destroySet(SET* sp)
{
    assert(sp != NULL);
	int i;
	for(i = 0; i < sp->length; i++)
	{
    	destroyList(sp -> lists[i]);
	}
    
    free(sp->lists);
    free(sp);
    return;
}

/*
 * Function:    numElements
 *
 * Complexity:  O(1)
 *
 * Description: Returns the number of elements in a given set.
 */

int numElements(SET* sp)
{
    assert(sp != NULL);
    return sp -> count;
}

/*
 * Function:    addElement
 *
 * Complexity:  O(n)
 *
 * Description: Adds a given element to a given set and places it in the hash table using functions from list.c.
 */

void addElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int key = (sp -> hash)(elt) % sp -> length;

    if (findItem(sp -> lists[key], elt) == NULL)
    {
        addLast(sp -> lists[key], elt);
        sp -> count++;
    }

    return;
}

/*
 * Function:    removeElement
 *
 * Complexity:  O(n)
 *
 * Description: Removes a given element from a given set by using functions from list.c.
 */

void removeElement(SET* sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int key = (sp -> hash)(elt) % sp -> length;

    if (findItem(sp -> lists[key], elt) != NULL)
    {
        removeItem(sp -> lists[key], elt);
        sp -> count--;
    }

    return;
}

/*
 * Function:	findElement
 *
 * Complexity:  O(n)
 *
 * Description: Finds a given element in a given set. Returns NULL if it was not found. Uses functions from list.c
 */

void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int key = (sp -> hash)(elt) % sp -> length;

    if (findItem(sp -> lists[key], elt) == NULL)
    {
        return NULL;
    }

    return findItem(sp -> lists[key], elt);
}

/*
 * Function:	getElements
 *
 * Complexity:  O(n)
 *
 * Description: Allocates an array of elements in a set and returns it.
*/

void *getElements(SET* sp)
{
    assert(sp != NULL);
    int i, j, temp = 0;
    void **arr = malloc(sizeof(LIST*) * sp -> count);
    assert(arr != NULL);
    for (i = 0; i < sp -> length; i++)
    {
        void **tempList = getItems(sp -> lists[i]);
        for (j = 0; j < numItems(sp -> lists[i]); j++)
        {
            arr[temp] = tempList[j];
            temp++;
        }
    }

    return arr;
}