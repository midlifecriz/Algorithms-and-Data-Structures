#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_node.h"
#include "array.h"
#include "tree.h"
#include "errors.h"
#include "my_readline.h"

#define KEYSIZE 50
#define DECIMAL 10

Tree *createTree() {
	Tree *tree = (Tree *)malloc(1 * sizeof(Tree));
	if (tree == NULL) return NULL;

	tree->root = NULL;

	return tree;
}


void destroyTree(Tree *tree) {
	if (tree == NULL) return;

	if (tree->root == NULL) {
		free(tree);
		return;
	}

	TreeNode *curr = tree->root;
	destroyNode(curr); //recursion
	free(tree);
}


void destroyNode(TreeNode *node) {
	if (node != NULL) {
		for (unsigned int i = 0; i <= node->size; i++) {
			if (node->sons[i] != NULL) {
				destroyNode(node->sons[i]);
			} else {
				destroyTreeNode(node);
				break;
			}
		}

	}
}


void shellPrintTree(Tree *tree) { // shell for printTree
	if (tree == NULL) return;

	printf("2-3 TREE:\n");

	if (tree->root == NULL) {
		printf("Tree is empty\n");
		return;
	}

	printTree(tree->root, 0); // 0 - level
}


void printTree(TreeNode *curr, int level) { // recursive print
	int i = level;
	int tmp = 0;

	if (curr != NULL) {
		if (curr->size == 1) {
			//2 sons, 1 key
			printTree(curr->sons[1], level + 1);

			while (i-- > 0) printf("  ");
			printf("%u\n", curr->keys[0]->key);

			printTree(curr->sons[0], level + 1);
		} else { 
			//3 sons, 2 keys
			if (curr->sons[2] != NULL) printTree(curr->sons[2], level + 1);
 
			tmp = i;
			while (i-- > 0) printf("  ");
			printf("%u\n", curr->keys[1]->key);
			
			if (curr->sons[1] != NULL) printTree(curr->sons[1], level + 1);
			
			while(tmp-- > 0) printf("  ");
			printf("%u\n", curr->keys[0]->key);

			if (curr->sons[0] != NULL) printTree(curr->sons[0], level + 1);
		}
	}
}


void traverse(TreeNode *curr, unsigned int lb, unsigned int rb) {
	if (curr != NULL) {
		if (curr->size == 1) {
			traverse(curr->sons[1], lb, rb);
			if (curr->keys[0]->key >= lb && curr->keys[0]->key <= rb) {
				printf("%u  ", curr->keys[0]->key);
			}
			traverse(curr->sons[0], lb, rb);
		} else {
			traverse(curr->sons[2], lb, rb);
			if (curr->keys[1]->key >= lb && curr->keys[1]->key <= rb) {
				printf("%u  ", curr->keys[1]->key);
			}
			traverse(curr->sons[1], lb, rb);
			if (curr->keys[0]->key >= lb && curr->keys[0]->key <= rb) {
				printf("%u  ", curr->keys[0]->key);
			}
			traverse(curr->sons[0], lb, rb);
		}
	}
	printf("\n");
}


TreeNode *searchMax(TreeNode *root) {
	if (root == NULL) return NULL;

	TreeNode *curr = root;
	while (!leaf(curr)) {
		if (curr->size == 1) curr = curr->sons[1];
		else curr = curr->sons[2];
	}

	return curr;
}


TreeNode *searchMin(TreeNode *root) {
	if (root == NULL) return NULL;

	TreeNode *curr = root;

	while (!leaf(curr)) curr = curr->sons[0];
	return curr;
}


Array *findKey(Tree *tree, unsigned int key) {
	if (tree == NULL) {
		return NULL;
	}

	if (tree->root == NULL) {
		return NULL;
	}
	
	int status = OK;

	Array *array = createArray();
	if (array == NULL) return NULL;

	TreeNode *curr = search(tree->root, key);

	for (unsigned int i = 0; i < curr->size; i++) { //check keys in node
		if (curr->keys[i]->key == key) {
			status = addArray(array, curr->keys[i]->info);
			if (status != OK) {
				destroyArray(array);
				return NULL;
			}
		}
	}

	if (array->size == 0) { // key not found
		destroyArray(array);
		array = NULL;
	}

	return array; // return NULL if key was not found
}


