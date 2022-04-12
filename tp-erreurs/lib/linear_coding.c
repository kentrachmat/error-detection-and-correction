#include <stddef.h>
#include <stdio.h>
#include "bitarray.h"
#include "linear_coding.h"

binary_matrix code_word(binary_matrix word, binary_matrix generator) {
  return multiply_matrices(word, generator);
}

binary_matrix transposed_control_matrix(binary_matrix generator) {
  int columns = nb_columns(generator), rows = nb_rows(generator);
  int matrixValue, i, j, n_moins_k = columns - rows, copyRow = rows;
  binary_matrix matrix = zero_matrix(columns, n_moins_k);
  
  for(i=0; i<copyRow; i++, copyRow = rows){

    for(j=0; copyRow<columns; j++, copyRow++){
      matrixValue = matrix_value(generator, i, copyRow);
      set_matrix_value(matrix, i, j, matrixValue);
    }
    
    j = 0;
  }

  for(;i < columns;i++, j++){
    set_matrix_value(matrix, i, j, 1);
  }
  
  return matrix;  
}

binary_matrix syndrome(binary_matrix word, binary_matrix tH) {
  return multiply_matrices(word, tH);
}

binary_matrix correct_result(binary_matrix word, binary_matrix s, binary_matrix tH) {
  binary_matrix zeroMatrix = zero_matrix(s->rows, s->columns);
  binary_matrix correctMatrixs = copy_matrix(word);
  int matrixValue, rows, columns;

  for(rows=0; rows<tH->rows; rows++){
    for(columns=0; columns<tH->columns; columns++){
      matrixValue = matrix_value(tH, rows, columns);
      set_matrix_value(zeroMatrix, 0, columns, matrixValue);
    }

    if(equals_matrix(s, zeroMatrix) != 0){
      if(matrix_value(word, 0, rows) == 1){
        set_matrix_value(correctMatrixs, 0, rows, 0);
      } 
      else{
        set_matrix_value(correctMatrixs, 0, rows, 1);
      }
      return correctMatrixs;
    }
  }
  return NULL;
}

binary_matrix decode_word(binary_matrix word, binary_matrix tH) {
  int columns, matrixValue, k = tH->rows - tH->columns;
  binary_matrix syndrom = syndrome(word, tH);
  binary_matrix decodeMatrix = zero_matrix(1, k), correctMatrixs = zero_matrix(1, tH->rows);

  if(is_zero_matrix(syndrom) != 0){
    for(columns=0; columns<k; columns++){
      matrixValue = matrix_value(word, 0, columns);
      set_matrix_value(decodeMatrix, 0, columns, matrixValue);
    }

    return decodeMatrix;
  } 
  else{
    correctMatrixs = correct_result(word, syndrom, tH);

    for(columns=0; columns<k; columns++){
      matrixValue = matrix_value(correctMatrixs, 0, columns);
      set_matrix_value(decodeMatrix, 0, columns, matrixValue);
    }

    return decodeMatrix;
  }
}

void linear_encoding(binary_matrix generator) {
  int byte;
  buffer_t read_buffer, write_buffer;
  
  read_buffer.bits = init_bitarray();
  read_buffer.size = 0;
  write_buffer.bits = init_bitarray();
  write_buffer.size = 0;

  while ((byte = getchar()) !=  EOF) {
    add_byte(read_buffer.bits, read_buffer.size, byte);
    read_buffer.size += 8;
    encode_with_buffer(&read_buffer, &write_buffer, generator);
    while (write_buffer.size >= 8) {
      putchar(pop_byte(write_buffer.bits));
      write_buffer.size -= 8;
    }
  }

  /* Completion */
  set_bit(read_buffer.bits, read_buffer.size);
  read_buffer.size += nb_rows(generator) - read_buffer.size;
  encode_with_buffer(&read_buffer, &write_buffer, generator);
  while (write_buffer.size >= 8) {
    putchar(pop_byte(write_buffer.bits));
    write_buffer.size -= 8;
  }

  /* Completion for write_buffer */
  set_bit(write_buffer.bits, write_buffer.size);
  write_buffer.size += 8 - write_buffer.size;
  putchar(pop_byte(write_buffer.bits));
}

void encode_with_buffer(buffer_t *read_buffer, buffer_t *write_buffer, binary_matrix generator) {
  binary_matrix word; 
  binary_matrix coded;
  while(read_buffer->size >= nb_rows(generator)) {
    word = pop_matrix_from_bitarray(read_buffer->bits, nb_rows(generator));
    read_buffer->size -= nb_rows(generator);

    //    print_matrix(word);
    /* v' = v*G */
    coded = code_word(word, generator);
    //    print_matrix(coded);
    write_buffer->size += append_matrix_to_bitarray(write_buffer->bits, coded, write_buffer->size);
  }
}

void linear_decoding(binary_matrix tH) {
  int byte;
  buffer_t read_buffer, write_buffer;
  
  read_buffer.bits = init_bitarray();
  read_buffer.size = 0;
  write_buffer.bits = init_bitarray();
  write_buffer.size = 0;

  while ((byte = getchar()) !=  EOF) {
    add_byte(read_buffer.bits, read_buffer.size, byte);
    read_buffer.size += 8;
    decode_with_buffer(&read_buffer, &write_buffer, tH, 2);
    while (write_buffer.size >= 8) {
      putchar(pop_byte(write_buffer.bits));
      write_buffer.size -= 8;
    }
  }

  add_byte(read_buffer.bits, read_buffer.size, byte);
  read_buffer.size += 8;
  while (get_bit(read_buffer.bits, read_buffer.size-1) == 0)
    read_buffer.size--;
  read_buffer.size--;
  decode_with_buffer(&read_buffer, &write_buffer, tH, 1);
  while (get_bit(write_buffer.bits, write_buffer.size-1) == 0)
    write_buffer.size--;
  write_buffer.size--;
  while (write_buffer.size >= 8) {
    putchar(pop_byte(write_buffer.bits));
    write_buffer.size -= 8;
  }
}

void decode_with_buffer(buffer_t *read_buffer, buffer_t *write_buffer, binary_matrix tH, int nb) {
  binary_matrix word; 
  binary_matrix decoded;
  while(read_buffer->size >= nb*nb_rows(tH)) {
    word = pop_matrix_from_bitarray(read_buffer->bits, nb_rows(tH));
    read_buffer->size -= nb_rows(tH);

    //    print_matrix(word);
    /* v' = v*G */
    decoded = decode_word(word, tH);
    //    print_matrix(decoded);
    write_buffer->size += append_matrix_to_bitarray(write_buffer->bits, decoded, write_buffer->size);
  }
}
