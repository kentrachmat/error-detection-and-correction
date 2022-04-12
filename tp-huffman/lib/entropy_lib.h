#ifndef ENTROPY_H
#define ENTROPY_H
#include <stdio.h>

/**
 * Describes the entropy of a file with its total size and its entropy.
 */
struct file_stat {
  int size;                     /* Total number of bytes in the file */
  float entropy;                /* Entropy of the file */
};


/**
 * Counts the occurrences of all the characters in the file given as the first
 * parameter (the FILE pointer was obtained with the fopen function) and puts
 * all the counts in the counts array.  
 *
 * @param file: A file opened in read mode
 * @param counts: The counts array must be of size 256,
 * and all cells must initially be at 0.
 * @post the `counts` array will contain the number of occurrences of each symbol
 *       (ie. counts[i] contains the number of occurrences of symbol i).
 */
void count_occurrences(FILE *file, int counts[]);

/**
 * Computes the entropy according to the symbol occurrences.
 *
 * @param counts: an array of 256 cells that contains the number of occurrences of each of the
 *        256 bytes.
 * @return a data structure containing the entropy information of the file.
 */
struct file_stat entropy(int counts[]);
#endif
