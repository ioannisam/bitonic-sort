#ifndef ELBOW_H
#define ELBOW_H

#include "./utility.h"

void merge(int* local, int left, int mid, int right, int direction);
void mergeSort(int* local, int left, int right, int direction); 
int  findElbow(Vector* local);
void elbowsort(Vector* local, int direction);

#endif // ELBOW_H
