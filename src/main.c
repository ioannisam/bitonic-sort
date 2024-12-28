#include "../include/bitonic.h"
#include "../include/utility.h"
#include "../include/test.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  // run a copy of main for each rank
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int q, p; // 2^p processes 2^q numbers each
  checkArgs(argc, argv, &q, &p, rank, size);

  // total numbers
  int N = 1 << (q+p);
  Vector* local = newVec(1<<q);
  if (rank == 0) {
    Vector* data = newVec(N);
    randomVec(data, 1000);
    // printVec(data, "Unsorted data:\n");

    // rank 0 scatters data across all ranks
    MPI_Scatter(data->arr, local->size, MPI_INT, local->arr, local->size, MPI_INT, 0, MPI_COMM_WORLD);
    delVec(data);
  } else {
    // other ranks accept data, but don't send
    MPI_Scatter(NULL, local->size, MPI_INT, local->arr, local->size, MPI_INT, 0, MPI_COMM_WORLD);
  }

  double start = MPI_Wtime();
  distributed_sort(local, rank, size);
  double end = MPI_Wtime();
  MPI_Barrier(MPI_COMM_WORLD);

  // gather sorted data at root
  Vector* sorted = NULL;
  if (rank == 0) {
    sorted = newVec(N);
  }
  MPI_Gather(local->arr, local->size, MPI_INT, sorted ? sorted->arr : NULL, local->size, MPI_INT, 0, MPI_COMM_WORLD);

  // wait until all ranks reach this point
  MPI_Barrier(MPI_COMM_WORLD);
  results(sorted, rank, size, end-start);

  delVec(local);
  MPI_Finalize();
  return 0;
}
