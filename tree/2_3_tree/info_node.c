#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info_node.h"
#include "errors.h"

InfoNode *createInfoNode(const char *info) {
	InfoNode *node = (InfoNode *)malloc(1 * sizeof(InfoNode));
	if (node == NULL) return NULL;

	node->next = NULL;
	node->info = strdup(info);

	if (node->info == NULL) {
		free(node);
		return NULL;
	}

	return node;
}


void destroyInfoNode(InfoNode *node) {
	if (node == NULL) {
		return;
	}

	free(node->info);
	free(node);
}


void printInfoNode(InfoNode *node) {
	if (node == NULL || node->info == NULL) {
		return;
	}

	printf("%s", node->info);
}

