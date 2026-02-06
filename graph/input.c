#include <stdio.h>
#include <stdlib.h>
#include "input.h"

int getFloat(float *x, float left_board, float right_board) {
	int op = 0;
	
	while (op == 0) {
		op = scanf("%f", x);

		if (op == EOF) {
			return EOF;
		}

		if (op == 1 && ((*x) < left_board || (*x) > right_board)) {
			op = 0;
		}

		if (op == 0) {
			scanf("%*[^\n]");
		}
	}
	return op;
}

int getInt(int *x, int left_board, int right_board) {
	int op = 0;

	while (op == 0) {
		op = scanf("%d", x);

		if (op == EOF) {
			return EOF;
		}

		if (op == 1 && ((*x) < left_board || (*x) > right_board)) {
			op = 0;
			printf("Повторите ввод\n");
	        }

		else if (op == 0) {
			printf("Повторите ввод\n");
			scanf("%*[^\n]");
		}
	}
	
	//scanf("%*[^\n]");
	return op;
}


int getUnsignedInt(unsigned int *x, unsigned int left_board, unsigned int right_board) {
	int op = 0;

	while (op == 0) {
		op = scanf("%u", x);

		if (op == EOF) {
			return EOF;
		}

		if (op == 1 && ((*x) < left_board || (*x) > right_board)) {
			op = 0;
			printf("Repeat the input:\n");
		}

		else if (op == 0) {
			printf("Repeat the input:\n");
			scanf("%*[^\n]");
		}
	}

	return op;
}


int getDouble(double *x, double left_board, double right_board) {
	int op = 0;

	while (op == 0) {
		op = scanf("%lf", x);

		if (op == EOF) {
			return EOF;
		}
		
		if (op == 1 && ((*x) < left_board || (*x) > right_board)) {
			op = 0;
		}

		if (op == 0) {
			scanf("%*[^\n]");
		}
	}
	return op;
}


int getSize_t(size_t *x, size_t left_board, size_t right_board) {
        int op = 0;

        while (op == 0) {
                op = scanf("%zu", x);
		if (op == EOF) return EOF;

                if (op == 1 && ((*x) < left_board || (*x) > right_board)) {
                        op = 0;
                        printf("Repeat the input:\n");
                } else if (op == 0) {
                        printf("Repeat the input:\n");
                        scanf("%*[^\n]");
                }
        }
	return op;
}

