#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

#ifndef NODE_H
#define NODE_H

typedef struct TreeNode {
	char *key;
	struct TreeNode *left;
	struct TreeNode *right;
	struct TreeNode *prev;
	struct TreeNode *next;
	struct TreeNode *parent;
	List *list; //список информации
} TreeNode;


TreeNode *createTreeNode(const char *);
void destroyTreeNode(TreeNode *);
void printTreeNode(TreeNode *);
bool nodeIsEmpty(TreeNode *);
bool leaf(TreeNode *);
int deleteInfo(TreeNode *);
int writeInfo(TreeNode *, const char *);

#endif
