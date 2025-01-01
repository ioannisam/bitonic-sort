#include "../include/bitonic.h"
#include "../include/utility.h"
#include "../include/test.h"

#include <time.h>

int main(int argc, char* argv[]) {

  int q, p; // 2^p processes 2^q numbers each
  checkArgs(argc, argv, &q, &p);

  // Total number of integers to sort: 2^(q + p)
  int N = 1 << (q+p); 

  Vector* vec = newVec(N);
  randomVec(vec, 1000);

  clock_t start = clock();
  bsort(vec->arr, 0, N, ASCENDING);
  clock_t end = clock();


  double elapsed = ((double)(end-start)) / CLOCKS_PER_SEC;
  results(vec, p, elapsed);

  return 0;
}
