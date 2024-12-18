#include "../include/bitonic.h"
#include "../include/minmax.h"
#include "../include/elbow.h"
#include "../include/utility.h"

#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <stdio.h>

void exchange(int partner, Vector* local, Vector* remote) {

  MPI_Sendrecv(local->arr, local->size, MPI_INT, partner, 0,
               remote->arr, local->size, MPI_INT, partner, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void distributed_sort(Vector* local, int rank, int size) {

  // number of processes
  int const p = log2(size);
  Vector* remote = newVec(local->size);

  // initial local sort
  if (rank & 1) {
    qsort(local->arr, local->size, sizeof(int), compDesc);
  } else { 
    qsort(local->arr, local->size, sizeof(int), compAsc);
  }

  for (int stage=1; stage<=p; stage++) {
    
    for (int step=stage; step>=1; step--) {

      int distance = 1 << (step-1);
      int partner = rank ^ distance;
      // printf("RANK %d: Stage %d, Distance %d. Partner: %d\n", rank, stage, distance, partner);

      exchange(partner, local, remote);
      minmax(rank, stage, distance, local, remote);
    }
    
    // Ascending (0) or Descending (1)
    int direction = (rank & (1 << stage)) == 0;     
    elbowsort(local, direction);
  }
  delVec(remote);
}
