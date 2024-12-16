#ifndef BITONIC_H
#define BITONIC_H

#include "./utility.h"

typedef enum {
  ASCENDING  = 1,
  DESCENDING = 0
} Order;

void exchange(int partner, Vector* local, Vector* buffer);
void minmax(int rank, int stage, int distance, Vector* local, Vector* buffer);
void elbowsort(int* local, int local_size, int ascending);

void distributed_sort(Vector* local_data, int rank, int size);

#endif // BITONIC_H
