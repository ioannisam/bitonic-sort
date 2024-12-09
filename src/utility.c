#include "../include/utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Vector* newVec(int size) {

  Vector* vec = (Vector*)malloc(sizeof(Vector));
  if (!vec) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }
  vec->arr = (int*)malloc(size*sizeof(int));
  if (!vec->arr) {
    fprintf(stderr, "Memory allocation failed\n");
    vec->size = 0;
    return NULL;
  } else {
    vec->size = size;
  }
  return vec;
}

void delVec(Vector* vec) {

  free(vec->arr);
  free(vec);
}

void printVec(Vector* vec) {

  if (vec == NULL || vec->arr == NULL) {
    fprintf(stderr, "Error: Invalid vector.\n");
    return;
  }

  for (int i=0; i<vec->size; i++) {
    printf("%d ", vec->arr[i]);
  }
  printf("\n");
}

void randomVec(Vector* vec, int max) {

  srand(time(NULL));
  for (int i=0; i<vec->size; i++) {
    vec->arr[i] = rand()%max;
  }
}
