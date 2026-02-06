#include <string.h>
#include "errors.h"
#include "list.h"


Edge *createEdge(char *vertex) {
	Edge *edge = (Edge *)malloc(sizeof(Edge));
	if (edge == NULL) return NULL;

	edge->ports = createArray();
	if (edge->ports == NULL) {
		free(edge);
		return NULL;
	}

	edge->vertex = strdup(vertex);
	if (edge->vertex == NULL) {
		destroyArray(edge->ports);
		free(edge);
		return NULL;
	}

	return edge;
}


void destroyEdge(Edge *edge) {
	if (edge == NULL) return;

	destroyArray(edge->ports);
	free(edge->vertex);
	free(edge);
}


Node *createNode(Edge *edge) {
	if (edge == NULL) return NULL;

	Node *node = (Node *)malloc(sizeof(Node));
	if (node == NULL) return NULL;

	node->edge = edge;
	node->next = NULL;

	return node;
}


void destroyNode(Node *node) {
	if (node == NULL) return;
	
	destroyEdge(node->edge);
	free(node);
}


List *createList() {
	List *list = (List *)malloc(sizeof(List));
	if (list == NULL) return NULL;

	list->head = NULL;
	list->tail = NULL;

	return list;
}


void destroyList(List *list) {
	if (list == NULL) return;

	Node *curr = list->head;
	Node *tmp = NULL;

	while (curr != NULL) {
		tmp = curr->next;
		destroyNode(curr);
		curr = tmp;
	}

	free(list);
}


/*
bool listIsEmpty(List *list) {
	if (list == NULL) {
		return 1;
	}

	if (list->head == NULL || list->tail == NULL) {
		return 1;
	}

	return 0;
}
*/

int push(List *list, Edge *edge) { //добавление в конец
	if (list == NULL || edge == NULL) return ALLOCATION_ERROR;

	Node *node = createNode(edge);
	if (node == NULL) return ALLOCATION_ERROR;
	
	//list is empty
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
		return OK;
	}
	//not empty
	list->tail->next = node;
	list->tail = node;
	return OK;
}


int del(List *list, char *name) {
	if (list == NULL || name == NULL) return ALLOCATION_ERROR;
	if (list->head == NULL) return EDGE_NOT_FOUND;

	Node *prev = NULL;
	Node *node = list->head;

	while (node != NULL) {
		if (strcmp(node->edge->vertex, name) == 0) {
			break;
		}
		prev = node;
		node = node->next;
	}

	if (node == NULL) return EDGE_NOT_FOUND;
	
	if (node == list->tail) list->tail = prev; //delete tail
	if (prev != NULL) prev->next = node->next;
	else list->head = node->next; //delete head
	
	destroyNode(node);
	return OK;
}


/*
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
*/
