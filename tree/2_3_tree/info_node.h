#include <stdio.h>
#include <stdlib.h>

#ifndef INFO_NODE_H
#define INFO_NODE_H

typedef struct InfoNode {
	char *info;
	struct InfoNode *next;
} InfoNode;

InfoNode *createInfoNode(const char *);
void destroyInfoNode(InfoNode *);
void printInfoNode(InfoNode *);

#endif

