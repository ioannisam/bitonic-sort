#include "../include/bitonic.h"
#include "../include/utility.h"

#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void exchange(int partner, Vector* local, Vector* buffer) {
  if (buffer->size < local->size) {
    fprintf(stderr, "Buffer size mismatch\n");
    MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
  }
  MPI_Sendrecv(local->arr, local->size, MPI_INT, partner, 0,
               buffer->arr, local->size, MPI_INT, partner, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void minmax(int rank, int stage, int distance, Vector* local, Vector* buffer) {

  int mirror = 1 << stage;
  int w = 2*mirror;
  int pos = rank % w;

  int reflection = pos<mirror ? mirror-pos-1 : pos-mirror; 

  if (reflection & (1 << (int)log2(distance))) {
    // min
  } else {
    // max
  }
}

void elbowsort(int* local, int local_size, int ascending) {
  // TODO: sort a bitonic sequence using starting from the "elbow" 
}

void distributed_sort(Vector* local, int rank, int size) {

  // number of processes
  int const p = log2(size);

  Vector* buffer = newVec(local->size);

  // initial local sort
  if (rank & 1) {
    qsort(local->arr, local->size, sizeof(int), compare_descending);
  } else { 
    qsort(local->arr, local->size, sizeof(int), compare_ascending);
  }

  for (int stage=1; stage<=p; stage++) {
    for (int step=stage; step>=1; step--) {

      int distance = 1 << (step-1);
      int partner = rank ^ distance;
      int direction = (rank & distance) == 0; // Ascending (0) or Descending (1)
      printf("RANK %d: Stage %d, Distance %d. Partner: %d\n", rank, stage, distance, partner);

      exchange(partner, local, buffer);
      minmax(rank, stage, distance, local, buffer);
    }
    elbowsort(local->arr, local->size, (rank & (1 << (stage - 1))) == 0);
  }

  free(buffer);
}
