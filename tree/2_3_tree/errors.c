#include <stdlib.h>
#include <stdio.h>
#include "errors.h"


void handleErrors(int status) {
	switch (status) {
		case ALLOCATION_ERROR:
			printf("ALLOCATION ERROR\n");
			break;

		case OK:
			break;

		case SUBSTRING_NOT_FOUND:
			printf("SUBSTRING WAS NOT FOUND\n");
			break;

		case KEY_NOT_FOUND:
			printf("KEY WAS NOT FOUND\n");
			break;
		
		case READING_FILE_ERROR:
			printf("ERROR OF READING FILE");
			break;

		case EMPTY_TREE:
			printf("TREE IS EMPTY\n");
			break;

	}

	return;
}



