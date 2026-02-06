#include <stdio.h>
#include <stdlib.h>
#include "tree_node.h"
#include "array.h"

#ifndef TREE_H
#define TREE_H

typedef struct Tree {
	TreeNode *root;
} Tree;


Tree *createTree();
void destroyTree(Tree *);
void printTree(TreeNode *, int); // форматированный вывод в виде дерева
void shellPrintTree(Tree *);
int traversingTree(Tree *, const char *); // обход дерева и вывод ключей с подстрокой
Array *findKey(Tree *, const char *);
Array *findOppositeKey(Tree *, const char *);
TreeNode *findMinKey(TreeNode *);
TreeNode *findMaxKey(TreeNode *);
int Insert(Tree *, const char *, const char *);
int Delete(Tree *, const char *);
int rewriteNode(TreeNode *, TreeNode *);
//int shellForDelete(Tree *, const char *);
//TreeNode *minimum(TreeNode *);
//TreeNode *recursiveDelete(TreeNode *, const char *);
int getFromFile(Tree *, const char *);
int getGVfile(Tree *, const char *);

#endif
	
