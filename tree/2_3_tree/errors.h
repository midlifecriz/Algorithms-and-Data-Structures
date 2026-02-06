#include <stdio.h>
#include <stdlib.h>

#ifndef ERRORS_H
#define ERRORS_h

enum TreeErrors {
	END_OF_PROGRAM = -6,
	READING_FILE_ERROR,
	ALLOCATION_ERROR,
	SUBSTRING_NOT_FOUND,
	KEY_NOT_FOUND,
	EMPTY_TREE,
	OK
};

void handleErrors(int);
#endif

