#include "queue.h"
#include "errors.h"

QNode *createQNode(int data) {
	QNode *node = (QNode *)malloc(sizeof(QNode));
	if (node == NULL) return NULL;

	node->data = data;
	node->next = NULL;
	return node;
}

void destroyQNode(QNode *node) {
	if (node == NULL) return;
	free(node);
}


Queue *createQueue() {
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	if (queue == NULL) return NULL;

	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}


void destroyQueue(Queue *queue) {
	if (queue == NULL) return;

	QNode *tmp = NULL;
	QNode *curr = queue->head;

	while (curr != NULL) {
		tmp = curr->next;
		destroyQNode(curr);
		curr = tmp;
	}
}


int pushQueue(Queue *queue, int data) {
	if (queue == NULL) return ALLOCATION_ERROR;

	QNode *node = createQNode(data);
	if (node == NULL) return ALLOCATION_ERROR;
	
	if (emptyQueue(queue)) {
		queue->head = node;
	} else {
		queue->tail->next = node;
	}
	queue->tail = node;
	return OK;
}


int popQueue(Queue *queue) {
	if (queue == NULL) return ALLOCATION_ERROR;
	if (queue->head == NULL) return EMPTY;

	int data = queue->head->data;

	QNode *tmp = queue->head;
	if (queue->head == queue->tail) queue->tail = NULL;
	queue->head = queue->head->next;
	destroyQNode(tmp);

	return data;
}


int emptyQueue(Queue *queue) {
	if (queue == NULL) return 1;
	if (queue->head == NULL) return 1;
	return 0;
}


