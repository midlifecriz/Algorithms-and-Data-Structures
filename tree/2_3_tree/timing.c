#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "timing.h"
#include "errors.h"
#include <time.h>

#define LENGTH 20
#define MAX 10000
#define QUANTITY 10000

char *randomString(int length) {
	char *str = (char *)malloc(length * sizeof(char));
	if (str == NULL) return NULL;

	for (int i = 0; i < length - 1; i++) {
		str[i] = (char)rand() % 128;
	}

	str[length - 1] = '\0';
	return str;
}

int timing(char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) return READING_FILE_ERROR;

	int status = OK;
	Tree *tree = NULL;
	clock_t start, end;
	int key[QUANTITY];
	char* info[QUANTITY];
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','u','z'};
	Array *arr = NULL;

	//initialise test array
	for (int i = 0; i < QUANTITY; i++) {
		key[i] = rand();
		if (key[i] == 0) key[i] += 1;
		info[i] = (char *)calloc(LENGTH, sizeof(char));
		for (int m = 0; m < LENGTH - 1; m++) {
			info[i][m] = alphabet[rand() % 26];
		}
	}

	int q = 1;
	while (q <= MAX) {
		tree = createTree();
		if (tree == NULL) {
			fclose(file);
			return ALLOCATION_ERROR;
		}

		fprintf(file, "ELEMENTS: %d\n", q);
		start = clock();
		for (int j = 0; j < q; j++) {
		 	status = insert(tree, key[j], info[j]);
		 	if (status != OK) {
				fclose(file);
				return status;
			}
		}
		end = clock();

		fprintf(file, "INSERT: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

		start = clock();
		for (int k = 0; k < q; k++) {
			arr = findKey(tree, key[k]);
			destroyArray(arr);
		}
		end = clock();

		fprintf(file, "FIND: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
		/*
		start = clock();
		for (int n = 0; n < q; n++) {
			status = del(tree, key[n]);
			if (status != OK) {
				fclose(file);
				return status;
			}
		}
		end = clock();

		fprintf(file, "DELETE: %lf\n", (double)(end - start)/CLOCKS_PER_SEC); */
		destroyTree(tree);
		q *= 10;
	}
	
	for (int q = 0; q < QUANTITY; q++) {
		free(info[q]); ///
	}

	fclose(file);
	return OK;
}






		


