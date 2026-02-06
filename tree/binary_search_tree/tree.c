#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_node.h"
#include "array.h"
#include "tree.h"
#include "errors.h"
#include "my_readline.h"


Tree *createTree() {
	Tree *tree = (Tree *)malloc(1 * sizeof(Tree));

	if (tree == NULL) {
		return NULL;
	}

	tree->root = NULL;

	return tree;
}


void destroyTree(Tree *tree) {
	if (tree == NULL) {
		return;
	}

	if (tree->root == NULL) {
		free(tree);
		return;
	}

	TreeNode *current = findMinKey(tree->root);
	TreeNode *tmp = NULL;

	while (current != NULL) {
		printf("DESTROY: %s\n", current->key);
		tmp = current;
		current = current->next;

		destroyTreeNode(tmp);
	}

	free(tree);
}


void shellPrintTree(Tree *tree) { // shell for printTree
	if (tree == NULL) {
		return;
	}

	printf("BINARY SEARCH TREE:\n");

	if (tree->root == NULL) {
		printf("Tree is empty\n");
		return;
	}

	printTree(tree->root, 0); // 0 - level
}


void printTree(TreeNode *current, int level) { // recursive print
	int i = level;

	if (current != NULL) {
		printTree(current->right, level + 1);

		while (i-- > 0) {
			printf("  ");
		}

		printf("%s\n", current->key);
		printTree(current->left, level + 1);
	}
}


int traversingTree(Tree *tree, const char *substring) {
	if (tree == NULL) {
		return ALLOCATION_ERROR;
	}

	if (tree->root == NULL) {
		return SUBSTRING_NOT_FOUND;
	}

	TreeNode *current = findMinKey(tree->root); // beginning
	size_t sub_len = strlen(substring);
	int status = SUBSTRING_NOT_FOUND;

	//int i = 1; 
	while (current != NULL) {
		printf("идем в %s\n", current->key);
		if (strncmp(current->key, substring, sub_len) == 0) {
			printf(current->key);
			printf("\n");
			status = OK;
		}
		
		current = current->next;
	}

	return status;
}


Array *findKey(Tree *tree, const char *key) {
	if (tree == NULL || key == NULL) {
		return NULL;
	}

	if (tree->root == NULL) {
		return NULL;
	}
	
	int status = OK;

	TreeNode *current = tree->root;
	Array *array = createArray();

	if (array == NULL) {
		return NULL;
	}

	while (current != NULL) {
		if (strcmp(current->key, key) == 0) { //ключ найден
			status = addElem(array, current->key);
			status = addInfo(array, current->list);

			if (status != OK) {
				return NULL;
			}

			return array;
		}
		
		if (strcmp(key, current->key) < 0) { //идем в left
			current = current->left;
		} else { // идем в right
			current = current->right;
		}
	}

	if (array->size == 0) { // key not found
		destroyArray(array);
		array = NULL;
	}

	return array; // return NULL if key was not found
}


Array *findOppositeKey(Tree *tree, const char *key) {
	if (tree == NULL || key == NULL) {
		return NULL;
	}

	if (tree->root == NULL) {
		return NULL;
	}

	int status = OK;
	Array *array = createArray();

	if (array == NULL) {
		return NULL;
	}
	
	TreeNode *min = findMinKey(tree->root);
	TreeNode *max = findMaxKey(tree->root);

	if (abs(strcmp(key, max->key)) > abs(strcmp(key, min->key))) {
		status = addElem(array, max->key);
		status = addInfo(array, max->list);

		if (status != OK) {
			free(array);
			return NULL;
		}

		return array;
	}

	status = addElem(array, min->key);
	status = addInfo(array, min->list);

	if (status != OK) {
		free(array);
		return NULL;
	}

	return array;
}


TreeNode *findMinKey(TreeNode *root) {
	if (root == NULL) {
		return NULL;
	}

	TreeNode *current = root;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}


TreeNode *findMaxKey(TreeNode *root) {
	if (root == NULL) {
		return NULL;
	}

	TreeNode *current = root;
	
	while (current->right != NULL) {
		current = current->right;
	}

	return current;
}