TreeNode *findNext(TreeNode *root, unsigned int x) {
	TreeNode *node = search(root, x);
	if (node->keys[0]->key > x) return node;
	else if (node->size == 2 && x < node->keys[1]->key) return node;

	unsigned int pos = 0;
	while (node != NULL) {
		for (unsigned int i = 0; i <= node->parent->size; i++) {
			if (node == node->parent->sons[i]) {
				pos = i;
				break;
			}
		}

		if (pos != node->parent->size) {
			//node has right brother
			node = searchMin(node->parent->sons[pos + 1]);
			return node;
		} else {
			node = node->parent;
		}
	}
	return node; //null
}


TreeNode *findPrevious(TreeNode *root, unsigned int x) {
	TreeNode *node = search(root, x);
	if (node->keys[node->size - 1]->key < x) return node;
	else if (x > node->keys[0]->key) return node;

	unsigned int pos = 0; 
	while (node != NULL) {
		for (unsigned int i = 0; i <= node->parent->size; i++) {
			if (node == node->parent->sons[i]) {
				pos = i;
				break;
			}
		}

		if (pos != 0) {
			//node has left brother
			node = searchMax(node->parent->sons[pos - 1]);
			return node;
		} else { 
			node = node->parent;
		}
	}
	return node; //null
}


unsigned int num_abs(int x) {
	if (x < 0) x = -1 * x;
	return x;
}


//TODO
Array **specialFind(Tree *tree, size_t *size, unsigned int x, unsigned int *key1, unsigned int *key2) {
	if (tree == NULL || tree->root == NULL) return NULL;

	int status = OK;

	TreeNode *prev = findPrevious(tree->root, x);
	TreeNode *next = findNext(tree->root, x);

	unsigned int prev_index = 0;
	unsigned int next_index = 0;

	Array **arrays = (Array **)calloc(2, sizeof (Array *));
	if (arrays == NULL) return NULL;

	if (prev != NULL) {
		if (prev->size == 1) {
			prev_index = 0;
			*key1 = prev->keys[0]->key;
		} else {
			if (x > prev->keys[1]->key) {
				prev_index = 1;
				*key1 = prev->keys[1]->key;
			} else {
				prev_index = 0;
				*key1 = prev->keys[0]->key;
			}
		}
	}

	if (next != NULL) {
		if (next->size == 1) {
			next_index = 0;
			*key2 = next->keys[0]->key;
		} else {
			if (x < next->keys[0]->key) {
				next_index = 0;
				*key2 = next->keys[0]->key;
			} else {
				next_index = 1;
				*key2 = next->keys[1]->key;
			}
		}
	}

	//need to choose nearest
	if (next != NULL && prev != NULL) {
		if (num_abs(x - (*key1)) < num_abs(x - (*key2))) {
			Array *array = createArray();
			status = addArray(array, prev->keys[prev_index]->info);
			if (status != OK) {
				free(arrays);
				destroyArray(array);
				return NULL;
			}
			arrays[0] = array;
			*size = 1;
			return arrays;
		} else if (num_abs(x - (*key1)) > num_abs(x - (*key2))) {
			Array *array = createArray();
			status = addArray(array, next->keys[next_index]->info);
			arrays[0] = array;
			*size = 1;
			*key1 = *key2;
			return arrays;
		} else { //abs ==
			Array *array1 = createArray();
			Array *array2 = createArray();
			status = addArray(array1, prev->keys[prev_index]->info);
			status = addArray(array2, next->keys[next_index]->info);

			arrays[0] = array1;
			arrays[1] = array2;
			*size = 2;
			return arrays;
		}
	} else if (prev != NULL) {
		Array *array = createArray();
		status = addArray(array, prev->keys[prev_index]->info);
		arrays[0] = array;
		*size = 1;
		return arrays;
	} else if (next != NULL) {
		Array *array = createArray();
		status = addArray(array, next->keys[next_index]->info);
		arrays[0] = array;
		*size = 1;
		*key1 = *key2;
		return arrays;
	} else {
		free(arrays);
		return NULL;
	}
	return arrays;
}


