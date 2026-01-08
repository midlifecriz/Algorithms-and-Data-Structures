#ifndef GRAPH_H
#define GRAPH_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#define WHITE   1
#define GREY    2
#define BLACK   3


// Граф представляется в виде списков смежности вершин


typedef struct Node { 
    int number;
    struct Node* next;
} Node;


typedef struct List {
    Node* head;
} List;


typedef struct Graph {
    List** adj_lists;
    size_t size;
} Graph;


Node* createNode(int);
void destroyNode(Node*);

List* createList();
void destroyList(List*);
void push(List*, int);


Graph* createGraph(size_t);
void addEdge(Graph*, int, int);
bool edgeExists(Graph*, int, int);
Graph* generateRandomGraph(size_t size);
Graph* generateSparseGraph(size_t size);
Graph* generateDenseGraph(size_t size);
void destroyGraph(Graph*);

//DFS
void DFS(Graph*, int, int*, int*, int*);
void shellForDFS(Graph*,  int*, int*, int*);

#endif

