#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "info_node.h"

#ifndef LIST_H
#define LIST_H

typedef struct List {
	InfoNode *head;
	InfoNode *tail;
} List;

List *createList();
void destroyList(List *);
void printList(List *);
bool listIsEmpty(List *);
int Push(List *, const char *); // добавить в конец списка (самая новая версия)
int deleteEl(List *); // удалить первый элемент в списке (самая старая версия)
List *copyList(List *);

#endif 

