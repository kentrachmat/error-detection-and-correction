#ifndef HUFFMAN_ALGO_H
#define HUFFMAN_ALGO_H

#include <stdio.h>

#define min(a, b) (((a)<(b)) ? (a) : (b))

#include "bitarray.h"
#include "huffman_tree.h"

/**
 * A structure used for the Huffman algorithm
 */
typedef struct {
  huffman_tree *node1;          /* `node1` and `node2` are two nodes with */
  huffman_tree *node2;          /* the minimal number of occurrences */
  int nb_leaves;                /* gives the number of leaves among `node1` and `node2` */
  int nb_nodes;                  /* gives the number of nodes among `node1` and `node2` */
} min_nodes;

/**
 * Creates a Huffman forest from a table of symbol occurrences
 *
 * @param occurrences: occurrences of each symbol (the array is of size ALPHABET_SIZE)
 * @param forest: a table of `HuffmanTree *`
 * @pre  `forest` has at least ALPHABET_SIZE cells, each initialized to NULL
 * @post The table `forest` contains a Huffman leaf for each symbol that is counted
 *       at least once in the table `occurrences`. In `forest` all the entries are consecutive.
 *       If there are 100 huffman leaves stored in `forest` their positions range
 *       from positions 0 to 99. The remaining cells (from position 100 to 255 are NULL).
 * @return the size of the forest (ie. the number of leaves stored in forest)
 */
int create_huffman_forest(int occurrences[], huffman_tree * forest[]);


/**
 * Sorts a Huffman forest by descending order of number of occurrences of the leaves.
 *
 * @param forest: an array of Huffman trees of ALPHABET_SIZE cells, the ones from position 0 to size-1
 *        contain a Huffman tree.
 * @param size: the size of the forest (ie. the number of non-NULL cells in forest)
 * @post forest[0]->nb_occurrences >= forest[1]->nb_occurrences >= … >= forest[size-1]->nb_occurrences
 */
void sort_huffman_forest(huffman_tree *forest[], int size);

/**
 * Return the two minimal nodes amonth the ones in `leaves` and `nodes`
 *
 * @param leaves: An array of ALPHABET_SIZE cells storing leaves in descending order of their 
 *        number of occurrences.
 * @param nb_leaves: The number of leaves in `leaves` that have not already been used.
 *        `leaves[nb_leaves-1]` is thus the leaf with the minimal number of occurrences
 * @param nodes: An array of ALPHABET_SIZE cells storing nodes in ascending order of their number
 *        of occurrences
 * @param pos_nodes: The position of the first node in `nodes` not already used.
 *        The first node is the one with the minimal number of occurrences.
 * @param nb_nodes: The number of nodes in `nodes` that have not already been used.
 */
min_nodes get_min_nodes(huffman_tree *leaves[], int nb_leaves,
                        huffman_tree *nodes[], int pos_nodes, int nb_nodes); 

/**
 * Creates a Huffman tree from the forest given in parameter.
 * Implements the Huffman algorithm.
 *
 * @param leaves: an array containing at most ALPHABET_SIZE Huffman tree leaves, ordered by descending order of number of occurrences
 * @param size: number of leaves in the array `leaves`
 * @return A final Huffman tree, resulting from the Huffman algorithm.
 */
huffman_tree *build_huffman_tree(huffman_tree *leaves[], int size);

/**
 * Get the Huffman code associated to each symbol
 *
 * @param tree: the tree in which we should get the Huffman code
 * @param codes: an array of bitarrays. codes[i] contains a bitarray representing
 * the code for symbol i. 
 * @pre The array `codes` must be created and have at least ALPHABET_SIZE cells, 
 * with an initialised `bitarray256_t*` in each cell.
 */
void create_huffman_coding(huffman_tree *tree, bitarray256_t *codes[]);

/**
 * Write the occurrences in the specified file
 * 
 * @param counts: the occurrences of each symbol in a table of counts
 * @param output: a file opened in write mode
 * @post Writes in the file the size of the alphabet on an integer and then writes
 * one symbol (one byte), followed by its number of occurrences (>0) on the size of an integer.
 */
void write_occurrences(int counts[], FILE *output);

/**
 * Read the occurrences in the specified file
 * 
 * @param input: a file opened in read mode
 * @param counts: the occurrences of each symbol in a table of counts
 * @pre `counts` contains at least ALPHABET_SIZE cells.
 * The file must have been written with `write_occurrences()`.
 * @post The array `counts` is filled with the occurrences read in the file.
 * The function stops reading the file when it read all the symbols.
 * The function sets in the `counts` array the count of each symbol found in the input file.
 * It doesn't modify the count of other symbols.
 */
void read_occurrences(FILE *input, int counts[]);

/**
 * Code the input file and puts the result in the output file.
 * 
 * @param input: input file, opened in read mode
 * @param output: output file, opened in write mode
 * @param codes: An array of (at least) ALPHABET_SIZE cells corresponding
 * to the code of each symbol (as produced by `create_huffman_coding()` 
 * for instance.
 */
void code_file(FILE *input, FILE *output, bitarray256_t *codes[]);

/**
 * Decode the input file in the output file, using the provided Huffman tree.
 *
 * @param input: input file, compressed with a Huffman coding, opened in read mode.
 * @param output: output file, opened in write mode
 * @param tree: Huffman Tree of the Huffman coding used to compress the input file
 * @param size: number of symbols to be decompressed
 * @pre The cursor in the input file is at the beginning of the compressed data.
 */
void huffman_decode_file(FILE *input, FILE *output, huffman_tree *tree, int size);

/**
 * Huffman code an input file in an output file
 *
 * @param in_filename: filename of the input file
 * @param out_filename: filename of the output file
 * @param verbose: if set to a value corresponding to true, will print the Huffman tree
 */
void huffman_coding(char *in_filename, char *out_filename, int verbose);

/**
 * Huffman decode an input file in an output file
 *
 * @param in_filename: filename of the input file
 * @param out_filename: filename of the output file
 * @param verbose: if set to a value corresponding to true, will print the Huffman tree
 */
void huffman_decoding(char *in_filename, char *out_filename, int verbose);
#endif
