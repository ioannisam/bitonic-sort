#include "../include/elbow.h"
#include "../include/utility.h"

#include "stdlib.h"

void merge(int* local, int left, int mid, int right, int ascending) {

  int size = right - left + 1;
  int temp[size];
  int i = left, j = mid + 1, k = 0;

  // Merge the two parts in sorted order
  while (i <= mid && j <= right) {
    if ((ascending && local[i] <= local[j]) || (!ascending && local[i] >= local[j])) {
      temp[k++] = local[i++];
    } else {
      temp[k++] = local[j++];
    }
  }

  // Copy the remaining elements
  while (i <= mid) temp[k++] = local[i++];
  while (j <= right) temp[k++] = local[j++];

  // Copy the merged array back to the original array
  for (i=left; i<=right; i++) {
    local[i] = temp[i-left];
  }
}

void mergeSort(int* local, int left, int right, int ascending) {
  if (left < right) {
    int mid = left + (right-left)/2;

    mergeSort(local, left, mid, ascending);
    mergeSort(local, mid+1, right, ascending);
    merge(local, left, mid, right, ascending);
  }
}

int findElbow(Vector* local) {

  for (int i=1; i<local->size; i++) {
    if (local->arr[i] < local->arr[i-1]) {
      return i-1;  // elbow is where the transition occurs
    }
  }

  return -1;  // no elbow found, sequence already sorted
}

void elbowsort(Vector* local, int direction){
  
  if(direction){
    qsort(local->arr, local->size, sizeof(int), compAsc);
  } else {
    qsort(local->arr, local->size, sizeof(int), compDesc);
  }
}

// void elbowsort(Vector* local, int ascending) {

//   int elbow = findElbow(local);
//   if (elbow == -1) {
//     return;
//   }

//   // sort first part before the elbow
//   mergeSort(local->arr, 0, elbow, ascending);
//   // sort second part after the elbow
//   mergeSort(local->arr, elbow + 1, local->size - 1, ascending);
//   // merge both sorted parts together 
//   merge(local->arr, 0, elbow, local->size - 1, ascending);
// }
