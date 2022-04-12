#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#define PRINT_TREE_DEPTH 100
#define PRINT_TREE_WIDTH 500

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/**
 * Representation of a Huffman tree
 */
typedef struct huffman_tree_s {
  /** `left` and `right` are respectively the left and right subtrees of the tree.
   * NULL if there is no such subtree. */
  struct huffman_tree_s *left, *right;
  /** The number of occurrences of the symbol (in a leaf) or the cumulative number
   * of occurrences of the symbols in the subtree */
  int nb_occurrences;
  /** The symbol (only in a leaf) */
  unsigned char symbol;
} huffman_tree;


/**
 * Creates an empty Huffman Tree, with 0 occurrence.
 * 
 * @post isHuffmanLeaf() on the returned tree will correspond to True.
 */
huffman_tree *create_empty_huffman_tree();

/**
 * Creates an Huffman Tree (actually a leaf) for the specified character
 * with the specified count (the number of occurrences of this character).
 * 
 * @post isHuffmanLeaf() on the returned tree will correspond to True
 * and the attributes `symbol` and `nb_occurrences` are respectively set
 * to `c` and `count`.
 */
huffman_tree *create_huffman_tree(char c, int count);

/**
 * Deletes the Huffman Tree given in parameter and all its subtrees
 *
 * A Huffman tree created with `create_empty_huffman_tree` or with 
 * `create_huffman_tree` must be deleted with this function when the
 * tree is not used anymore.
 */
void delete_huffman_tree(huffman_tree *);

/**
 * Predicate that tells if the Huffman tree in parameter is a leaf.
 * 
 * @return a value evaluated to true if the tree in parameter is restricted to
 * a leaf (ie. `tree->left` and `tree->right` are NULL).
 */
int is_huffman_leaf(huffman_tree *tree);

/**
 * Compare two Huffman trees by the number of occurrences they represent.
 *
 * @return -1 if tree1 has more occurrences than tree2, 1, in the opposite case
 * and 0 if occurrences from both trees are equal
 */
int compare_huffman_trees(huffman_tree *tree1, huffman_tree *tree2);

/**
 * Prints a Huffman tree
 */
void print_huffman_tree(huffman_tree *tree);

/* void setHuffmanLeftTree(huffman_tree *tree, huffman_tree *left); */
/* void setHuffmanLeftTree(huffman_tree *tree, huffman_tree *right); */

/* void setHuffmanCount(huffman_tree *tree, int count); */
#endif
