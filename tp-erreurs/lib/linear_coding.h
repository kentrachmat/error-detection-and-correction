#ifndef LINEAR_CODING_H
#define LINEAR_CODING_H

#include "binary_matrix.h"
#include "bitarray.h"

typedef struct buffer_s {
  bitarray256_t *bits;
  int size;
} buffer_t;

/**
 * Code a word with the generator matrix.
 *
 * @param word: binary word to be coded
 * @param generator: generator matrix to use.
 * @pre nb_columns(word) == nb_rows(generator)
 */
binary_matrix code_word(binary_matrix word, binary_matrix generator);

/**
 * Gets the transposed control matrix from the generator matrix.
 *
 * @param generator: A generator matrix which must be of the shape (I A)
 * where the first part is the identity matrix.
 * @return the transposed control matrix
 */
binary_matrix transposed_control_matrix(binary_matrix generator);

/**
 * Computes the syndrome s(v) of a word v.
 *
 * @param word: the word v
 * @param tH: the transposed control matrix
 * @return the syndrome.
 */
binary_matrix syndrome(binary_matrix word, binary_matrix tH);

/**
 * Corrects the word in parameter using the syndrome and the transposed control matrix.
 * 
 * @param word: word to be corrected
 * @param s: syndrome of the word
 * @param tH: transposed control matrix
 * @return the corrected word (or NULL if the correction failed)
 * @pre the coding used must be able to correct **exactly** one error
 * @post word must **not** be modified
 */
binary_matrix correct_result(binary_matrix word, binary_matrix s, binary_matrix tH);

/**
 * Decode a word with the transposed control matrix.
 *
 * @param word: binary word to be decoded
 * @param tH: transposed control matrix
 * @pre The coding must have correction capacities and must be a systematic coding.
 * @return the decoded word (after correction if needed), without the added parity bits.
 */
binary_matrix decode_word(binary_matrix word, binary_matrix tH);

/**
 * Encode the data on the standard input with the provided generator matrix.
 *
 * @post Output is produced on standard output
 */
void linear_encoding(binary_matrix generator);

/**
 * Decode the data on the standard input with the provided transposed control matrix.
 *
 * @post Output is produced on standard output
 */
void linear_decoding(binary_matrix tH);

/**
 * Encode data in the read buffer with the generator matrix and writes the
 * result in the write buffer.
 * 
 * @pre read_buffer->size >= nb_rows(generator)
 */
void encode_with_buffer(buffer_t *read_buffer, buffer_t *write_buffer, binary_matrix generator);

void decode_with_buffer(buffer_t *read_buffer, buffer_t *write_buffer, binary_matrix tH, int nb);

#endif
