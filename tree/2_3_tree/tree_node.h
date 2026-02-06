#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef TREE_NODE_H
#define TREE_NODE_H

typedef struct Key {
	unsigned int key;
	List *info;
} Key;

typedef struct TreeNode {
	unsigned int size;
	Key **keys;
	struct TreeNode **sons;
	struct TreeNode *parent;
} TreeNode;


Key *createKey();
void destroyKey(Key *);

//есть ли ключ в узле
int checkKey(TreeNode *, unsigned int);

TreeNode *createTreeNode();
void destroyTreeNode(TreeNode *);

//вставить в узел новый ключ или копировать уже существующий
int insertNewKey(TreeNode *, unsigned int, const char *);
int insertKey(TreeNode *, unsigned int, List *);

//удалить ключ из узла
int removeKey(TreeNode *, unsigned int);

//является ли узел листом, пустой ли ключ
int leaf(TreeNode *);
int empty(TreeNode *, unsigned int);

//удалить информацию из узла, дописать ее в узел
int deleteInfo(TreeNode *, unsigned int);
int writeInfo(TreeNode *, unsigned int, const char *);

#endif
