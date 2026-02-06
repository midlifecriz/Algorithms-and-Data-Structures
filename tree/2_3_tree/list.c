#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "info_node.h"
#include "errors.h"

List *createList() {
	List *list = (List *)malloc(1 * sizeof(List));
	if (list == NULL) return NULL;

	list->head = NULL;
	list->tail = NULL;

	return list;
}


void destroyList(List *list) {
	if (list == NULL) {
		return;
	}

	InfoNode *current = list->head;
	InfoNode *tmp = NULL;

	while (current != NULL) {
		tmp = current->next;
		destroyInfoNode(current);
		current = tmp;
	}

	free(list);
}

void printList(List *list) {
	if (list == NULL) {
		return;
	}

	InfoNode *current = list->head;

	while (current != NULL) {
		printInfoNode(current);
		printf(" ");
		
		current = current->next;
	}

	printf("\n");
}

bool listIsEmpty(List *list) {
	if (list == NULL) {
		return 1;
	}

	if (list->head == NULL || list->tail == NULL) {
		return 1;
	}

	return 0;
}


int Push(List *list, const char *info) { // добавление в конец
	if (list == NULL) {
		return ALLOCATION_ERROR;
	}

	InfoNode *node = createInfoNode(info);

	if (node == NULL) {
		return ALLOCATION_ERROR;
	}

	if (list->head == NULL || list->tail == NULL) {
		list->head = node;
		list->tail = node;

		return OK;
	}

	list->tail->next = node;
	list->tail = node;

	return OK;
}


int deleteEl(List *list) { // удалить из начала
	if (list == NULL) {
		return ALLOCATION_ERROR;
	}

	if (list->head == NULL) {
		return OK; // ????????
	}

	InfoNode *tmp = list->head;
	list->head = list->head->next;
	destroyInfoNode(tmp);

	return OK;
}


int copylst(List **dst, List *src) {
	if (src == NULL) return ALLOCATION_ERROR;

	destroyList(*dst);
	*dst = createList();
	if (*dst == NULL) return ALLOCATION_ERROR;

	int status = OK;
	InfoNode *curr = src->head;

	while (curr != NULL) {
		status = Push(*dst, curr->info);
		if (status != OK) {
			destroyList(*dst);
			return status;
		}
		curr = curr->next;
	}

	return OK;
}

