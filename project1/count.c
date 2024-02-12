/*
 * File Name: count.c
 * 
 * Author: Jake Esperson
 * 
 * Date: 01-11-2023
 * 
 * Description: Counts the number of words given a text file. Outputs the total number of words.
 */

#include <stdio.h>
#include <assert.h>
#define MAX_WORD_LENGTH 30 

/*
 * Function: countWords
 *
 * Description: Counts the number of words in the text file passed from main. Returns the total amount of words. Runtime: O(n)
 */

int countWords(FILE* infp)
{
    int count = 0;
    char x[MAX_WORD_LENGTH];

    while(fscanf(infp, "%s", x) != EOF) 
    {
        count++;
    }

    return count;
}

/*
 * Function: main
 *
 * Description: driver function. opens file defined by user and outputs the total number of words at the end. Errors if the user does not enter a valid file name. Runtime: O(n)
 */

int main(int argc, char* argv[]) 
{
    FILE* infp = fopen(argv[1], "r");
    assert(infp != NULL);
    int total = countWords(infp);

    printf("%d total words\n", total); 

    return 0;
}
