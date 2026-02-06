#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array {
	size_t capacity;
	size_t size;
	char **data; // массив указателей на информацию
} Array;

Array *createArray();
void destroyArray(Array *);
void printArray(Array *, unsigned int);
int pushArray(Array *, char *);
int addArray(Array *, List *);

#endif

