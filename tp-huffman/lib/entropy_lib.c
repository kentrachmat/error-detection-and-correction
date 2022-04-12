#include <math.h>

#include "entropy_lib.h"

void count_occurrences(FILE *file, int counts[]) {
  int char_read;
  while ((char_read = fgetc(file)) != EOF) {
    counts[char_read]++;
  }
}

struct file_stat entropy(int counts[]) {
  int i;
  struct file_stat stat;

  stat.entropy = 0;
  stat.size = 0;

  /* On utilise la formule
   * $$ H(M) = \log_2{N} - \frac{\sum_{i=1}^mn_i\log_2{n_i}}{N}.$$
   */
  for (i = 0; i < 256; i++) {
    if (counts[i] > 0) {
      stat.entropy += counts[i] * log(counts[i]) / log(2);
      stat.size += counts[i];
    }
  }

  stat.entropy = log(stat.size) / log(2) - stat.entropy / stat.size;

  return stat;
}