//TODO
int Insert(Tree *tree, const char *key, const char *info) { // прошить
	if (tree == NULL) {
		return ALLOCATION_ERROR;
	}

	int status = OK;

	if (tree->root == NULL) { // добавление в корень
		tree->root = createTreeNode(key);

		if (tree->root == NULL) {
			return ALLOCATION_ERROR;
		}

		status = writeInfo(tree->root, info); 

		if (status != OK) {
			destroyTreeNode(tree->root);
			tree->root = NULL;
			return status;
		}

		return OK;
	}

	TreeNode *current = tree->root;
	TreeNode *parent = NULL;
	TreeNode *previous = NULL;

	while (current != NULL) {
		previous = parent;
		parent = current;

		if (strcmp(key, current->key) == 0) {
			status = writeInfo(current, info);

			if (status != OK) {
				return status;
			}

			return OK;
		}
		
		if (strcmp(key, current->key) < 0) { // идем в left
			current = current->left;
		} else {
			current = current->right;
		}
	}

	TreeNode *node = createTreeNode(key); // иначе создаем новый узел

	if (node == NULL) {
		return ALLOCATION_ERROR;
	}

	status = writeInfo(node, info); //записали инфу в узел

	if (status != OK) {
		return status;
	}

	if (strcmp(key, parent->key) < 0) { // вставка в левое
		if (previous != NULL && previous->right == parent) {
			previous->next = node;
			node->prev = previous; ///
		}

		node->next = parent;
		parent->prev = node; ///
		parent->left = node;
		node->parent = parent;
		
	} else { // вставка в правое
		node->next = parent->next;
		if (parent->next != NULL) parent->next->prev = node; ///
		parent->next = node;
		node->prev = parent; ///
		parent->right = node;
		node->parent = parent;
	}

	return OK;
}
	
//TreeNode *search(TreeNode *root, const char *key) {
//	if (root == NULL) return NULL;
//}


//TODO
int Delete(Tree *tree, const char *key) {
	if (tree == NULL || key ==  NULL) return ALLOCATION_ERROR;

	TreeNode *curr = tree->root;

	while (curr != NULL && strcmp(key, curr->key) != 0) {
		if (strcmp(key, curr->key) < 0) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}

	if (curr == NULL) return KEY_NOT_FOUND;

	if (strcmp(key, curr->key) == 0) {
		int status = deleteInfo(curr);
		if (status != OK) return status;
	}
	
	if (!nodeIsEmpty(curr)) return OK;

	// node is empty, delete
	TreeNode *del = NULL;

	// CASE 1
	if (leaf(curr)) {
		if (curr == tree->root) {
			tree->root = NULL;
			destroyTreeNode(curr);
			return OK;
		}

		if (curr->prev != NULL) curr->prev->next = curr->next;
		if (curr->next != NULL) curr->next->prev = curr->prev;

		if (curr->parent->left == curr) curr->parent->left = NULL;
		else curr->parent->right = NULL;

		destroyTreeNode(curr);
	}

	//CASE 2: only left son
	else if (curr->left != NULL && curr->right == NULL) {
		del = curr->left;
		if (curr->prev != NULL) curr->prev->next = curr->next;
		if (curr->next != NULL) curr->next->prev = curr->prev; //???
		
		if (curr == tree->root) tree->root = del;
		else if (curr->parent->right == curr) curr->parent->right = del;
		else curr->parent->left = del;
		del->parent = curr->parent;

		destroyTreeNode(curr);
	}

	//CASE 3: only right son
	else if (curr->right != NULL && curr->left == NULL) {
		del = curr->right;

		if (curr->prev != NULL) curr->prev->next = curr->next;
		if (curr->next != NULL) curr->next->prev = curr->prev;
		
		if (curr == tree->root) {
			tree->root = del;
		} else if (curr->parent->right == curr) {
			curr->parent->right = del;
		} else {
			curr->parent->left = del;
		}

		del->parent = curr->parent;

		destroyTreeNode(curr);
	}

	//CASE 4: 2 sons
	else { 
		del = findMaxKey(curr->left);

		//if (curr->prev != NULL) curr->prev->next = curr->next;
		//if (curr->next != NULL) curr->next->prev = curr->prev;

		//if (curr->parent != NULL) {
		//	if (curr->parent->left == curr) curr->parent->left = del;
		//	else curr->parent->right = del;
		//}
		
		rewriteNode(curr, del);
		//delete del
		if (del->prev != NULL) del->prev->next = del->next;
		if (del->next != NULL) del->next->prev = del->prev;

		if (leaf(del)) {
			if (del->parent->left == del) del->parent->left = NULL;
			else del->parent->right = NULL;
		} else { //left son
			if (del->parent->left == del) del->parent->left = del->left;
			else del->parent->right = del->left;
			del->left->parent = del->parent;
		}

		destroyTreeNode(del);
	}

	return OK;
}