// нужно проверить на предмет >= / <=
TreeNode *search(TreeNode *root, unsigned int key) {
	if (root == NULL) return NULL;
	
	TreeNode *curr = root;
	if (checkKey(curr, key)) return curr; //key in the node

	while (curr != NULL && !leaf(curr)) {
		//2 sons
		if (curr->size == 1) {
			if (curr->keys[0]->key < key) {
				curr = curr->sons[1];
			} else {
				curr = curr->sons[0];
			}
		//3 sons
		} else if (curr->keys[1]->key < key) {
			curr = curr->sons[2];
		} else if (curr->keys[0]->key < key) {
			curr = curr->sons[1];
		} else {
			curr = curr->sons[0];
		}
		
		//printf("KEY: %u\n: ", curr->keys[0]->key);
		if (checkKey(curr, key)) return curr; //key in the node
	}

	return curr;
}

 
int insert(Tree *tree, unsigned int key, const char *info) {
	if (tree == NULL) return ALLOCATION_ERROR;

	int status = OK;

	if (tree->root == NULL) { //insert to the root
		tree->root = createTreeNode();
		if (tree->root == NULL) return ALLOCATION_ERROR;

		tree->root->keys[0]->key = key;
		tree->root->size = 1;
		status = writeInfo(tree->root, key, info);
		tree->root->parent = NULL;

		if (status != OK) {
			destroyTreeNode(tree->root);
			tree->root = NULL;
			return status;
		}
		return OK;
	}

	TreeNode *curr = search(tree->root, key);
	//printf("INSERT here =>: ");
	//for (unsigned int i = 0; i < curr->size; i++) printf("%u  ",curr->keys[i]->key);

	//duplicate keys
	for (unsigned int i = 0; i < curr->size; i++) {
		if (curr->keys[i]->key == key) {
			status = writeInfo(curr, key, info);
			if (status != OK) return status;
			return OK;
		}
	}

	// insert 
	status = insertNewKey(curr, key, info); //insert and sort keys
	if (status != OK) return status;

	TreeNode *parent = NULL;
	while (curr->size == 3) {
		if (curr == tree->root) {
			status = split(curr);
			break;
		} else {
			parent = curr->parent;
			status = split(curr);
			curr = parent;
		}
	}

	return OK;
}	

