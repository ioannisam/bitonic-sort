#include "../include/utility.h"

#include <stdio.h>

int sortCheck(Vector* vec, int p) {

  int ans = 1;
  for (int i=0; i<p-1; i++) {
    if (vec->arr[i*p] > vec->arr[(i+1)*p]) {
      ans = 0;
      break;
    }
  }

  return ans;
}

int fullCheck(Vector* vec) {

  for (int i=0; i<vec->size-1; i++) {
    if (vec->arr[i] > vec->arr[i+1]) {
      return 0; // not sorted
    }
  }
  return 1;
}

void results(Vector* sorted, int p, double time) {

  // printVec(sorted, "Sorted data:\n");
  sortCheck(sorted, p) ? printf("Partial Check: Array is Sorted :)\n") : printf("Partial Check: Array is NOT Sorted :(\n");
  fullCheck(sorted)    ? printf("Full    Check: Array is Sorted :)\n") : printf("Full    Check: Array is NOT Sorted :(\n");
  printf("\nExecution Time (s): %f\n", time);

  delVec(sorted);
}
