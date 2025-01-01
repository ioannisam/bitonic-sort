#ifndef TEST_H
#define TEST_H 

#include "./utility.h"

int  sortcheck(Vector* vec, int processes);
int  fullCheck(Vector* vec);
void results  (Vector* sorted, int processes, int rank, double time);

#endif // TEST_H