// NEED TO FINISH WRITING
int split(TreeNode *curr) { //unsigned int key, const char *info) {
	if (curr == NULL) return ALLOCATION_ERROR;
	if (curr->size < 3) return OK;

	//split node
	TreeNode *child1 = createTreeNode();
	if (child1 == NULL) return ALLOCATION_ERROR;
	TreeNode *child2 = createTreeNode();
	if (child2 == NULL) return ALLOCATION_ERROR;

	child1->keys[0]->key = curr->keys[0]->key;
	child2->keys[0]->key = curr->keys[2]->key;

	copylst(&(child1->keys[0]->info), curr->keys[0]->info);//
	copylst(&(child2->keys[0]->info), curr->keys[2]->info);//

	child1->size = 1;
	child2->size = 1;
 
	if (!leaf(curr)) {
		//child1
		child1->sons[0] = curr->sons[0]; //first son
		child1->sons[0]->parent = child1;

		child1->sons[1] = curr->sons[1]; //second son
		child1->sons[1]->parent = child1;

		//child2
		child2->sons[0] = curr->sons[2]; //third son
		child2->sons[0]->parent = child2;

		child2->sons[1] = curr->sons[3];//forth son
		child2->sons[1]->parent = child2;
	}
		
	//curr is root
	if (curr->parent == NULL) {
		curr->keys[0]->key = curr->keys[1]->key; //middle key
		copylst(&(curr->keys[0]->info), curr->keys[1]->info); //

		for (unsigned int i = 1; i < curr->size; i++) {
			curr->keys[i]->key = 0;
		}

		curr->size = 1;

		curr->parent = NULL;
		curr->sons[0] = child1;
		curr->sons[1] = child2;
		for (unsigned int i = 2; i < 4; i++) { //size+1
			curr->sons[i] = NULL;
		}

		child1->parent = curr;
		child2->parent = curr;
	} else { 
		int status = insertNewKey(curr->parent, curr->keys[1]->key, NULL);
		if (status != OK) return status;

		for (unsigned int i = 0; i < curr->parent->size + 1; i++) { //+1
			if (curr->parent->sons[i] == curr) curr->parent->sons[i] = NULL;
		}
			
		for (unsigned int i = 0; i < curr->parent->size + 1; i++) {
			if (curr->parent->sons[i] == NULL) {
				//тогда вставляем child1 на i, child2 на i+1
				for (unsigned int j = 3; j > i + 1; j--) { //+1?
					curr->parent->sons[j] = curr->parent->sons[j - 1];
				}

				curr->parent->sons[i] = child1;
				curr->parent->sons[i + 1] = child2;
				break;
			}
		}

		child1->parent = curr->parent;
		child2->parent = curr->parent;

		destroyTreeNode(curr);
	}

	return OK;
}


void swap(void *a, void *b, size_t width) {
	void *tmp = malloc(width);
	memcpy(tmp, b, width);
	memcpy(b, a, width);
	memcpy(a, tmp, width);
	free(tmp);
}


//TODO
int del(Tree *tree, unsigned int key) {
	if (tree == NULL) return ALLOCATION_ERROR;
	if (tree->root == NULL) return EMPTY_TREE;

	TreeNode *node = search(tree->root, key);
	if (node == NULL) return KEY_NOT_FOUND;
	int status = KEY_NOT_FOUND;

	for (unsigned int i = 0; i < node->size; i++) {
		if (node->keys[i]->key == key) {
			status = OK;
			break;
		}
	}
	if (status == KEY_NOT_FOUND) return status;

	status = deleteInfo(node, key);
	if (status != OK) return status;
	if (!empty(node, key)) return OK;

	//delete node
	if (leaf(node)) {
		if (node->size == 2) {
			status = removeKey(node, key);
			if (status != OK) return status;
		} else {
			removeLeaf(tree, node, key);
		}
	} else {
		removeNode(tree, node, key);
	}
	return OK;
}


int mergeLeft(TreeNode *node1, TreeNode *node2) {
	if (node1 == NULL || node2 == NULL) return ALLOCATION_ERROR;

	printf("size %u\n", node1->size);
	for (unsigned int i = 0; i < node2->size; i++) {
		if (node1->keys[node1->size] == NULL) {
			printf("NUUUULL");
			return OK;
		}
		node1->keys[node1->size]->key = node2->keys[i]->key;
		copylst(&(node1->keys[node1->size]->info), node2->keys[i]->info);
		node1->sons[node1->size] = node2->sons[i];
		(node1->size)++;
	}
	node1->sons[node1->size] = node2->sons[node2->size];

	for (unsigned int i = 0; i <= node1->size; i++) {
		if (node1->sons[i] == NULL) break;
		node1->sons[i]->parent = node1;
	}

	destroyTreeNode(node2);
	return OK;
}


int mergeRight(TreeNode *node1, TreeNode *node2) {
	if (node1 == NULL || node2 == NULL) return ALLOCATION_ERROR;

	for (unsigned int i = 0; i < node2->size; i++) {
		node1->keys[node1->size]->key = node2->keys[i]->key;
		copylst(&(node1->keys[node1->size]->info), node2->keys[i]->info);
	}

	for (unsigned int i = 0; i <= node1->size; i++) {
		if (node1->sons[i] == NULL) break;
		node1->sons[i]->parent = node1;
	}

	destroyTreeNode(node2);
	return OK;
}


