#include "../include/utility.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void checkArgs(int argc, char** argv, int* q, int* p, int rank, int size) {

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <q> <p>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  *q = atoi(argv[1]);
  *p = atoi(argv[2]);
  if (*q <= 0 || *p <= 0) {
    fprintf(stderr, "Error: q and p must be positive!\n");
    exit(EXIT_FAILURE);
  }
  
  if (size != (1 << *p)) {
    fprintf(stderr, "Error: the number of processes must be 2^p!\n");
    MPI_Finalize();
    exit(EXIT_FAILURE);
  }
  
  if (rank == 0) {
    printf("2^q=%d numbers per process, 2^p=%d processes.\n\n", 1<<*q, 1<<*p);
  }
}

int compare_ascending(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

int compare_descending(const void* a, const void* b) {
  return (*(int*)b - *(int*)a);
}

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

void printVec(Vector* vec, char* message) {

  if (vec == NULL || vec->arr == NULL) {
    fprintf(stderr, "Error: Invalid vector.\n");
    return;
  }

  printf("%s", message);
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
