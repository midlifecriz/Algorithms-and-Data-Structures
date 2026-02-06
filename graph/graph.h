#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex {
	char *name; //name of the computer
	size_t port; //number of the port
	List *link;  //list of linked verteces	
} Vertex;


typedef struct Graph {
	size_t capacity;
	size_t size; //quantity of verteces
	Vertex **verteces; //array of verteces;
} Graph;


//Vertex
Vertex *createVertex(char *, size_t);
void destroyVertex(Vertex *);
void printVertex(Vertex *);

//Graph
Graph *createGraph();
void destroyGraph(Graph *);
void printGraph(Graph *);

int printEdge(Graph *, char *, char *);
int insertVertex(Graph *, char *, size_t);
int deleteVertex(Graph *, char *);
int insertEdge(Graph *, char *, char *, Array *);
int deleteEdge(Graph *, char *, char *);
int changeVertex(Graph *, char *, size_t); //change data in the vertex
int changeEdge(Graph *, char *, char *, Array *); //change data in the edge

int search(Graph *, char *); //return index of vertex
int accecible(Graph *, int, int);
int BFS(Graph *, char *, int *);
void DFS(Graph *, int, int, int *, int *, int *, int *, int *);
void DFS_r(Graph *, int, int *, int *, size_t *, int);
int max(int *, size_t);
Graph *reverse(Graph *);
void printComponents(Graph *, int **, size_t *, size_t);
int component(Graph *, int ***, size_t *, size_t **); //find component
void printPath(Graph *, int, int *, int *);
int fordBellman(Graph *, char *, char *, size_t);
int visualiseGraph(Graph *, char *); //get graph.gv file

#endif

