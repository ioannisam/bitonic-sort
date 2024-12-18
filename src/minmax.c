#include "../include/minmax.h"
#include "../include/utility.h"

#include "math.h"

void max(Vector* local, Vector* remote) {

  for (int i=0; i<local->size; i++) {
    if (local->arr[i] < remote->arr[i]) {
      local->arr[i] = remote->arr[i];
    }
  }
}

void min(Vector* local, Vector* remote) {

  for (int i=0; i<local->size; i++) {
    if (local->arr[i] > remote->arr[i]) {
      local->arr[i] = remote->arr[i];
    }
  }
}

void minmax(int rank, int stage, int distance, Vector* local, Vector* remote) {

  int mirror = 1 << stage;
  int w = 2*mirror;
  int pos = rank % w;

  int reflection = pos<mirror ? mirror-pos-1 : pos-mirror; 

  if (reflection & (1 << (int)log2(distance))) {
    min(local, remote);
  } else {
    max(local, remote);
  }
}
