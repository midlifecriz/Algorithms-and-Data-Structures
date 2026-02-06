#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "timing.h"
#include "errors.h"
#include <time.h>

#define LENGTH 20

char *randomString(int length) {
	char *str = (char *)malloc(length * sizeof(char));
	if (str == NULL) return NULL;

	for (int i = 0; i < length - 1; i++) {
		str[i] = (char)rand() % 128;
	}

	str[length - 1] = '\0';
	return str;
}

int timing(int quantity) {
	Tree *tree = createTree();
	if (tree == NULL) return ALLOCATION_ERROR;
	
	int status = OK;
	clock_t start, end;
	char* key[quantity];
	char* info[quantity];
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','u','z'};
	Array *arr = NULL;

	printf("%d ELEMENTS\n", quantity);

	for (int i = 0; i < quantity; i++) {
		key[i] = (char *)calloc(LENGTH, sizeof(char));
		info[i] = (char *)calloc(LENGTH, sizeof(char));
		for (int m = 0; m < LENGTH - 1; m++) {
			key[i][m] = alphabet[rand() % 26];
			info[i][m] = alphabet[rand() % 26];
		}
		//key[i] = randomString(LENGTH);
		//info[i] = randomString(LENGTH);
	}

	start = clock();
	for (int j = 0; j < quantity; j++) {
		 status = Insert(tree, key[j], info[j]);
		 if (status != OK) return status;
	}
	end = clock();

	printf("INSERT: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	start = clock();
	for (int k = 0; k < quantity; k++) {
		arr = findKey(tree, key[k]);
		destroyArray(arr);
	}
	end = clock();

	printf("FIND: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	start = clock();
	for (int n = 0; n < quantity; n++) {
		status = Delete(tree, key[n]);
		if (status != OK) return status;
	}
	end = clock();

	printf("DELETE: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
	destroyTree(tree);
	
	for (int q = 0; q < quantity; q++) {
		free(key[q]);
		free(info[q]); ///
	}

	return OK;
}






		


