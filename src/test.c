#include "../include/utility.h"

#include <stdio.h>

int isSorted(Vector* vec, int processes) {

  int ans = 1;

  for (int i=0; i<processes-1; i++) {
    if (vec->arr[i*processes] > vec->arr[(i+1)*processes]) {
      ans = 0;
      break;
    }
  }

  return ans;
}

int sortCheck(Vector* vec) {

  for (int i=0; i<vec->size-1; i++) {
    if (vec->arr[i] > vec->arr[i+1]) {
      return 0; // not sorted
    }
  }
  return 1;
}

void results(Vector* sorted, int rank, int size) {

  if (rank == 0) {
    // printVec(sorted, "Sorted data:\n");
    isSorted(sorted, size) ? printf("Partial Check: Array is Sorted :)\n") : printf("Partial Check: Array is NOT Sorted :(\n");
    sortCheck(sorted)      ? printf("Full Check:    Array is Sorted :)\n") : printf("Full Check:    Array is NOT Sorted :(\n");
    delVec(sorted);
  }
}
