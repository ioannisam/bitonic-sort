#ifndef UTILITY_H
#define UTILITY_H 

typedef struct {
  int* arr;
  int size;
} Vector;

void checkArgs(int argc, char** argv, int* q, int* p, int rank, int size);

Vector* newVec(int size);
void delVec(Vector* vec);
void printVec(Vector* vec, char* message);
void randomVec(Vector* vec, int max);

int compAscending (const void* a, const void* b);
int compDescending(const void* a, const void* b);

#endif // UTILITY_H 
