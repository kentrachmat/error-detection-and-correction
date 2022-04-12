#ifndef CHANNEL_H
#define CHANNEL_H


/**
 * Transmits a byte through a channel with a given probability of error.
 *
 * @param byte: Input byte in the channel
 * @param proba: Probability of error for a given bit (0 <= proba <= 1)
 * @return The byte after going through the channel (it may contain errors).
 */
char cbssm(char, float);

#endif
