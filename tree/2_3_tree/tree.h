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
void destroyTree(Tree *); //shell
void destroyNode(TreeNode *); //recursion
void printTree(TreeNode *, int); // форматированный вывод в виде дерева
void shellPrintTree(Tree *);
void traverse(TreeNode *, unsigned int lb, unsigned int rb);

//find
Array *findKey(Tree *, unsigned int);
TreeNode *search(TreeNode *, unsigned int);
unsigned int num_abs(int);
TreeNode *findPrevious(TreeNode *, unsigned int);
TreeNode *findNext(TreeNode *, unsigned int);
Array **specialFind(Tree *, size_t *, unsigned int, unsigned int *, unsigned int *);
TreeNode *searchMin(TreeNode *);
TreeNode *searchMax(TreeNode *);

//insert
int insert(Tree *, unsigned int, const char *);
int split(TreeNode *);

//delete
int del(Tree *, unsigned int);
int mergeLeft(TreeNode *, TreeNode *);
int mergeRight(TreeNode *, TreeNode *);
int removeLeaf(Tree *, TreeNode *, unsigned int);
int repair(Tree *, TreeNode *);
int removeNode(Tree *, TreeNode *, unsigned int);

//work with files
int getFromFile(Tree *, const char *);
int getGVfile(Tree *, const char *);
void visualise(TreeNode *, FILE *);

#endif
	
