#ifndef UTILITY_H
#define UTILITY_H 

typedef struct {
  int* arr;
  int size;
} Vector;

void checkArgs(int argc, char** argv, int* q, int* p, int rank, int size);

int compare_ascending (const void* a, const void* b);
int compare_descending(const void* a, const void* b);

Vector* newVec(int size);
void delVec(Vector* vec);
void printVec(Vector* vec, char* message);
void randomVec(Vector* vec, int max);

#endif // UTILITY_H 
