#include <stdlib.h>
#include <stdio.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct QNode {
	int data;
	struct QNode *next;
} QNode;


typedef struct Queue {
	QNode *head;
	QNode *tail;
} Queue;

//QNode
QNode *createQNode(int);
void destroyQNode(QNode *);

//Queue
Queue *createQueue();
void destroyQueue(Queue *);
int pushQueue(Queue *, int);
int popQueue(Queue *);
int emptyQueue(Queue *);

#endif
