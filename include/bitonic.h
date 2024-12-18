#ifndef BITONIC_H
#define BITONIC_H

#include "./utility.h"

typedef enum {
  ASCENDING  = 1,
  DESCENDING = 0
} Order;

void initialSort(Vector* local, int rank);
void exchange(int partner, Vector* local, Vector* remote);
void distributed_sort(Vector* local_data, int rank, int size);

#endif // BITONIC_H