//CASE: delete key from leaf
int removeLeaf(Tree *tree, TreeNode *node, unsigned int key) {
	if (tree == NULL) return ALLOCATION_ERROR;
	if (node == NULL || tree->root == NULL) return ALLOCATION_ERROR;
	int status = OK;

	if (node == tree->root && node->size == 1) {
		status = removeKey(node, key);
		if (status != OK) return status;
		tree->root = NULL;
		destroyTreeNode(node);
		return OK;
	}

	if (node == tree->root || node->size == 2) { //size == 2
		status = removeKey(node, key);
		return status;
	}

	TreeNode *curr = node;
	/*unsigned int index = 0; //индекс ключа в узле

	for (unsigned int i = 0; i < curr->size; i++) {
		if (curr->keys[i]->key == key) {
			index = i;
			break;
		}
	} */

	TreeNode *parent = curr->parent;
	unsigned int position = 0; //позиция узла по отношению к родителю

	for (unsigned int i = 0; i <= parent->size; i++) {
		if (parent->sons[i] == curr) {
			position = i;
			break;
		}
	}

	Key *key1 = NULL;
	Key *key2 = NULL;
	if (position == 0) { //curr is left son
		if (parent->sons[position + 1]->size == 2) {
			//минимальный ключ правого брата
			key1 = parent->sons[position + 1]->keys[0];
			//ключ разделитель у родителя
			key2 = parent->keys[position];

			status = insertKey(curr, key2->key, key2->info);
			if (status != OK) return status;
			status = removeKey(curr, key);
			if (status != OK) return status;

			parent->keys[position]->key = key1->key;
			copylst(&(parent->keys[position]->info), key1->info);

			status = removeKey(parent->sons[position + 1], key1->key);
			if (status != OK) return status;
		} else {
			status = removeKey(curr, key);
			if (curr->size == 0) repair(tree, curr);
		}
	} else {
		//curr is right son 
		if (position == parent->size) {
			//left brother has 2 keys
			if (parent->sons[position - 1]->size == 2) {
				TreeNode *tmp = parent->sons[position - 1];
				key1 = tmp->keys[tmp->size - 1];
				key2 = parent->keys[position - 1];
				
				status = insertKey(curr, key2->key, key2->info);
				status = removeKey(curr, key); /////

				parent->keys[position - 1]->key = key1->key;
				copylst(&(parent->keys[position - 1]->info), key1->info);
				status = removeKey(tmp, key1->key);
			} else {
				status = removeKey(curr, key);
				if (curr->size == 0) repair(tree, curr);
			}
		} else { //есть братья и справа и слева
			 if (parent->sons[position + 1]->size == 2) {
				 //right brother has 2 keys
				 key1 = parent->sons[position + 1]->keys[0];
				 key2 = parent->keys[position];
				 
				 status = insertKey(curr, key2->key, key2->info);
				 status = removeKey(curr, key);

				 parent->keys[position]->key = key1->key;
				 copylst(&(parent->keys[position]->info), key1->info);
				 status = removeKey(parent->sons[position + 1], key1->key);
			} else {
				if (parent->sons[position - 1]->size == 2) {
					//left brother has 2 keys
					TreeNode *tmp = parent->sons[position - 1];
					key1 = tmp->keys[tmp->size - 1];
					key2 = parent->keys[position - 1];

					status = insertKey(curr, key2->key, key2->info);
					status = removeKey(curr, key);

					parent->keys[position - 1]->key = key1->key;
					copylst(&(parent->keys[position - 1]->info), key1->info);
					status = removeKey(tmp, key1->key);
				} else {
					//у обоих братьев меньше 2 ключей
					status = removeKey(curr, key);
					if (curr->size == 0) repair(tree, curr);
				}
			}
		}
	}
	return OK;
}


