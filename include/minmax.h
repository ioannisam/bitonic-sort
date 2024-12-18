#ifndef MINMAX_H
#define MINMAX_H

#include "./utility.h"

void min(Vector* local, Vector* remote);
void max(Vector* local, Vector* remote);
void minmax(int rank, int stage, int distance, Vector* local, Vector* remote);

#endif // MINMAX_H
