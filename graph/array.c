#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "input.h"
#include "array.h"
#include "errors.h"

#define CAPACITY 2

Array *createArray() {
	Array *array = (Array *)malloc(1 * sizeof(Array));
	if (array == NULL) return NULL;

	array->data = (size_t *)malloc(CAPACITY * sizeof(size_t));

	if (array->data == NULL) {
		free(array);
		return NULL;
	}

	array->capacity = CAPACITY;
	array->size = 0;

	return array;
}


void destroyArray(Array *array) {
	if (array == NULL) return; 
	free(array->data);
	free(array);
}


int pushArray(Array *array, size_t x) {
	if (array == NULL) return ALLOCATION_ERROR;

	if (array->size == array->capacity) {
		array->capacity *= 2;
		array->data = (size_t *)realloc(array->data, array->capacity * sizeof(size_t));
		if (array->data == NULL) return ALLOCATION_ERROR;
	}
	
	array->data[array->size] = x;
	(array->size)++;

	return OK;
}


Array *inputArray(size_t quantity) {
	Array *array = createArray();
	if (array == NULL) return NULL;

	size_t port = 0;
	int status = OK;

	for (size_t i = 0; i < quantity; i++) {
		printf("Input number of port:\n");
		status = getSize_t(&port, 1, ULONG_MAX);
		if (status == EOF) {
			destroyArray(array);
			return NULL;
		}

		status = pushArray(array, port);
		if (status != OK) {
			destroyArray(array);
			return NULL;
		}
	}

	return array;
}



