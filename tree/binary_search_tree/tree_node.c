#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include <string.h>
#include "tree_node.h"
#include "list.h"
#include "errors.h"

TreeNode *createTreeNode(const char *key) {
	TreeNode *node = (TreeNode *)malloc(1 * sizeof(TreeNode));

	if (node == NULL) {
		return NULL;
	}

	node->key = strdup(key);
	
	if (node->key == NULL) {
		free(node);
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->parent = NULL;

	node->list = createList();

	if (node->list == NULL) {
		return NULL;
	}

	return node;
}


void destroyTreeNode(TreeNode *node) {
	if (node == NULL) {
		return;
	}

	destroyList(node->list);
	free(node->key);
	free(node);
}


void printTreeNode(TreeNode *node) {
	if (node == NULL) {
		return;
	}

	printf("%s", node->key);
	printList(node->list);
}


bool nodeIsEmpty(TreeNode *node) {
	if (node == NULL || listIsEmpty(node->list)) {
		return 1;
	}

	return 0;
}


bool leaf(TreeNode *node) {
	if (node == NULL) return 0;
	return node->left == NULL && node->right == NULL;
}


int writeInfo(TreeNode *node, const char *info) { // добавление новой информации в узел дерева
	if (node == NULL || info == NULL) {
		return ALLOCATION_ERROR;
	}

	int status = Push(node->list, info);
	
	if (status != OK) {
		return status;
	}

	return OK;
}


int deleteInfo(TreeNode *node) { //удалит самую старую информацию
	if (node == NULL) {
		return ALLOCATION_ERROR;
	}

	int status = deleteEl(node->list);

	if (status != OK) {
		return status;
	}

	return status;
}

