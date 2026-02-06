#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "list.h"
#include "errors.h"
#include "tree_node.h"

#define CAPACITY 2
#define KEYSIZE 15
#define DECIMAL 10 // system

Array *createArray() {
	Array *array = (Array *)malloc(1 * sizeof(Array));
	if (array == NULL) return NULL;

	array->data = (char **)malloc(CAPACITY * sizeof(char *));

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


void printArray(Array *array, unsigned int key) {
	if (array == NULL || array->size == 0) {
		return;
	}

	printf("KEY: %u\n", key);
	printf("INFO: ");

	for (size_t i = 0; i < array->size; i++) {
		printf("%s", array->data[i]);
		printf("  ");
	}
	
	printf("\n");
}


int pushArray(Array *array, char *elem) {
	if (array == NULL || elem == NULL) {
		return ALLOCATION_ERROR;
	}

	if (array->size == array->capacity) {
		array->capacity *= 2;
		array->data = (char **)realloc(array->data, array->capacity * sizeof(char *));
		if (array->data == NULL) return ALLOCATION_ERROR;
	}
	
	array->data[array->size] = elem;
	(array->size)++;

	return OK;
}


int addArray(Array *array, List *info) { // информацию из node to array
	if (array == NULL || info == NULL) return ALLOCATION_ERROR;

	InfoNode *curr = info->head;
	while (curr != NULL) {
		int status = pushArray(array, curr->info);
		if (status != OK) return status;
		curr = curr->next;
	}

	return OK;
}

