#include <stdlib.h>
#include "bitarray.h"

bitarray256_t *init_bitarray() {
  bitarray256_t *bits = malloc(sizeof(struct bitarray256_s));
  bits->size = 0;
  for (int i = 0; i < 4; i++)
    bits->data[i] = 0;
  return bits;
}

void delete_bitarray(bitarray256_t *bits) {
  free(bits);
}

void copy_bitarray(bitarray256_t *src, bitarray256_t *dest) {
  dest->size = src->size;
  for (int i = 0; i < 4; i++)
    dest->data[i] = src->data[i];
}

int get_bit(bitarray256_t *bits, int pos) {
  /* TODO: BEWARE cast */
  return (bits->data[pos / 64] & ((uint64_t)1 << (pos%64))) >> (pos%64);
}

unsigned int get_bits(bitarray256_t *bits, int pos, int nb_bits) {
  int first_cell = pos / 64;
  int second_cell = (pos+nb_bits-1) / 64;

  if (first_cell == second_cell)
    return (bits->data[first_cell] & ((uint64_t)((1 << nb_bits) - 1) << (pos % 64))) >> (pos % 64);

  int nb_bits_first_cell = (first_cell+1) * 64 - pos;
  unsigned int result_second_cell = get_bits(bits, (first_cell + 1)*64, nb_bits - nb_bits_first_cell);
  unsigned int result_first_cell = get_bits(bits, pos, nb_bits_first_cell);

  return (result_second_cell << nb_bits_first_cell) | result_first_cell;
}

void set_bit(bitarray256_t *bits, int pos) {
  bits->data[pos / 64] |=  ((uint64_t)1 << (pos%64));
  if (pos+1 > bits->size)
    bits->size = pos + 1;
}

void unset_bit(bitarray256_t *bits, int pos) {
  bits->data[pos / 64] &=  (uint64_t) 0xFFFFFFFFFFFFFFFF ^ ((uint64_t)1 << (pos%64));
}

void left_shift_bit(bitarray256_t *bits) {
  int i, remainder;
  remainder = 0;
  for (i=0; i < 4; i++) {
    int last_bit = bits->data[i] >> 63;
    bits->data[i] = (bits->data[i]<<1) | remainder;
    remainder = last_bit;
  }
  if (bits->size < 256)
    bits->size++;
}
