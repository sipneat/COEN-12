/*
 * File Name: pqueue.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 03-05-2023
 * 
 * Description: This file defines functions that modify an list of unknown types in a variety of 
 *              ways defined by sort.c. It uses a priority queue to do this. It contains a struct pqueue, 
 *              createQueue, destroyQueue, numEntries, addEntry, and removeEntry
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

#define INIT_LENGTH 10
#define p(x) (((x) - 1) / 2)
#define l(x) ((x) * 2 + 1)
#define r(x) ((x) * 2 + 2)

typedef struct pqueue
{
    int count;
    int length;
    void **data;
    int (*compare)();
}PQ;

/* Function: createQueue
 * 
 * Description: Creates a new queue
 * 
 * Big-O: O(1)
*/
PQ *createQueue(int (*compare)())
{
    PQ *pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq -> count = 0;
    pq -> length = INIT_LENGTH;
    assert(compare != NULL);
    pq -> compare = compare;
    pq -> data = malloc(sizeof(void*) * INIT_LENGTH);
    assert(pq -> data != NULL);

    return pq;
}

/* Function: destroyQueue
 * 
 * Description: Destroys a given queue
 * 
 * Big-O: O(n)
*/
void destroyQueue(PQ *pq)
{
    assert(pq != NULL);
    int i;
    for (i = 0; i < pq -> count; i++)
    {
        free(pq -> data[i]);
    }
    free(pq -> data);
    free(pq);

    return;
}

/* Function: numEntries
 * 
 * Description: Returns the number of entries in the queue
 * 
 * Big-O: O(1)
*/
int numEntries(PQ *pq)
{
    assert(pq != NULL);

    return pq -> count;
}

/* Function: addEntry
 * 
 * Description: Creates a new entry in the queue
 * 
 * Big-O: O(n)
*/
void addEntry(PQ *pq, void *entry)
{
    assert(pq != NULL && entry != NULL);

    if (pq -> count == pq -> length)
    {
        pq -> length *= 2;
        pq -> data = realloc(pq -> data, sizeof(void*) * pq -> length);
        assert(pq -> data != NULL);
    }
    
    pq -> data[pq -> count] = entry;

    int locate = pq -> count;
    while (pq -> count != 0 && (*pq -> compare)(pq -> data[p(locate)], pq -> data[locate]) > 0)
    {
        void *temp = pq -> data[locate];
        pq -> data[locate] = pq -> data[p(locate)];
        pq -> data[p(locate)] = temp;
        locate = p(locate);
    }
    pq -> count++;

    return;
}

/* Function: addEntry
 * 
 * Description: Removes the first entry in the queue
 * 
 * Big-O: O(n)
*/
void *removeEntry(PQ *pq)
{
    assert(pq != NULL);

    void *start = pq -> data[0];
    pq -> data[0] = pq -> data[pq -> count - 1];
    int locate = 0; 
    int smallest = 0;
    while (l(locate) <= pq -> count - 1)
    {
        smallest = l(locate);
        if (r(locate) <= pq -> count - 1)
        {
            if ((*pq -> compare)(pq -> data[r(locate)], pq -> data[l(locate)]) < 0)
            {
                smallest = r(locate);
            }
        }

        if ((*pq -> compare)(pq -> data[locate], pq -> data[smallest]) < 0)
        {
            break;
        }
        else
        {
            void *temp = pq -> data[locate];
            pq -> data[locate] = pq -> data[smallest];
            pq -> data[smallest] = temp;
            locate = smallest;
        }
        locate = smallest;
    }
    pq -> count--;

    return start;
}
