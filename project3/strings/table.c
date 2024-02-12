/*
 * File Name: table.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 02-01-2023
 * 
 * Description: This file defines functions that modify an set in a hash table in avariety of 
 *              ways defined by unique.c and parity.c. It contains a struct, createSet,
 *              destroySet, numElements, strhash, search, addElement, removeElement, findElement, and getElement.
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
    char** elts;
    int length;
    int count;
    int copy;
    char *flags;
};

/*
 * Function:    createSet
 * 
 * Complexity:  O(n)
 *
 * Description: Creates a set that returns a set pointer and takes a max number of elements.
 */

SET *createSet(int n)
{
    int i;
    SET *sp = malloc(sizeof(SET));
    assert(sp);
    sp -> elts = malloc(sizeof(char*) * n);
    assert(sp -> elts);
    sp -> length = n;
    sp -> count = 0;
    sp -> copy = 0;
    sp -> flags = malloc(sizeof(char) * n);
    assert(sp -> flags);
    for (i = 0; i < n; i++)
    {
        sp -> flags[i] = 'E';
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
	for(i = 0; i < sp->count; i++)
	{
    	if(sp->flags[i] == 'F')
        {
        	free(sp->elts[i]);
        }
	}
    
    free(sp->elts);
    free(sp->flags);
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
 * Function:    strhash
 *
 * Complexity:  O(1)
 *
 * Description: Hash function, provided in the lab documentation.
 */

unsigned strhash(char *str)
{
    unsigned hash = 0;

    while (*str != '\0')
    {
        hash = 31 * hash + *str++;
    }

    return hash;
}

/*
 * Function:    search
 *
 * Complexity:  O(n)
 *
 * Description: Search function used by other functions in this file. 
 *              Searches the hash table, returning the location and
 *              copy flag.
 */

static int search(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    int i, index;
    int first = -1;
    sp -> copy = 0;
    unsigned key = strhash(elt);

    for(i = 0; i < sp -> length; i++)
    {
        index = (key + i) % sp->length;
       	if(sp -> flags[index] == 'F')
        {
            	if (strcmp(elt, sp->elts[index]) == 0)
            	{
                	sp -> copy = 1;
                	return index;
            	}
        }

        if(sp->flags[index] == 'D')
        {
            first = index;
        }

        if(sp->flags[index] == 'E')
        {
            if(first > -1)
            {
            	return first;
            }
            return index;
        }
    }

    return -1;
}

/*
 * Function:    addElement
 *
 * Complexity:  O(n)
 *
 * Description: Adds a given element to a given set and places it in the hash table.
 */

void addElement(SET *sp, char *str)
{
    assert(sp != NULL && str != NULL);
    int index = search(sp, str);
    if (sp -> copy == 0)
    {
        assert(sp -> count < sp-> length);
        char *temp = strdup(str);
        assert(temp != NULL);
        sp -> elts[index] = temp;
        sp -> flags[index] = 'F';
        sp -> count++;
    }

    return;
}

/*
 * Function:    removeElement
 *
 * Complexity:  O(n)
 *
 * Description: Removes a given element from a given set and marks the index in the hash as deleted to be rewritten later.
 */

void removeElement(SET* sp, char *str)
{
    assert(sp != NULL && str != NULL);
    int index = search(sp, str);

    if (sp -> copy == 0)
    {
        return;
    }
    
    free(sp -> elts[index]);
    sp -> flags[index] = 'D';
    sp -> count--;

    return;
}

/*
 * Function:	findElement
 *
 * Complexity:  O(n)
 *
 * Description: Finds a given element in a given set. Returns NULL if it was not found.
 */

char *findElement(SET *sp, char *str)
{
    assert(sp != NULL && str != NULL);
    int index = search(sp, str);

    if (sp -> copy == 0)
    {
        return NULL;
    }

    return sp -> elts[index];
}

/*
 * Function:	getElements
 *
 * Complexity:  O(n)
 *
 * Description: Allocates an array of elements in a set and returns it.
*/

char **getElements(SET* sp)
{
    assert(sp != NULL);
    int i, j = 0;
    char **arr = malloc(sizeof(char*) * sp -> count);
    assert(arr);
    for (i = 0; i < sp -> length; i++, j++)
    {
        if (sp -> flags[i] != 'F')
        {
            j--;
            continue;
        }
        arr[j] = sp -> elts[i];
    }

    return arr;
}