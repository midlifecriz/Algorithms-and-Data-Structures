#include "sortings.h"
#include <time.h>


#define RANDOM_SEED 144
#define NUM_TESTS   10


int main() {
    size_t sizes[] = {10000000};
    size_t n = sizeof(sizes)/sizeof(size_t);
    double sum_time[] = {0, 0, 0, 0};

    int* array = (int*)malloc(sizeof(int) * sizes[n - 1]);
    if (array == NULL) return 1;

    //для каждого количества элементов проводим NUM_TESTS экспериментов
    for (size_t i = 0; i < n; i++) {
        for (int j = 0; j < NUM_TESTS; j++) {
            //генерируем новый массив
            srand(RANDOM_SEED + j);
            for (size_t k = 0; k < sizes[i]; k++) {
                array[k] = rand() % 100;
                //printf("%d ", array[k]);
            }
            //printf("\n");
        
            //замеряем время работы
            clock_t start_time = clock();
            quickSort(array, 0, sizes[i]-1);
            clock_t end_time = clock();
            sum_time[i] += (end_time - start_time)/CLOCKS_PER_SEC;

           //for (size_t count = 0; count < sizes[i]; count++) printf("%d ", array[count]);
            //printf("\n\n");
        }

        printf("Среднее время для %zu элементов: %lf\n", sizes[i], sum_time[i]/NUM_TESTS);
    }

    free(array);
    return 0;
}

