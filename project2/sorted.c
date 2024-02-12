/*
 * File Name: sorted.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 01-23-2023
 * 
 * Description: This file defines functions that modify an alphabetically sorted set in a variety of 
 *              ways defined by unique.c and parity.c. It contains a struct, createSet,
 *              destroySet, numElements, search, addElement, removeElement, findElement, and getElement.
 *              Note: Decided to use an int flag called copy instead of a boolean flag for determining if
 *              an element is already in this list, hence why it is missing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"

struct set
{
    char **elts;
    int length;
    int count;
    int copy;
};

/*
 * Function:    createSet
 * 
 * Complexity:  O(1)
 *
 * Description: Creates a set that returns a set pointer and takes a max number of elements.
 */

SET *createSet(int n)
{
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp);
    sp -> elts = malloc(sizeof(char*) * n);
    assert(sp -> elts);
    sp -> length = n;
    sp -> count = 0;
    sp -> copy = 0;

    return sp;
}

/*
 * Function:    destroySet
 *
 * Complexity:  O(1)
 *
 * Description: Destroys a given set via freeing the pointer.
 */

void destroySet(SET* sp)
{
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
    return sp -> count;
}

/*
 * Function:    search
 *
 * Complexity:  O(log(n))
 *
 * Description: Search function used by other functions in this file. 
 *              Conducts a binary search of the set, returning the location
 *              of the element if found, returns the first index if not.
 */

static int search(SET *sp, char *str)
{
    int first = 0;
    int last = sp -> count - 1;
    int mid, compare;

    while (first <= last)
    {
        mid = first + (last - first) / 2;
        compare = strcmp(sp -> elts[mid], str);

        if (compare == 0) 
        {
            sp -> copy = 1;
            return mid;
        } 
        else if (compare < 0) 
        {
            first = (mid + 1);
        }
        else 
        {
            last = (mid - 1);
        }
    }

    sp -> copy = 0;
    return first;
}

/*
 * Function:    addElement
 *
 * Complexity:  O(n)
 *
 * Description: Adds a given element to a given set and places it in alphabetical order.
 */

void addElement(SET *sp, char *str)
{
    int i = search(sp, str);
    if (sp -> copy == 1)
    {
        return;
    }
    int j = sp -> count;

    while (j >= i)
    {
        sp -> elts[j + 1] = sp -> elts[j];
        j--;
    }
    sp -> elts[j + 1] = strdup(str);
    sp -> count++;

    return;
}

/*
 * Function:    removeElement
 *
 * Complexity:  O(n)
 *
 * Description: Removes a given element from a given set and keeps the alphabetical sort.
 */

void removeElement(SET* sp, char *str)
{
    int i = search(sp, str);
    if (sp -> copy == 0)
    {
        return;
    }
    int j;

    for (j = i; j < sp -> count - 1; j++)
	{
		sp -> elts[j] = sp -> elts[j + 1];
	}
	sp -> count--;

    return;
}

/*
 * Function:	findElement
 *
 * Complexity:  O(1)
 *
 * Description: Finds a given element in a given set. Returns NULL if it was not found.
 */

char *findElement(SET *sp, char *str)
{
    int i = search(sp, str);
    if (sp -> copy == 0)
    {
        return NULL;
    }

    return sp -> elts[i];
}

/*
 * Function:	getElements
 *
 * Complexity:  O(1)
 *
 * Description: Allocates an array of elements in a set and returns it.
*/

char **getElements(SET* sp)
{
    char **arr = malloc(sizeof(char*) * sp -> count);
    assert(arr);
    memcpy(arr, sp -> elts, sizeof(char*) * sp -> count);

    return arr;
}
