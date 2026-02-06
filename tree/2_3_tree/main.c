#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "array.h"
#include <limits.h> 
#include "errors.h"
#include "my_readline.h"
#include "input.h"
#include "timing.h"

#define OPTIONS  "(1)Print tree\n(2)Insert element\n(3)Delete element\n(4)Traverse tree\n(5)Find element by the key\n(6)Special find\n(7)Visualize tree\n(8)Import tree from txt file\n(9)Timing\n(10)End of program\n"


enum {
	PRINT = 1,
	INSERT,
	DELETE,
	TRAVERSE,
	FIND,
	SPECIAL_FIND,
	VISUALIZE,
	IMPORT,
	TIMING,
	END,
};


int main() {
	int status = OK;
	int option = 0;
	char *info = NULL;
	unsigned int key = 0;
	unsigned int lb = 0;
	unsigned int rb = 0;
	unsigned int key1 = 0;
	unsigned int key2 = 0;
	size_t size = 0;
	char *filename = NULL;
	Array *array = NULL;
	Array **arrays = NULL;

	Tree *tree = createTree();
	if (tree == NULL) return ALLOCATION_ERROR;
	
	while (option != END) {
		printf("____MENU____\n");
		printf("%s", OPTIONS);

		status = getInt(&option, PRINT, END);
	
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
				printf("Input key:\n");
				status = getUnsignedInt(&key, 0, UINT_MAX);

				if (status == EOF) {
					return EOF;
				}

				getchar();
				info = Readline("Input information:\n");

				if (info == NULL) {
					destroyTree(tree);
					return OK;
				}

				status = insert(tree, key, info);
				handleErrors(status);

				if (status == ALLOCATION_ERROR) {
					free(info);
					destroyTree(tree);
					return ALLOCATION_ERROR;
				}

				free(info);
				break;
		
			case DELETE:
				getchar();

				printf("Input key:\n");
				status = getUnsignedInt(&key, 0, UINT_MAX);
				if (status == EOF) {
					destroyTree(tree);
					return OK;
				}

				status = del(tree, key);
				handleErrors(status);
				break;

			case TRAVERSE:
				getchar();
				printf("Input the left board:\n");
				status = getUnsignedInt(&lb, 0, UINT_MAX);
				if (status == EOF) {
					destroyTree(tree);
					return OK;
				}
				
				printf("Input the right board:\n");
				status = getUnsignedInt(&rb, 0, UINT_MAX);
				if (status == EOF) {
					destroyTree(tree);
					return OK;
				}

				traverse(tree->root, lb, rb);
				break;

			case FIND:
				getchar();
				printf("Input key:\n");
				status = getUnsignedInt(&key, 1, UINT_MAX);

				if (status == EOF) {
					destroyTree(tree);
					return OK;
				}

				array = findKey(tree, key);

				if (array == NULL) {
					printf("KEY WAS NOT FOUND\n");
					break;
				}

				printArray(array, key);
				destroyArray(array);
				break;

			case SPECIAL_FIND:
				getchar();
				printf("Input value:\n");
				status = getUnsignedInt(&key, 0, UINT_MAX);

				if (status == EOF) {
					destroyTree(tree);
					return OK;
				}

				arrays = specialFind(tree, &size, key, &key1, &key2);
				if (arrays == NULL) {
					printf("KEY WAS NOT FOUND\n");
					break;
				}

				printArray(arrays[0], key1);
				if (size == 2) printArray(arrays[1], key2);
				for (size_t i = 0; i < size; i++) destroyArray(arrays[i]);

				free(arrays);
				break;

			case VISUALIZE:
				status = getGVfile(tree, "tree.gv");
				handleErrors(status);
				break;

			case IMPORT:
				if (tree != NULL) destroyTree(tree);

				tree = createTree();
				if (tree == NULL) return ALLOCATION_ERROR;

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

			case TIMING:
				getchar();
				filename = Readline("Input name of file for results:\n");
				if (filename == NULL) {
					destroyTree(tree);
					return OK;
				}

				status = timing(filename);
				handleErrors(status);
				free(filename);
				break;
			case END:
				break;
		}
	}

	destroyTree(tree);
	return OK;
}

