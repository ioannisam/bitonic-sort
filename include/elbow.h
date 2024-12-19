#ifndef ELBOW_H
#define ELBOW_H

#include "./utility.h"

typedef struct  {
  int index;
  int polarity; 
} Extremum;

Extremum  elbow(Vector* local);
void elbowmerge(Vector* local, int direction);

#endif // ELBOW_H
