#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tree.h"
#include "array.h"
#include "errors.h"
#include "my_readline.h"
#include "input.h"
#include "timing.h"

#define OPTIONS  "(1)Print tree\n(2)Insert element\n(3)Delete element\n(4)Traverse tree\n(5)Find element by the key\n(6)Special find (find element with opposite key)\n(7)Visualize a binary search tree\n(8)Import tree from txt file\n(9)End of program\n(10)Timing\n"


enum {
	PRINT = 1,
	INSERT,
	DELETE,
	TRAVERSE,
	FIND,
	SPECIAL_FIND,
	VISUALIZE,
	IMPORT,
	END,
	TIMING
};


int main() {
	int status = OK;
	int option = 0;
	char *info = NULL;
	char *key = NULL;
	char *filename = NULL;
	char *substring = NULL;
	unsigned int quantity = 0;

	Array *array = NULL;

	Tree *tree = createTree();

	if (tree == NULL) {
		return ALLOCATION_ERROR;
	}
	
	while (option != END) {
		printf("____MENU____\n");
		printf("%s", OPTIONS);

		status = getInt(&option, 1, 10);
	
		if (status == EOF) {
			destroyTree(tree);
			return OK;
		}

		switch (option) {
			case PRINT:
				shellPrintTree(tree);
				break;

			case INSERT:
				getchar();
				key = Readline("Input key: \n");

				if (key == NULL) {
					destroyTree(tree);
					return OK;
				}

				info = Readline("Input information:\n");

				if (info == NULL) {
					free(key);
					destroyTree(tree);
					return OK;
				}

				status = Insert(tree, key, info);
				handleErrors(status);

				if (status == ALLOCATION_ERROR) {
					free(key);
					free(info);
					destroyTree(tree);
					return ALLOCATION_ERROR;
				}

				free(info);
				free(key);

				break;
		
			case DELETE:
				getchar();
				key = Readline("Input key\n");

				if (key == NULL) {
					destroyTree(tree);
					return OK;
				}

				status = Delete(tree, key);
				handleErrors(status);

				free(key);
				break;

			case TRAVERSE:
				getchar();
				substring = Readline("Input substring:\n");

				if (substring == NULL) {
					destroyTree(tree);
					return OK;
				}

				status = traversingTree(tree, substring);
				handleErrors(status);

				free(substring);
				break;

			case FIND:
				getchar();
				key = Readline("Input key:\n");

				if (key == NULL) {
					destroyTree(tree);
					return OK;
				}

				array = findKey(tree, key);

				if (array == NULL) {
					printf("KEY WAS NOT FOUND\n");
					free(key);
					break;
				}

				printArray(array);
				destroyArray(array);

				free(key);
				break;

			case SPECIAL_FIND:
				getchar();
				key = Readline("Input key:\n");

				if (key == NULL) {
					destroyTree(tree);
					return OK;
				}

				array = findOppositeKey(tree, key);

				if (array == NULL) {
					printf("KEY WAS NOT FOUND\n");
					free(key);
					break;
				}

				printArray(array);
				destroyArray(array);

				free(key);
				break;

			case VISUALIZE:
				status = getGVfile(tree, "tree.gv");
				handleErrors(status);

				break;

			case IMPORT:
				if (tree != NULL) {
					destroyTree(tree);
				}

				tree = createTree();

				if (tree == NULL) {
					return ALLOCATION_ERROR;
				}

				getchar();
				filename = Readline("Input name of txt file:\n");

				if (filename == NULL) {
					destroyTree(tree);
					return OK;
				}

				status = getFromFile(tree, filename);

				if (status == ALLOCATION_ERROR) {
					free(filename);
					destroyTree(tree);
					return ALLOCATION_ERROR;
				}

				handleErrors(status);
				free(filename);

				break;

			case END:
				break;
			case TIMING:
				printf("Input quantity of elements: \n");
				status = getUnsignedInt(&quantity, 1, INT_MAX);
				if (status == EOF) {
					destroyTree(tree);
					return EOF;
				}

				status = timing(quantity);
				
				break;

		}
	}

	destroyTree(tree);
	return OK;
}











