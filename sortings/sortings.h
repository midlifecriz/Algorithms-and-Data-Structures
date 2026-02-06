#ifndef SORTINGS_H
#define SORTINGS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void swap(void*, void*, size_t);
void bubbleSort(int*, size_t);
void optimizedBubbleSort(int*, size_t);
void combSort(int*, size_t);
void shakerSort(int*, size_t);
void selectionSort(int*, size_t);
void insertionSort(int*, size_t);
void quickSort(int*, int, int);
int partition(int*, int, int); //для quick sort


#endif

