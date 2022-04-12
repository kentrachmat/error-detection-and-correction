#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree.h"

huffman_tree *create_empty_huffman_tree() {
  return calloc(1, sizeof(huffman_tree));
}

huffman_tree *create_huffman_tree(char c, int count) {
  huffman_tree *tree = create_empty_huffman_tree();
  tree->symbol = c;
  tree->nb_occurrences = count;
  return tree;
}

void delete_huffman_tree(huffman_tree *tree) {
  if (! is_huffman_leaf(tree)) {
    delete_huffman_tree(tree->left);
    delete_huffman_tree(tree->right);
  }
  free(tree);
}

int is_huffman_leaf(huffman_tree *tree) {
  return tree->left == NULL && tree->right == NULL;
}

int compare_huffman_trees(huffman_tree *tree1, huffman_tree *tree2) {
  if (tree1->nb_occurrences < tree2->nb_occurrences) {
    return 1;
  } else if (tree1->nb_occurrences > tree2->nb_occurrences) {
    return -1;
  }
  return 0;
}


int _print_ht(huffman_tree *tree, int depth) {
  if (!tree) return 0;

  _print_ht(tree->right, depth + 1);
  
  for (int i = 0; i < depth; i++)
    printf("\t");
  if (is_huffman_leaf(tree))
    printf("[%d, %d]\n", tree->nb_occurrences, (int)tree->symbol);
  else
    printf("(%d)\n", tree->nb_occurrences);
    
  _print_ht(tree->left, depth + 1);

  return 1;
}

void print_huffman_tree(huffman_tree *tree) {
  _print_ht(tree, 0);
}
