#ifndef UTILITY_H
#define UTILITY_H 

typedef struct {
  int* arr;
  int size;
} Vector;

void checkArgs(int argc, char** argv, int* q, int* p);

Vector* newVec(int size);
void delVec(Vector* vec);
void printVec(Vector* vec);
void randomVec(Vector* vec, int max);

#endif // UTILITY_H 