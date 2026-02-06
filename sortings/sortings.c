#include "sortings.h"


void swap(void* a, void* b, size_t size) {
    void* tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}


//пузырьковая сортировка
void bubbleSort(int* array, size_t n) {
    if (array == NULL || n <= 1) return;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            if (array[j] > array[j + 1])
                swap(array + j, array + j + 1, sizeof(int));
        }
    }
}


//оптимизированная пузырьковая сортировка
void optimizedBubbleSort(int* array, size_t n) {
    if (array == NULL || n <= 1) return;
    size_t i = 0;
    bool t = true;
    
    while (t) {
        t = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array + j, array + j + 1, sizeof(int));
                t = true;
            }
        }
        i++;
    }
}


//сортировка расческой
void combSort(int* array, size_t n) {
    if (array == NULL || n <= 1) return;

    float k = 1.3;
    int jump = n;
    bool swapped = true;

    while (jump > 1 && swapped) {
        if (jump > 1) jump /= k;
        swapped = false;
        
        for (size_t i = 0; i < n - jump; i++) {
            if (array[i + jump] < array[i]) {
                swap(array + i, array + i + jump, sizeof(int));
                swapped = true;
            }
        }
    }
}


void shakerSort(int* array, size_t n) {
    if (array == NULL || n <= 1) return;

    bool swapped = true;
    int begin = -1;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        begin++;

        for (int i = begin + 1; i < end; i++) {
            if (array[i] > array[i + 1]) {
                swap(array + i, array + i + 1, sizeof(int));
                swapped = true;
            }
        }

        if (!swapped) break;
        swapped = false;
        end--;

        for (int j = end; j >= begin; j--) {
            if (array[j] > array[j + 1]) {
                swap(array + j, array + j + 1, sizeof(int));
                swapped = true;
            }
        }
    }
}


void selectionSort(int* array, size_t n) {
    if (array == NULL || n <= 1) return;

    int min = -1;
    for (size_t i = 0; i < n - 1; i++) {
        min = i;
        for (size_t j = i + 1; j < n; j++)
            if (array[j] < array[min])
                min = j;
        swap(array + i, array + min, sizeof(int));
    }
}


void insertionSort(int* array, size_t n) {
    if (array == NULL || n <= 1) return;

    int j = 0;
    for (size_t i = 1; i < n; i++) {
        j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            swap(array + j, array + j + 1, sizeof(int));
            j--;
        }
    }
}


void quickSort(int* array, int l, int r) {
    if (array == NULL) return;
    if (l < r) {
        int q = partition(array, l, r);
        quickSort(array, l, q);
        quickSort(array, q + 1, r);
    }
}


int partition(int* array, int l, int r) {
    int v = array[(l+r)/2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (array[i] < v) i++;
        while (array[j] > v) j--;
        if (i >= j) break;
        swap(array+(i++), array+(j--), sizeof(int));
    }
    return j;
}

