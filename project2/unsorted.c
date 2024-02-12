/*
 * File Name: unsorted.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 01-18-2023
 * 
 * Description: This file defines functions that modify an unsorted set in a variety of 
 *              ways defined by unique.c and parity.c. It contains a struct, createSet,
 *              destroySet, numElements, search, addElement, removeElement, findElement, and getElement.
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
 * Complexity:  O(n)
 *
 * Description: Search function used by other functions in this file. 
 *              If a matching element is found, if it returns its location, 
 *              otherwise it returns the end of the set.
 */

static int search(SET *sp, char *str) //O(n)
{
    int i;
    for (i = 0; i < sp -> count; i++)
    {
        if (strcmp(sp -> elts[i], str) == 0)
        {
            return i;
        }
    }

    return sp -> count;
}

/*
 * Function:    addElement
 *
 * Complexity:  O(1)
 *
 * Description: Adds a given element to a given set.
 */

void addElement(SET *sp, char *str)
{
    if (search(sp, str) == sp -> count)
    {
        sp -> elts[sp -> count++] = strdup(str);
    }

    return;
}

/*
 * Function:    removeElement
 *
 * Complexity:  O(1)
 *
 * Description: Removes a given element from a given set.
 */

void removeElement(SET* sp, char *str)
{
    int i = search(sp, str);

    if (i < sp -> count)
    {
        sp -> elts[i] = sp -> elts[sp -> count - 1]; 
        sp -> count--;
    }

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

    if (i < sp -> count)
    {
        return sp -> elts[i];
    }

    return NULL;
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
