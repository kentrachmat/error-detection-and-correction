#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdint.h>

#define ALPHABET_SIZE (sizeof(((struct bitarray256_s *)0)->data) << 3)

/** 
 * A structure storing at most 256 bits.
 */
typedef struct bitarray256_s {
  /** the number of bits used in the structure */
  int size;
  /** the bits stored in the structure (you should not access this directly) */
  uint64_t data[4];
} bitarray256_t;

/**
 * Creates and init a bitarray.
 *
 * @return a bitarray256_t * bits, such that bits->size == 0 and bits->data[i] == 0 for i in {0, ..., 3}
 */
bitarray256_t *init_bitarray();

void delete_bitarray(bitarray256_t * bits);

/**
 * Copy bitarray `src` into bitarray `dest`.
 *
 * @param src: the source bitarray
 * @param dest: the destination bitarray (must have already been created with init_bitarray)
 */
void copy_bitarray(bitarray256_t *src, bitarray256_t *dest);

/**
 * Gets the bit at the specified position.
 * 
 * @param bits: structure storing the bits under 64-bit integers.
 * @param pos : the position of the requested bit in the bitarray.
 *              Position 0 is the least significant bit in bits.data[0]
 * @pre 0 <= pos < 256
 * @return the bit (0 or 1) at the requested position
 */
int get_bit(bitarray256_t *bits, int pos);

/**
 * Return consecutive bits in the representation
 * 
 * @param bits: the structure containing at most 256 bits
 * @param pos: the position of the least significant bit to retrieve
 * @param nb_bits: the number of consecutive bits to retrieve (at most 8)
 * @pre nb_bits <= 8 and pos+nb_bits <= bits->size and pos >= 0
 * @return the value of the corresponding bits (between 0 and 255)
 */
unsigned int get_bits(bitarray256_t *bits, int pos, int nb_bits);

/**
 * Sets the bit at the specified position and potentially updates the
 * size.
 * 
 * @param bits: structure storing the bits under 64-bit integers.
 * @param pos : the position of the bit to be set in the bitarray.
 *              Position 0 is the least significant bit.
 * @pre 0 <= pos < 256
 * @post get_bit(bits, pos) == 1, and bits.size >= pos+1
 */
void set_bit(bitarray256_t *bits, int pos);

/**
 * Unsets the bit at the specified position
 *
 * @param bits: structure storing the bits under 64-bit integers.
 * @param pos : the position of the bit to be unset in the bitarray.
 *              Position 0 is the least significant bit.
 * @pre The bit array must have been created with at least pos+1 bits and pos >= 0
 * @post get_bit(bitarray, pos) == 0
 */
void unset_bit(bitarray256_t *bits, int pos);

/**
 * Shift bits left in the bitarray.
 *
 * @param bits : structure storing the bits under 64-bit integers.
 * @post bits.size has been increased by 1 (unless it reached the maximum).
 *       All the bits in the bitarray have been shifted to the left by 1 bit
 *       (ie. the least significant bit is now the second least significant, and so on)
 */
void left_shift_bit(bitarray256_t *bits);

#endif
