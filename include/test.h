#ifndef TEST_H
#define TEST_H 

#include "./utility.h"

int  sortcheck(Vector* vec, int processes);
int  fullCheck(Vector* vec);
void results  (Vector* sorted, int rank, int processes, double time);

#endif // TEST_H