int rewriteNode(TreeNode *a, TreeNode *b) {
	if (a == NULL || b == NULL) return ALLOCATION_ERROR;

	destroyList(a->list);
	a->list = copyList(b->list);
	if (a->list == NULL) return ALLOCATION_ERROR;

	free(a->key);
	a->key = strdup(b->key);

	return OK;
}
	


/*if (nodeIsEmpty(current)) {
		if (current->left == NULL && current->right == NULL) { //delete leaf
			if (current == tree->root) {
				tree->root = NULL;
				destroyTreeNode(current);
			} 

			else if (parent->left == current) {
				parent->left = NULL;
			} else {
				parent->right = NULL;
			}

			destroyTreeNode(current);
		}

		TreeNode *tmp = current;

		if (current->left != NULL && current->right == NULL) {
			if (current == tree->root) {
				tree->root = current->left;
				destroyTreeNode(tmp);
				return OK;
			}

			if (parent->left == current) {
				parent->left = current->left;
			} else {
				parent->right = current->left;
			}

			destroyTreeNode(tmp);
			return OK;
		}

		if (current->left == NULL && current->right != NULL) {
			if (current == tree->root) {
				tree->root = current->right;
				destroyTreeNode(tmp);
				return OK;
			}

			if (parent->left == current) {
				parent->left = current->right;
			} else {
				parent->right = current->right;
			}

			destroyTreeNode(tmp);
		}

		if (current->left != NULL && current->right != NULL) {
			TreeNode *previous = current;
			current = current->right;

			while (current->left != NULL) {
				previous = current;
				current = current->left;
			}

			if (tmp == tree->root) {
				tree->root = current;
			} else if (parent->left == tmp) {
				parent->left = current;
			} else if (parent->right == tmp) {
				parent->right = current;
			}

			destroyTreeNode(tmp);

			if (previous->left == current) {
				previous->left = NULL;
			} else {
				previous->right = NULL;
			}
		}
			
		sewTree(tree->root, NULL);
		return OK;
	}
}
*/

	
	

