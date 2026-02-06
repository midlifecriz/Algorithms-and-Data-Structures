#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#ifndef LIST_H
#define LIST_H

typedef struct Edge {
	char *vertex;
	Array *ports;
} Edge;

typedef struct Node {
	Edge *edge;
	struct Node *next;
} Node;

typedef struct List {
	Node *head;
	Node *tail;
} List;

//Edge
Edge *createEdge(char *);
void destroyEdge(Edge *);

//Node
Node *createNode(Edge *);
void destroyNode();

//List
List *createList();
void destroyList(List *);
int push(List *, Edge *);
int del(List *, char *);

#endif 

