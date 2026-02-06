#include <stdlib.h>
#include <stdio.h>
#include "errors.h"


void handleErrors(int status) {
	switch (status) {
		case OK: 
			break;

		case ALLOCATION_ERROR:
			printf("ALLOCATION ERROR\n");
			break;

		case VERTEX_NOT_FOUND:
			printf("VERTEX WAS NOT FOUND\n");
			break;

		case EDGE_NOT_FOUND:
			printf("EDGE WAS NOT FOUND\n");
			break;
		
		case COMPUTER_NOT_FOUND:
			printf("NEAREST COMPUTER WAS NOT FOUND");
			break;

		case DUPLICATE_VERTEX:
			printf("DUPLICATE VERTEX\n");
			break;
		
		case DUPLICATE_EDGE:
			printf("DUPLICATE EDGE\n");
			break;

		case READING_FILE_ERROR:
			printf("ERROR OF READING FILE\n");
			break;

		case EMPTY:
			printf("GRAPH IS EMPTY\n");
			break;

	}

	return;
}



