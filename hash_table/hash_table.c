#include "hash_table.h"


#define LOAD    0.8


HashTable* createTable(size_t size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) return NULL;

    table->data = (List**)malloc(sizeof(List*) * size);
    if (table->data == NULL) {
        free(table);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        table->data[i] = createList();
        if (table->data[i] == NULL) {
            free(table);
            return NULL;
        }
    }

    table->size = size;
    table->count = 0;
    return table;
}


void destroyTable(HashTable* table) {
    if (table == NULL) return;
    for (size_t i = 0; i < table->size; i++) destroyList(table->data[i]);
    free(table->data);
    free(table);
}


void insert(HashTable* table, int value) {
    if (table == NULL) return;
    if ((double)table->count / table->size > LOAD) rehash(table);

    size_t index = hash(value) % table->size;
    push(table->data[index], value);
    (table->count)++;
}


void deleteEl(HashTable* table, int value) {
    if (table == NULL) return;
    size_t index = hash(value) % table->size;
    if (del(table->data[index], value)) (table->count)--;
}


bool find(HashTable* table, int value) {
    if (table == NULL) return false;
    size_t index = hash(value) % table->size;

    Node* curr = table->data[index]->head;
    while (curr != NULL) {
        if (curr->value == value) return true;
        curr = curr->next;
    }

    return false;
}


void rehash(HashTable* table) {
    if (table == NULL) return;
    
    List** old_data = table->data;
    size_t old_size = table->size;

    table->data = (List**)malloc(sizeof(List*) * old_size * 2);
    for (size_t i = 0; i < old_size * 2; i++)
        table->data[i] = createList();
    table->size *= 2;
    table->count = 0;

    Node* curr = NULL;
    for (size_t i = 0; i < old_size; i++) {
        curr = old_data[i]->head;
        while (curr != NULL) {
            insert(table, curr->value);
            curr = curr->next;
        }
    }
    
    for (size_t i = 0; i < old_size; i++)
        destroyList(old_data[i]);
    free(old_data);
}


int hash(int val) {
    const int M = 23;
    const int N = 47;
    if (val < 0) return (-1)*val*M+N;
    else return val*M+N;
}


void printTable(HashTable* table) {
    if (table == NULL) return;
    printf("___Hash Table___\nsize = %zu\ncount = %zu\n", table->size, table->count);
    for (size_t i = 0; i < table->size; i++)
        printList(table->data[i]);
    printf("\n");
}


List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->head = NULL;
    return list;
}


void destroyList(List* list) {
    if (list == NULL) return;
    Node* current = list->head;
    Node* tmp = current;
    while (current != NULL) {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    free(list);
}


void push(List* list, int value) {
    if (list == NULL) return;
    Node* node = createNode(value);
    if (node == NULL) return;
    node->next = list->head;
    list->head = node;
}


bool del(List* list, int val) {
    if (list == NULL) return false;
    Node* prev = list->head;
    Node* curr = list->head;

    while (curr != NULL) {
        if (curr->value == val) {
            prev->next = curr->next;
            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}


void printList(List* list) {
    if (list == NULL) return;
    Node* curr = list->head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}


Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

