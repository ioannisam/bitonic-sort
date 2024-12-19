#include "../include/elbow.h"
#include "../include/utility.h"

#include "stdlib.h"
#include "string.h"

Extremum elbow(Vector* local) {

  Extremum point;
  point.index = -1;
  point.polarity = 0;

  int  n   = local->size;
  int* arr = local->arr;

  for (int i=0; i<n; i++) {
    int prev = arr[(i-1 + n) % n];
    int curr = arr[i];
    int next = arr[(i+1) % n];

    if (curr>prev && curr>next) {
      point.index = i;
      point.polarity = 1;
      return point; // elbow
    }

    if (curr<prev && curr<next) {
      point.index = i;
      point.polarity = -1;
      return point; // pit
    }
  }

  // invalid bitonic sequences (corner cases)
  int max = 0;
  for (int i=1; i<n; i++) {
    if (arr[i] > arr[max]) {
      max = i;
    }
  }
  // return max as elbow
  point.index = max;
  point.polarity = 1;

  return point;
}

void elbowmerge(Vector* local, int direction) {

  Extremum point = elbow(local);
  int  n   = local->size;
  int* tmp = malloc(sizeof(int)*n);

  // adjacent indices to the extremum (elbow or pit)
  int left  = (point.index-1 + n) % n;
  int right = (point.index+1) % n;

  // pit (minimum), ascending order
  if (point.polarity == -1) {  

    // add the extremum (minimum) first
    int i = 0;
    tmp[i++] = local->arr[point.index];  

    // fill the array in ascending order
    while (i < n) {
      if (local->arr[left] < local->arr[right]) {
        tmp[i++] = local->arr[left];
        left = (left-1 + n) % n;  // move left index circularly
      } else {
        tmp[i++] = local->arr[right];
        right = (right + 1) % n;  // move right index circularly
      }
    }
  // elbow (maximum), descending order
  } else if (point.polarity == 1) {  

    // Add the extremum (maximum) first
    int i = n-1;
    tmp[i--] = local->arr[point.index];  

    // fill the array in descending order
    while (i >= 0) {
      if (local->arr[left] > local->arr[right]) {
        tmp[i--] = local->arr[left];
        left = (left-1 + n) % n;  // move left index circularly
      } else {
        tmp[i--] = local->arr[right];
        right = (right+1) % n;  // move right index circularly
      }
    }
  }

  if (direction == 1) {
    // Ascending Order: normal copy
    memcpy(local->arr, tmp, sizeof(int)*n);
  } else {
    // Descending Order: reverse copy
    for (int j=0; j<n; j++) {
      local->arr[j] = tmp[n-1 - j];
    }
  }

  free(tmp);
}