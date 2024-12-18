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

void results(Vector* sorted, int rank, int size) {

  if (rank == 0) {
    printVec(sorted, "Sorted data:\n");
    isSorted(sorted, size) ? printf("Array is Sorted :)\n") : printf("Array is NOT Sorted :(\n");
    delVec(sorted);
  }
}
