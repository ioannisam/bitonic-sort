#include "../include/bitonic.h"
#include "../include/utility.h"

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
    randomVec(data, 100);
    printVec(data, "Unsorted data:\n");

    // rank 0 scatters data across all ranks
    MPI_Scatter(data->arr, local->size, MPI_INT, local->arr, local->size, MPI_INT, 0, MPI_COMM_WORLD);
    delVec(data);
  } else {
    // other ranks accept data, but don't send
    MPI_Scatter(NULL, local->size, MPI_INT, local->arr, local->size, MPI_INT, 0, MPI_COMM_WORLD);
  }

  distributed_sort(local, rank, size);

  // gather sorted data at root
  Vector* sorted = NULL;
  if (rank == 0) {
    sorted = newVec(N);
  }
  MPI_Gather(local->arr, local->size, MPI_INT, sorted ? sorted->arr : NULL, local->size, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    printVec(sorted, "Sorted data:\n");
    delVec(sorted);
  }

  delVec(local);
  MPI_Finalize();
  return 0;
}