int repair(Tree *tree, TreeNode *node) {
	if (node == NULL) return ALLOCATION_ERROR;

	if (node->parent == NULL && node->size == 0) {
		if (node->sons[0] != NULL) {
			tree->root = node->sons[0];
			node->sons[0]->parent = NULL;
			//node->sons[0] = NULL; /////
		} else {
			destroyTreeNode(node);
		}
		return OK; /////
	}

	TreeNode *curr = node;
	TreeNode *parent = curr->parent;
	TreeNode *tmp = NULL;
	//Key *key1 = NULL;
	//Key *key2 = NULL;
	int status = OK;
	unsigned int position = 0;

	for (unsigned int i = 0; i <= parent->size; i++) {
		if (parent->sons[i] == curr) {
			position = i;
			break;
		}
	}

	//curr is left son
	if (position == 0) {
		status = insertKey(curr, parent->keys[position]->key, parent->keys[position]->info);
		if (status != OK) return status;
		mergeLeft(curr, parent->sons[position + 1]);
		parent->sons[position + 1] = curr;
		parent->sons[position] = NULL;
		status = removeKey(parent, parent->keys[position]->key);

		if (curr->size == 3) {
			while (curr->size == 3) {
				if (curr == tree->root) {
					status = split(curr);
					break;
				} else {
					tmp = curr->parent;
					status = split(curr);
					curr = tmp;
				}
			}
		} else {
			if (parent->size == 0) repair(tree, parent);
		}
	} else {
		//curr is right son
		if (position == parent->size) {
			status = insertKey(parent->sons[position - 1], parent->keys[position - 1]->key, parent->keys[position - 1]->info);
			unsigned int size = curr->size;
			status = mergeLeft(parent->sons[position - 1], curr);
			
			parent->sons[position] = parent->sons[position - 1];
			parent->sons[position - 1] = NULL;
			status = removeKey(parent, parent->keys[position - 1]->key);
			TreeNode *tmp = parent->sons[position];
			TreeNode *temp = NULL;
			
			if (size == 2) { //curr->size
				while (tmp->size == 2) {
					if (tmp == tree->root) {
						status = split(tmp);
						break;
					} else {
						temp = tmp->parent;
						status = split(tmp);
						tmp = temp;
					}
				}
			} else {
				if (parent->size == 0) repair(tree, parent);
			}
		} else {
			//curr has left and right brothers
			status = insertKey(curr, parent->keys[position]->key, parent->keys[position]->info);
			mergeLeft(curr, parent->sons[position + 1]);
			parent->sons[position + 1] = curr;
			parent->sons[position] = NULL;
			
			status = removeKey(parent, parent->keys[position]->key);
			
			if (curr->size == 3) { ///// was 2
				while (curr->size == 3) { ///// was 2
					if (curr == tree->root) {
						status = split(curr);
						break;
					} else {
						tmp = curr;
						status = split(curr);
						curr = tmp;
					}
				}
			} else {
				if (parent->size == 0) repair(tree, parent);
			}
		}
	}
	return OK;
}

//Удаление из произвольного узла
int removeNode(Tree *tree, TreeNode *node, unsigned int key) {
	if (node == NULL) return ALLOCATION_ERROR;

	TreeNode *curr = node;
	int status = OK;
	unsigned int index = 0;
	//unsigned int pos = 0; //position

	//позиция ключа в узле node
	for (unsigned int i = 0; i < node->size; i++) {
		if (node->keys[i]->key == key) {
			index = i;
			break;
		}
	}

	/*
	//позиция узла node среди детей его родителя
	if (node->parent != NULL) {
		for (unsigned int i = 0; i <= node->parent->size; i++) {
			if (node->parent->sons[i] == node) {
				pos = i;
				break;
			}
		}
	} */

	//находим наименьший ключ в правом поддереве
	curr = curr->sons[index + 1];
	Key *new_key = curr->keys[0];
	while (!leaf(curr)) curr = curr->sons[0];

	if (curr->size == 2) {
		new_key = curr->keys[0];
		status = removeKey(curr, new_key->key);
		if (status != OK) return status;
		node->keys[index]->key = new_key->key;
		copylst(&(node->keys[index]->info), new_key->info);
	} else {
		curr = node;
		//ищем наибольший ключ в левом поддереве
		curr = curr->sons[index];
		new_key = curr->keys[curr->size - 1];
		while (!leaf(curr)) curr = curr->sons[curr->size];

		new_key = curr->keys[curr->size - 1];
		node->keys[index]->key = new_key->key;
		copylst(&(node->keys[index]->info), new_key->info);

		if (curr->size == 2) {
			status = removeKey(curr, new_key->key);
		} else {
			status = removeLeaf(tree, curr, new_key->key);
		}
	}
	return OK;
}