/*int Delete(Tree *tree, const char *key) {		// пусть эта функция будет тут
	if (tree == NULL || key == NULL) {		// как память о потраченном на нее времени
		return ALLOCATION_ERROR;
	}

	TreeNode *current = tree->root;
	TreeNode *parent = NULL;

	while (current != NULL && strcmp(key, current->key) != 0) { // find key
		parent = current;

		if (strcmp(key, current->key) < 0) { // go to left
			current = current->left;
		} else if (strcmp(key, current->key) > 0) { // go to right
			current = current->right;
		}
	}

	if (current == NULL) {
		return KEY_NOT_FOUND;
	}

	int status = OK;

	if (strcmp(key, current->key) == 0) { // key was found
		status = deleteInfo(current);

		if (status != OK) {
			return status;
		}
	}

	if (nodeIsEmpty(current)) { // need to delete node
		if (current->left == NULL && current->right == NULL) { //leaf
			if (current == tree->root) {
				tree->root = NULL;
				destroyTreeNode(current);
				return OK;
			}

			if (parent->left == current) {
				parent->left = NULL;
			} else {
				parent->next = parent->right->next;
				parent->right = NULL;
			}

			destroyTreeNode(current);
			return OK;
		}

		TreeNode *tmp = current;

		if (current->left != NULL && current->right == NULL) { // one child
			if (current == tree->root) {
				current = current->left;
				tree->root = current;

				while (current->next != tmp) {
					current = current->right;
				}

				current->next = NULL;
				destroyTreeNode(tmp);

				return OK;

			}

			if (parent->left == current) {
				current = current->left;
				parent->left = current;

				while (current->next != tmp) {
					current = current->right;
				}

				current->next = parent;
			} else { //parent->right == current;
				current = current->left;
				parent->right = current;

				while (current->next != tmp) {
					current = current->right;
				}

				current->next = NULL;
			}

			destroyTreeNode(tmp);
			return OK;
		}

		if (current->left == NULL && current->right != NULL) { // one child
			if (current == tree->root) {
				tree->root = current->right;
				destroyTreeNode(tmp);

				return OK;
			}

			if (parent->left == current) {
				current = current->right;
				parent->left = current;

			} else { //parent->right == current
				current = current->right;
				parent->right = current;

				parent->next = tmp->next;
			}

			destroyTreeNode(tmp);
			return OK;
		}

		if (current->left != NULL && current->right != NULL) { // two children
			TreeNode *previous = current;
			current = current->right;

			while (current->left != NULL) {
				previous = current;
				current = current->left;
			}

			TreeNode *victim = current;
			
			if (victim->right == NULL && parent != NULL) { // leaf
				if (previous->left == victim) {
					previous->left = NULL;
				}

				if (previous->right == victim) {
					previous->next = victim->next;
					parent->right = NULL;
				}
			} else { // right != NULL && left == NULL
				if (previous->left == victim) {
					previous->left = current->right;
				}

				if (previous->right == victim) {
					previous->right = victim->right;
					previous->next = victim->next;
				}
			}
					
			if (tree->root == tmp) { // delete root
				//victim->next = tmp->next;
				victim->right = tmp->right;
				victim->left = tmp->left;
				tree->root = victim;

				current = tmp->left;

				while (current->right != NULL) {
					current = current->right;
				}

				current->next = victim;

				destroyTreeNode(tmp);
				return OK;
			}

			if (parent->left == tmp) {
				victim->next = tmp->next;
				victim->right = tmp->right;
				victim->left = tmp->left;
				parent->left = victim;
			} else { /// ? parent->right == tmp
				parent->right = victim;
				victim->left = tmp->left;
				//tmp->left->next = victim;

				current = tmp->left;
				
				while (current->right != NULL) {
					current = current->right;
				}

				current->next = victim;
			}

			destroyTreeNode(tmp);
			return OK;
		}
	}

	return OK;
}
*/


int getFromFile(Tree *tree, const char *filename) {
	if (tree == NULL || filename == NULL) {
		return ALLOCATION_ERROR;
	}

	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		return READING_FILE_ERROR;
	}

	char *key = NULL;
	char *info = NULL;

	char *str = fileReadline(file);
	int status = OK;

	while (str != NULL) { 
		key = str;
		info = fileReadline(file);

		if (info == NULL) {
			break;
		}

		status = Insert(tree, key, info);

		if (status != OK) {
			return status;
		}

		free(key);
		free(info);

		str = fileReadline(file);
	}

	fclose(file);

	return OK;
}


int getGVfile(Tree *tree, const char *filename) {
	if (tree == NULL) {
		return ALLOCATION_ERROR;
	}

	if (tree->root == NULL) {
		return EMPTY_TREE;
	}

	FILE *file = fopen(filename, "w");

	if (file == NULL) {
		return READING_FILE_ERROR;
	}

	fprintf(file, "digraph Tree {\n");

	TreeNode *current = findMinKey(tree->root);

	while (current != NULL) {
		fprintf(file, "\t%s;\n", current->key);

		if (current->left != NULL) {
			fprintf(file, "\t%s -> %s;\n", current->key, current->left->key);
		}

		if (current->right != NULL) {
			fprintf(file, "\t%s -> %s;\n", current->key, current->right->key);
		}

		current = current->next;
	}
	
	fprintf(file, "}\n");
	fclose(file);

	return OK;
}

