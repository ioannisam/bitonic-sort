#include "../include/bitonic.h"
#include "../include/utility.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <q> <p>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int q = atoi(argv[1]);
  int p = atoi(argv[2]);
  if (q <= 0 || p <= 0) {
    fprintf(stderr, "Error: Both q and p must be positive integers.\n");
    return EXIT_FAILURE;
  }

  // Total number of integers to sort: 2^(q + p)
  int N = 1 << (q+p); 

  Vector* vec = newVec(N);
  if (!vec->arr) {
    return EXIT_FAILURE;
  }
  randomVec(vec, 100);
  printf("Original array:\n");
  printVec(vec);

  bsort(vec->arr, 0, N, ASCENDING);
  printf("Sorted array:\n");
  printVec(vec);

  delVec(vec);

  return EXIT_SUCCESS;
}
