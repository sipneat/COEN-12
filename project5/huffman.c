/*
 * File Name: huffman.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 03-08-2023
 * 
 * Description: This file defines functions that compress a file using Huffman coding. These functions include
 *              compare, mknode, depth, readFile, and the main driver function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;

int count[257];
NODE* nodes[257];

/* Function: compare
 * 
 * Description: compares data in 2 nodes
 * 
 * Big-O: O(1)
*/
static int compare(NODE *t1, NODE *t2)
{
    assert(t1 != NULL && t2 != NULL);
    return ((t1 -> count < t2 -> count) ? -1 : (t1 -> count > t2 -> count));
}

/* Function: mknode
 * 
 * Description: creates a new node for the tree
 * 
 * Big-O: O(1)
*/
static NODE* mknode(int data, NODE *left_node, NODE *right_node)
{
    NODE* new_node = malloc(sizeof(NODE));
    assert(new_node != NULL);
    new_node -> count = data;
    new_node -> parent = NULL;
    if (left_node != NULL)
    {
        left_node -> parent = new_node;
    }
    if (right_node != NULL)
    {
        right_node -> parent = new_node;
    }

    return new_node;
}

/* Function: depth
 * 
 * Description: calculates the depth of the tree from leaf to root
 * 
 * Big-O: O(n)
*/
static int depth(NODE* node)
{
    assert(node != NULL);
    if(node -> parent == NULL)
    {
        return 0;
    }

    return depth(node -> parent) + 1;
}

/* Function: readFile
 * 
 * Description: opens the input file and assigns each character a value
 * 
 * Big-O: O(n)
*/
static void readFile(char* fileName)
{
    FILE* infp = fopen(fileName, "r");
    if(infp == NULL)
    {
        printf("File Error\n");
        return;
    }

    int ch = getc(infp);
    while(ch != EOF)
    {
        count[ch]++;
        ch = getc(infp);
    }

    fclose(infp);

    return;
}

/* Function: main
 * 
 * Description: main driver function for the program
 * 
 * Big-O: O(n)
*/
int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        printf("Missing Files!\n");
        return 0;
    }
    else
    {
        readFile(argv[1]);
    }

    PQ* pq = createQueue(compare);
    int i;
    for (i = 0; i < 256; i++)
    {
        if (count[i] > 0)
        {
            nodes[i] = mknode(count[i], NULL, NULL);
            addEntry(pq, nodes[i]);
        }
    }
    nodes[256] = mknode(0, NULL, NULL);
    addEntry(pq, nodes[256]);

    while(numEntries(pq) > 1)
    {
        NODE* left = removeEntry(pq);
        NODE* right = removeEntry(pq);
        NODE* parent = mknode(left -> count + right -> count, left, right);
        addEntry(pq, parent);
    }

    int j;
    for (j = 0; j < 256; j++)
    {
        if (nodes[j] != NULL)
        {
            printf(isprint(j) ? "%c" : "%03o", j);
            printf(": %d x %d bits = %d bits\n", count[j], depth(nodes[j]), count[j] * depth(nodes[j]));
        }
    }

    pack(argv[1], argv[2], nodes);
    destroyQueue(pq);

    return 0;
}

