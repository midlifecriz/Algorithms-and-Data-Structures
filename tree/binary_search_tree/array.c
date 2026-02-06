#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "list.h"
#include "errors.h"

#define CAPACITY 1

Array *createArray() {
	Array *array = (Array *)malloc(CAPACITY * sizeof(Array));

	if (array == NULL) {
		return NULL;
	}

	array->data = (char **)malloc(1 * sizeof(char *));

	if (array->data == NULL) {
		return NULL;
	}

	array->capacity = 1;
	array->size = 0;

	return array;
}


void destroyArray(Array *array) {
	if (array == NULL) {
		return;
	}

	free(array->data);
	free(array);
}


void printArray(Array *array) {
	if (array == NULL || array->size == 0) {
		return;
	}

	printf("KEY: %s\n", array->data[0]);
	printf("INFO: ");

	for (size_t i = 1; i < array->size; i++) {
		printf("%s", array->data[i]);
		printf("  ");
	}
	
	printf("\n");
}


int addElem(Array *array, char *elem) {
	if (array == NULL || elem == NULL) {
		return ALLOCATION_ERROR;
	}

	if (array->size == array->capacity) {
		array->capacity *= 2;
		array->data = (char **)realloc(array->data, array->capacity * sizeof(char *));

		if (array->data == NULL) {
			return ALLOCATION_ERROR;
		}
	}
	
	array->data[array->size] = elem;
	(array->size)++;

	return OK;
}


int addInfo(Array *array, List *list) { // информацию из списка в массив
	if (array == NULL || list == NULL) {
		return ALLOCATION_ERROR;
	}

	InfoNode *current = list->head;
	int status = OK;

	while (current != NULL) {
		status = addElem(array, current->info);

		if (status != OK) {
			return status;
		}

		current = current->next;
	}

	return OK;
}







		
