#include "../include/bitonic.h"

#include <stdio.h>
#include <stdlib.h>

void bmerge(int* arr, int low, int cnt, Order direction) {

  if (cnt > 1) {

    int k = cnt/2;

    int* minb = (int*)malloc(k*sizeof(int));
    int* maxb = (int*)malloc(k*sizeof(int));

    for (int i=0; i<k; i++) {
      int left  = arr[low+i];
      int right = arr[low+i + k];
      minb[i] = (left<right) ? left : right;
      maxb[i] = (left>right) ? left : right;
    }

    // merge according to direction
    if (direction == ASCENDING) {
      for (int i=0; i<k; i++) {
        arr[low+i] = minb[i];
        arr[low+i + k] = maxb[i];
      }
    } else if (direction == DESCENDING){
      for (int i=0; i<k; i++) {
        arr[low+i] = maxb[i];
        arr[low+i + k] = minb[i];
      }
    } else {
      fprintf(stderr, "Direction Error\n");
      free(minb);
      free(maxb);
      exit(EXIT_FAILURE);
    }

    free(minb);
    free(maxb);

    // merge the two halves
    bmerge(arr, low  , k, direction);
    bmerge(arr, low+k, k, direction);
  }
}

void bsort(int* arr, int low, int cnt, Order direction) {
  if (cnt > 1) {
    int k = cnt / 2;

    // sort the two halves
    bsort(arr, low  , k, ASCENDING);
    bsort(arr, low+k, k, DESCENDING);

    // merge the two halves
    bmerge(arr, low, cnt, direction);
  }
}