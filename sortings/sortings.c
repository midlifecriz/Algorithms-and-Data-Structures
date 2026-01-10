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




