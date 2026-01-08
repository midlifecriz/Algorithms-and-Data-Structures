#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//Хэш-таблица с цепочками
typedef struct HashTable {
    size_t size;
    size_t count;
    struct List** data; 
} HashTable;


HashTable* createTable(size_t);
void insert(HashTable*, int);
void deleteEl(HashTable*, int);
bool find(HashTable*, int);
void rehash(HashTable*);
void printTable(HashTable*);
void destroyTable(HashTable*);
int hash(int);


typedef struct List {
    struct Node* head;
} List;


List* createList();
void push(List*, int);
bool del(List*, int);
void printList(List*);
void destroyList(List*);


typedef struct Node {
    int value;
    struct Node* next;
} Node;


Node* createNode(int);
void destroyNode(Node*);


#endif