int getFromFile(Tree *tree, const char *filename) {
	if (tree == NULL || filename == NULL) return ALLOCATION_ERROR;

	FILE *file = fopen(filename, "r");
	if (file == NULL) return READING_FILE_ERROR;

	unsigned int key = 0;
	char *info = NULL;

	char *str = fileReadline(file);
	int status = OK;

	while (str != NULL) { 
		key = atoi(str);
		info = fileReadline(file);

		if (info == NULL) {
			break;
		}

		status = insert(tree, key, info);
		if (status != OK) return status;

		free(info);
		str = fileReadline(file);
	}

	fclose(file);
	return OK;
}


//TODO
int getGVfile(Tree *tree, const char *filename) {
	if (tree == NULL) return ALLOCATION_ERROR;
	if (tree->root == NULL) return EMPTY_TREE;

	FILE *file = fopen(filename, "w");
	if (file == NULL) return READING_FILE_ERROR;

	fprintf(file, "digraph Tree {\n");
	TreeNode *curr = tree->root;

	visualise(curr, file); //recursive
	fprintf(file, "\n}\n");

	fclose(file);
	return OK;
}


void visualise(TreeNode *curr, FILE *file) {
	char *key = NULL;
	char *key1 = NULL;

	if (curr != NULL) {
		//printf("AYAYAYAYAYAYAYAYA");
		if (curr->size == 1) {
			key = (char *)malloc(KEYSIZE * sizeof(char));
			if (key == NULL) return;
			sprintf(key, "%u", curr->keys[0]->key);

			fprintf(file, "\t%s;\n", key);
		} else {
			key = (char *)malloc(KEYSIZE * sizeof(char));
			if (key == NULL) return;
			sprintf(key, "%u %u", curr->keys[0]->key, curr->keys[1]->key);

			fprintf(file, "\t%s;\n", key);
		}
		
		if (leaf(curr)) return;
		for (unsigned int i = 0; i <= curr->size; i++) {
			if (curr->size == 1) {
				if (curr->sons[i]->size == 1) {
					key1 = (char *)malloc(KEYSIZE * sizeof(char));
                        		if (key1 == NULL) return;
                        		sprintf(key1, "%u", curr->keys[0]->key);

					fprintf(file, "\t%s -> %s;\n", key, key1);
				} else {
					key1 = (char *)malloc(KEYSIZE * sizeof(char));
	                        	if (key1 == NULL) return;
        	                	sprintf(key1, "%u %u", curr->sons[i]->keys[0]->key, curr->sons[i]->keys[1]->key);

					fprintf(file, "\t%s -> %s;\n", key, key1);
				}
			} else {
				if (curr->sons[i]->size == 1) {
					key1 = (char *)malloc(KEYSIZE * sizeof(char));
                        		if (key1 == NULL) return;
                        		sprintf(key1, "%u", curr->keys[0]->key);

					fprintf(file, "\t%s -> %s;\n", key, key1);
				} else {
                        		key1 = (char *)malloc(KEYSIZE * sizeof(char));
                        		if (key1 == NULL) return;
                        		sprintf(key1, "%u %u", curr->sons[i]->keys[0]->key, curr->sons[i]->keys[1]->key);

					fprintf(file, "\t%s -> %s;\n", key, key1);
				}
			}
		}

		free(key);
		free(key1);

		visualise(curr->sons[0], file);
		visualise(curr->sons[1], file);
		if (curr->size == 2) visualise(curr->sons[2], file);
	}
}

