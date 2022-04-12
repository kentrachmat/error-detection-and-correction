#include<stdio.h>
#include<stdlib.h>

#include "lib/entropy_lib.h"
#include "lib/bitarray.h"
#include "lib/huffman_algo.h"
#include "lib/huffman_tree.h"

int main(int argc, char **argv) {

  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("Cannot open the input file");
    exit(1);
  }
  int counts[ALPHABET_SIZE];
  int i;
  for (i = 0; i < ALPHABET_SIZE; i++) {
    counts[i] = 0;
  }

  count_occurrences(file, counts);
  fclose(file);

  huffman_tree *forest[ALPHABET_SIZE];
  for (i = 0; i < ALPHABET_SIZE; i++)
    forest[i] = NULL;

  int nb_leaves = create_huffman_forest(counts, forest);
  for (i = 0; i < nb_leaves; i++)
    printf("[%d, %d] ", forest[i]->nb_occurrences, forest[i]->symbol);
  printf("\n");
  
  sort_huffman_forest(forest, nb_leaves);
  for (i = 0; i < nb_leaves; i++)
    printf("[%d, %d] ", forest[i]->nb_occurrences, forest[i]->symbol);
  printf("\n");

  
  huffman_tree *huffman = build_huffman_tree(forest, nb_leaves);
  printf("\n");
  print_huffman_tree(huffman);
  

  exit(0);
}
