#ifndef GENERATOR_MATRICES_H
#define GENERATOR_MATRICES_H

#include "binary_matrix.h"

/**
 * Creates a generator matrix for a parity [n+1, n, 2] coding.
 *
 * @param n: the number of bits of the unencoded message
 * @return the generator matrix
 */
binary_matrix parity_generator(int n);

/**
 * Creates a generator matrix for a repeat 3 times coding ([3n, n, 3]-linear coding).
 *
 * @param n: the number of bits of the unencoded message
 * @return the generator matrix
 */
binary_matrix repeat3_generator(int n);

/**
 * Creates a generator matrix for a parity 2D coding (as seen in Ex. 2.2)
 *
 * @return the generator matrix
 */
binary_matrix parity2d_generator();

/**
 * Creates a generator matrix for a Hamming coding [7, 4, 3]
 *
 * @return the generator matrix
 */
binary_matrix hamming_generator();

/**
 * Creates a generator matrix for a Hamming coding, with parity [8, 4, 4]
 *
 * @return the generator matrix
 */
binary_matrix hammingp_generator();

#endif
