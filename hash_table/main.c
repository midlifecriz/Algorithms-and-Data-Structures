#include "hash_table.h"
#include <limits.h>


#define PRINT   1
#define INSERT  2
#define FIND    3
#define DELETE  4

#define SIZE    2


int getInt(int *x, int left_board, int right_board) {
        int op = 0;
        while (op == 0) {
                op = scanf("%d", x);
                if (op == EOF) return EOF;

                if (op == 1 && ((*x) < left_board || (*x) > right_board)) {
                        op = 0;
                        printf("Повторите ввод\n");
                } else if (op == 0) {
                        printf("Повторите ввод\n");
                        scanf("%*[^\n]");
                }
        }

        return op;
}


int main() {
    const char* menu[] = {"print","insert","find","delete"};
    size_t msize = sizeof(menu)/sizeof(char*);

    HashTable* table = createTable(SIZE);
    if (table == NULL) return 1;
    int option = 0;
    int status = 0;

    int val = 0;

    while (1) {
        for (size_t i = 0; i < msize; i++) printf("(%zu) %s\n", i+1, menu[i]);

        status = getInt(&option, 1, 5);
        if (status == EOF) {
            destroyTable(table);
            return 0;
        }

        switch(option) {
            case PRINT:
                printTable(table);
                break;

            case INSERT:
                status = getInt(&val, INT_MIN, INT_MAX);
                if (status == EOF) {
                    destroyTable(table);
                    return 0;
                }
                insert(table, val);
                break;

            case FIND:
                status = getInt(&val, INT_MIN, INT_MAX);
                if (status == EOF) {
                    destroyTable(table);
                    return 0;
                }
                printf("result: %d\n", find(table, val));
                break;

            case DELETE:
                status = getInt(&val, INT_MIN, INT_MAX);
                if (status == EOF) {
                    destroyTable(table);
                    return 0;
                }
                deleteEl(table, val);
                break;
        }
    }

    destroyTable(table);
    return 0;
}
