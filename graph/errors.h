#include <stdio.h>
#include <stdlib.h>

#ifndef ERRORS_H
#define ERRORS_h

enum GraphErrors {
	READING_FILE_ERROR = -8,
	ALLOCATION_ERROR,
	VERTEX_NOT_FOUND,
	COMPUTER_NOT_FOUND,
	EDGE_NOT_FOUND,
	DUPLICATE_VERTEX,
	DUPLICATE_EDGE,
	EMPTY,
	OK
};

void handleErrors(int);
#endif

