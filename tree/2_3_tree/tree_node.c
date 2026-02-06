#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_node.h"
#include "list.h"
#include "errors.h"

#define KEYS 3
#define SONS 4

Key *createKey() {
	Key *key = (Key *)malloc(1 * sizeof(Key));
	if (key == NULL) return NULL;

	key->key = 0;
	key->info = createList();

	return key;
}

void destroyKey(Key *key) {
	if (key == NULL) return;

	destroyList(key->info);
	free(key);
}


int checkKey(TreeNode *node, unsigned int key) {
	if (node == NULL) return 0;

	for (unsigned int i = 0; i < node->size; i++) {
		if (node->keys[i]->key == key) {
			return 1;
			break;
		}
	}

	return 0;
}


TreeNode *createTreeNode() {
	TreeNode *node = (TreeNode *)malloc(1 * sizeof(TreeNode));
	if (node == NULL) return NULL;

	node->keys = (Key **)malloc(KEYS * sizeof(Key *));
	if (node->keys == NULL) return NULL;

	for (int i = 0; i < KEYS; i++) {
		node->keys[i] = createKey();
		if (node->keys[i] == NULL) return NULL;
	}

	node->sons = (TreeNode **)malloc(SONS * sizeof(TreeNode *));
	if (node->sons == NULL) return NULL;
	for (unsigned int i = 0; i < SONS; i++) node->sons[i] = NULL;

	node->parent = NULL;
	node->size = 0;

	return node;
}


void destroyTreeNode(TreeNode *node) {
	if (node == NULL) return;

	for (unsigned int i = 0; i < node->size; i++) {
		destroyKey(node->keys[i]);
	}
	
	free(node->keys);
	free(node->sons);
	free(node);
}


int insertNewKey(TreeNode *node, unsigned int key, const char *info) {
	if (node == NULL) return ALLOCATION_ERROR;
	int status = OK;

	if (node->size == 0) {
		node->keys[0]->key = key;
		status = Push(node->keys[0]->info, info);
		if (status != OK) return status;
	} else {
		unsigned int index = 0;
		while (index < node->size && key > node->keys[index]->key) {
			index++;
		}

		for (unsigned int i = node->size; i > index; i--) {
			node->keys[i]->key = node->keys[i - 1]->key;
			copylst(&(node->keys[i]->info), node->keys[i - 1]->info);
		}

		node->keys[index]->key = key;
		if (info != NULL) status = Push(node->keys[index]->info, info);
		if (status != OK) return status;

	}

	(node->size)++;
	return OK;
}


int insertKey(TreeNode *node, unsigned int key, List *info) {
        if (node == NULL) return ALLOCATION_ERROR;
        int status = OK;

        if (node->size == 0) {
                //if (node->keys[0] == NULL) { /////
		//	printf("NUUUUUUUUUUUULL\n"); /////
		//	return OK; //////
		//} /////

		node->keys[0]->key = key;
                copylst(&(node->keys[0]->info), info);
                if (status != OK) return status;
        } else {
                unsigned int index = 0;
                while (index < node->size && key > node->keys[index]->key) {
                        index++;
                }

                for (unsigned int i = node->size; i > index; i--) {
                        node->keys[i]->key = node->keys[i - 1]->key;
                        copylst(&(node->keys[i]->info), node->keys[i - 1]->info);
                }

                node->keys[index]->key = key;
                if (info != NULL) copylst(&(node->keys[index]->info), info);
                if (status != OK) return status;

        }

        (node->size)++;
        return OK;
}

//удаление ключа из листа, в котором два ключа
int removeKey(TreeNode *node, unsigned int key) {
	if (node == NULL) return ALLOCATION_ERROR;
	
	int status = OK;
	unsigned int index = 0;
	for (unsigned int i = 0; i < node->size; i++) {
		if (node->keys[i]->key == key) {
			index = i;
			break;
		}
	}
	//очищаем список информации
	while (!listIsEmpty(node->keys[index]->info)) {
		status = deleteEl(node->keys[index]->info);
		if (status != OK) return status;
	}

	for (unsigned int i = index; i < node->size; i++) {
		node->keys[i] = node->keys[i + 1]; //////
		node->sons[i] =  node->sons[i + 1];
	}

	node->keys[node->size - 1] = 0;
	node->sons[node->size - 1] = node->sons[node->size];
	node->sons[node->size] = NULL;

	(node->size)--;
	return OK;
}


int leaf(TreeNode *node) {
	if (node == NULL) return 1;
	for (unsigned int i = 0; i < node->size + 1; i++) {
		if (node->sons[i] != NULL) return 0;
	}
	return 1;
}


int empty(TreeNode *node, unsigned int key) {
	if (node == NULL) return 1;
	for (unsigned int i = 0; i < node->size; i++) {
		if (node->keys[i]->key == key) {
			if (listIsEmpty(node->keys[i]->info)) return 1;
			else return 0;
			break;
		}
	}
	return 1;
}


int writeInfo(TreeNode *node, unsigned int key, const char *info) { // добавление новой информации в узел дерева
	if (node == NULL || info == NULL) {
		return ALLOCATION_ERROR;
	}

	int status = OK;
	for (unsigned int i = 0; i < node->size; i++) {
		if (node->keys[i]->key == key) {
			status = Push(node->keys[i]->info, info);
			if (status != OK) return status;
			break;
		}
	}

	return OK;
}


int deleteInfo(TreeNode *node, unsigned int key) { //удалит информацию
	if (node == NULL) {
		return ALLOCATION_ERROR;
	}

	int status = OK;
	for (unsigned int i = 0; i < node->size; i++) {
		if (node->keys[i]->key == key) {
			status = deleteEl(node->keys[i]->info);
			if (status != OK) return status;
			break;
		}
	}

	return OK;
}

