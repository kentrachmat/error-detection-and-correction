#ifndef REPEAT_H
#define REPEAT_H

/**
 * Reads bytes on stdin, repeat them three times and output them on standard
 * output.
 */
void encode_repeat();

/**
 * Takes three bytes (from a repeat three times coding), decode it and 
 * return the result of the decoding.
 * 
 * @param bytes: Three bytes
 * @return A single byte made of the majority bits at each position.
 */
unsigned char decode_three_bytes(unsigned char bytes[3]);

/**
 * Reads bytes on stdin that should be encoded by repeating bytes three times
 * decode them and output results on stdout. 
 */
void decode_repeat();

#endif
