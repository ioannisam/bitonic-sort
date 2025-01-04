#ifndef BITONIC_H
#define BITONIC_H

typedef enum {
  ASCENDING  = 1,
  DESCENDING = 0
} Order;

void bmerge(int* arr, int low, int cnt, Order direction);
void bsort (int* arr, int low, int cnt, Order direction);

#endif // BITONIC_H