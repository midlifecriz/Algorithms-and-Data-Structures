#include <stdio.h>
#include <stdlib.h>

#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
	size_t capacity;
	size_t size;
	size_t *data; // массив указателей на информацию
} Array;

Array *createArray();
void destroyArray(Array *);
int pushArray(Array *, size_t);
Array *inputArray(size_t);

#endif

