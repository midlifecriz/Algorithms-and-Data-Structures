#include "graph.h"
#include "errors.h"
#include "queue.h"
#include <string.h>
#include <limits.h>

#define CAPACITY 2
#define WHITE 1
#define GREY 2
#define BLACK 3

Vertex *createVertex(char *name, size_t port) {
	Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
	if (vertex == NULL) return NULL;

	vertex->name = strdup(name);
	if (vertex->name == NULL) {
		free(vertex);
		return NULL;
	}

	vertex->link = createList();
	if (vertex->link == NULL) {
		free(vertex->name);
		free(vertex);
		return NULL;
	}

	vertex->port = port;
	return vertex;
}


void destroyVertex(Vertex *vertex) {
	if (vertex == NULL) return;

	destroyList(vertex->link);
	free(vertex->name);
	free(vertex);
}


Graph *createGraph() {
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	if (graph == NULL) return NULL;

	graph->verteces = (Vertex **)malloc(CAPACITY * sizeof(Vertex *));
	if (graph->verteces == NULL) {
		free(graph);
		return NULL;
	}

	graph->size = 0;
	graph->capacity = CAPACITY;
	return graph;
}


void destroyGraph(Graph *graph) {
	if (graph == NULL) return;

	for (size_t i = 0; i < graph->size; i++) {
		destroyVertex(graph->verteces[i]);
	}

	free(graph->verteces);
	free(graph);
}


void printGraph(Graph *graph) {
	if (graph == NULL) return;
	if (graph->size == 0) {
		printf("Graph is empty\n");
		return;
	}

	printf("GRAPH:\n");
	Node *curr = NULL;

	for (size_t i = 0; i < graph->size; i++) {
		printf("%s: ", graph->verteces[i]->name);

		curr = graph->verteces[i]->link->head;
		while (curr != NULL) {
			printf("%s  ", curr->edge->vertex);
			curr = curr->next;
		}

		printf("\n");
	}
}


int printEdge(Graph *graph, char *name1, char *name2) {
	if (graph == NULL) return ALLOCATION_ERROR;
	if (name1 == NULL || name2 == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	int index1 = -1;
	int index2 = -1;

	for (size_t i = 0; i < graph->size; i++) {
		if (index1 != -1 && index2 != -1) {
			break;
		} else if (strcmp(graph->verteces[i]->name, name1) == 0) {
			index1 = i;
		} else if (strcmp(graph->verteces[i]->name, name2) == 0) {
			index2 = i;
		}
	}

	if (index1 == -1 || index2 == -1) return EDGE_NOT_FOUND;

	Node *curr = graph->verteces[index1]->link->head;
	while (curr != NULL) {
		if (strcmp(curr->edge->vertex, name2) == 0) {
			break;
		}
		curr = curr->next;
	}

	if (curr == NULL) return EDGE_NOT_FOUND;

	printf("EDGE: %s -> %s\nallowed ports: ", graph->verteces[index1]->name, graph->verteces[index2]->name);
	for (size_t i = 0; i < curr->edge->ports->size; i++) {
		printf("%zu  ", curr->edge->ports->data[i]);
	}
	printf("\n");
	return OK;
}


int insertVertex(Graph *graph, char *name, size_t port) {
	if (graph == NULL || name == NULL) return ALLOCATION_ERROR;

	//check duplicates
	for (size_t i = 0; i < graph->size; i++) {
		if (strcmp(graph->verteces[i]->name, name) == 0) {
			return DUPLICATE_VERTEX;
		}
	}

	//create new vertex
	Vertex *vertex = createVertex(name, port);
	if (vertex == NULL) return ALLOCATION_ERROR;

	//insert to graph
	if (graph->size == graph->capacity) {
		graph->verteces = (Vertex **)realloc(graph->verteces, 2 *graph->capacity * sizeof(Vertex *));
		if (graph->verteces == NULL) {
			destroyVertex(vertex);
			return ALLOCATION_ERROR;
		}
		graph->capacity = graph->capacity * 2;
	}

	graph->verteces[graph->size] = vertex;
	(graph->size)++;

	return OK;
}


int deleteVertex(Graph *graph, char *name) {
	if (graph == NULL || name == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	int index = -1;
	for (size_t i = 0; i < graph->size; i++) {
		if (strcmp(graph->verteces[i]->name, name) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) return VERTEX_NOT_FOUND;

	//delete all linked edges
	for (size_t i = 0; i < graph->size; i++) {
		del(graph->verteces[i]->link, name);
	}

	destroyVertex(graph->verteces[index]);
	for (size_t i = index; i < graph->size - 1; i++) {
		graph->verteces[i] = graph->verteces[i + 1];
	}

	(graph->size)--;
	return OK;
}


int insertEdge(Graph *graph, char *name1, char *name2, Array *ports) {
	if (graph == NULL) return ALLOCATION_ERROR;
	if (name1 == NULL || name2 == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	int status = OK;
	int index1 = -1;
	int index2 = -1;

	for (size_t i = 0; i < graph->size; i++) {
		if (index1 != -1 && index2 != -1) {
			break;
		} else if (strcmp(graph->verteces[i]->name, name1) == 0) {
			index1 = i;
		} else if (strcmp(graph->verteces[i]->name, name2) == 0) {
			index2 = i;
		}
	}

	if (index1 == -1 || index2 == -1) return VERTEX_NOT_FOUND;

	//check duplicates
	Node *curr = graph->verteces[index1]->link->head;
	while (curr != NULL) {
		if (strcmp(curr->edge->vertex, name2) == 0) {
			return DUPLICATE_EDGE;
		}
		curr = curr->next;
	}

	//create new edge
	Edge *edge = createEdge(name2);
	if (edge == NULL) return ALLOCATION_ERROR;

	//input ports to the edge
	if (ports != NULL) {
		for (size_t i = 0; i < ports->size; i++) {
			status = pushArray(edge->ports, ports->data[i]);
			if (status != OK) return status;
		}
	}

	//push new edge ptr to the list
	status = push(graph->verteces[index1]->link, edge);
	if (status != OK) return status;
	
	return OK;
}


int deleteEdge(Graph *graph, char *name1, char *name2) {
	if (graph == NULL) return ALLOCATION_ERROR;
	if (name1 == NULL || name2 == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	int status = OK;
	int index = -1;

	for (size_t i = 0; i < graph->size; i++){
		if (strcmp(graph->verteces[i]->name, name1) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) return EDGE_NOT_FOUND;

	//find by the name and delete edge in the list
	status = del(graph->verteces[index]->link, name2);
	if (status != OK) return status;
	
	return OK;
}


int changeVertex(Graph *graph, char *name, size_t port) {
	if (graph == NULL || name == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	int index = -1;
	for (size_t i = 0; i < graph->size; i++) {
		if (strcmp(graph->verteces[i]->name, name) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) return VERTEX_NOT_FOUND;

	//change data
	graph->verteces[index]->port = port;
	return OK;
}

//TODO
int changeEdge(Graph *graph, char *name1, char *name2, Array *ports) {
	if (graph == NULL) return ALLOCATION_ERROR;
	if (name1 == NULL || name2 == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	int index = -1;
	for (size_t i = 0; i < graph->size; i++) {
		if (strcmp(graph->verteces[i]->name, name1) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) return EDGE_NOT_FOUND;

	Node *curr = graph->verteces[index]->link->head;
	while (curr != NULL) {
		if (strcmp(curr->edge->vertex, name2) == 0) {
			break;
		}
		curr = curr->next;
	}

	if (curr == NULL) return EDGE_NOT_FOUND;
	//copy array
	Array *dst = curr->edge->ports;
	if (ports->size > dst->capacity) {
		dst->data = (size_t *)realloc(dst->data, ports->size * sizeof(size_t));
		if (dst->data == NULL) return ALLOCATION_ERROR;
	}

	for (size_t i = 0; i < ports->size; i++) {
		dst->data[i] = ports->data[i];
	}

	dst->size = ports->size;
	return OK;
}


int search(Graph *graph, char *name) {
	if (graph == NULL || name == NULL) return -1;
	if (graph->size == 0) return -1;

	int index = -1;
	for (size_t i = 0; i < graph->size; i++) {
		if (strcmp(graph->verteces[i]->name, name) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

//TODO: добавить ограничения на номера портов
int BFS(Graph *graph, char *name, int *near) {
	if (graph == NULL || near == NULL) return ALLOCATION_ERROR;
	if (name == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	//find index of vertex
	int status = OK;
	int v1 = -1;
	int index = 0;

	for (size_t i = 0; i < graph->size; i++) {
		if (strcmp(graph->verteces[i]->name, name) == 0) {
			v1 = i;
			break;
		}
	}
	if (v1 == -1) return VERTEX_NOT_FOUND;

	//create queue
	Queue *queue = createQueue();
	if (queue == NULL) return ALLOCATION_ERROR;

	//array of visited
	int *visited = (int *)malloc(graph->size * sizeof(int));
	if (visited == NULL) return ALLOCATION_ERROR;

	for (size_t i = 0; i < graph->size; i++) visited[i] = -1; //not visited
	visited[v1] = 0;

	//add first vertex to the queue
	size_t port = graph->verteces[v1]->port;
	status = pushQueue(queue, v1);
	if (status != OK) return status;

	int u = -1; //current vertex
	Node *curr = NULL;

	while (!emptyQueue(queue)) {
		u = popQueue(queue);
		if (u != v1 && graph->verteces[u]->port == port) { //есть указанный сервис
			*near = u; //find
			free(visited);
			destroyQueue(queue);
			return OK;
		}
		
		curr = graph->verteces[u]->link->head;
		while (curr != NULL) {
			index = search(graph, curr->edge->vertex);
			if (accecible(graph, u, index)) { //edge has port u and port index
				if (visited[index] == -1) { 
					visited[index] = 1;
					pushQueue(queue, index);
				}
			}
			curr = curr->next;
		}
	}
	
	//not found
	free(visited);
	destroyQueue(queue);
	return COMPUTER_NOT_FOUND;
}


int accecible(Graph *graph, int v1, int v2) {
	if (graph == NULL) return 0;
	if (graph->size == 0) return 0;
	
	int find = 0;
	Node *curr = graph->verteces[v1]->link->head;
	while (curr != NULL) {
		if (strcmp(curr->edge->vertex, graph->verteces[v2]->name) == 0) {
			find = 1;
			break;
		}
		curr = curr->next;
	}
	//if (find == 1) printf("Edge was found\n"); //debugging
	if (find == 0) return 0; //no edge
	
	//check port v1 and v2 in array
	size_t port1 = graph->verteces[v1]->port;
	size_t port2 = graph->verteces[v2]->port;
	int check1 = 0;
	int check2 = 0;

	for (size_t i = 0; i < curr->edge->ports->size; i++) {
		if (check1 == 1 && check2 == 1) return 1;
		if (curr->edge->ports->data[i] == port1) check1 = 1;
		if (curr->edge->ports->data[i] == port2) check2 = 1;
	}

	if (check1 == 0 || check2 == 0) {
		//printf("Port was not found\n"); //debugging
		return 0;
	}
	return 1;
}


void DFS(Graph *graph, int v, int par, int *colour, int *parent, int *time_in, int *time_out, int *timer) {
	if (graph == NULL) return;

	time_in[v] = *timer;
	(*timer)++;
	parent[v] = par;
	colour[v] = GREY;

	int u = -1;
	Node *curr = graph->verteces[v]->link->head;

	while (curr != NULL) {
		u = search(graph, curr->edge->vertex);
		if (colour[u] == WHITE) {
			DFS(graph, u, v, colour, parent, time_in, time_out, timer);
		}
		curr = curr->next;
	}
	
	time_out[v] = *timer;
	(*timer)++;
	colour[v] = BLACK;
}


void DFS_r(Graph *graph, int v, int *colour, int *component, size_t *sizes, int index) {
	if (graph == NULL) return;
	//colour[v] = GREY;

	int u = -1;
	Node *curr = graph->verteces[v]->link->head;
	
	while (curr != NULL) {
		u = search(graph, curr->edge->vertex);
		if (colour[u] == WHITE) {
			DFS_r(graph, u, colour, component, sizes, index);
		}
		curr = curr->next;
	}

	component[sizes[index]] = v;
	(sizes[index])++;
	colour[v] = BLACK;
}


//TODO
int component(Graph *graph, int ***components, size_t *comp_quantity, size_t **sizes) {
	if (graph == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;

	int timer = 0;
	Graph *rev_graph = NULL; //reversed graph

	int *colour = (int *)malloc(graph->size * sizeof(int));
	if (colour == NULL) return ALLOCATION_ERROR;

	int *parent = (int *)malloc(graph->size * sizeof(int));
	if (parent == NULL) return ALLOCATION_ERROR;

	int *time_in = (int *)malloc(graph->size * sizeof(int));
	if (time_in == NULL) return ALLOCATION_ERROR;

	int *time_out = (int *)malloc(graph->size * sizeof(int));
	if (time_out == NULL) return ALLOCATION_ERROR;

	int *topsort = (int *)malloc(graph->size * sizeof(int));
	if (topsort == NULL) return ALLOCATION_ERROR;

	for (size_t i = 0; i < graph->size; i++) {
		colour[i] = WHITE;
		parent[i] = -1;
		time_in[i] = -1;
		time_out[i] = -1;
		topsort[i] = -1;
	}

	//DFS for graph
	for (size_t i = 0; i < graph->size; i++) {
		if (colour[i] == WHITE) {
			DFS(graph, i, -1, colour, parent, time_in, time_out, &timer);
		}
	}

	//получить список вершин topsort в порядке убывания time_out
	int j = -1;
	for (size_t i = 0; i < graph->size; i++) {
		j = max(time_out, graph->size); 
		time_out[j] = -1; //////
		topsort[i] = j;
	}

	//get new reversed graph
	rev_graph = reverse(graph);
	if (rev_graph == NULL) return ALLOCATION_ERROR;

	//printf("REVERSED:\n");
	//printGraph(rev_graph);

	//colour all verteces in white
	for (size_t i = 0; i < graph->size; i++) colour[i] = WHITE;

	//DFS for reversed graph
	//get components
	*components = (int **)calloc(graph->size, sizeof(int *));
	if (*components == NULL) return ALLOCATION_ERROR;
	*comp_quantity = 0;

	*sizes = (size_t *)calloc(graph->size, sizeof(size_t));
	if (*sizes == NULL) return ALLOCATION_ERROR;

	for (size_t i = 0; i < graph->size; i++) {
		//printf("colour[%zu]: %d\n", i, colour[i]);
		if (colour[i] == WHITE) { ////////////
			//printf("BEGINNING: %s\n", graph->verteces[i]->name);
			//create new component
			(*components)[*comp_quantity] = (int *)malloc(graph->size * sizeof(int));
			if ((*components)[*comp_quantity] == NULL) return ALLOCATION_ERROR;
			(*comp_quantity)++;

			//add vertices to new component
			DFS_r(rev_graph, topsort[i], colour, (*components)[*comp_quantity - 1], *sizes, *comp_quantity - 1);
		}
	}

	free(colour);
	free(parent);
	free(time_in);
	free(time_out);
	free(topsort);
	destroyGraph(rev_graph);

	return OK;
}


void printComponents(Graph *graph, int **components, size_t *sizes, size_t comp_quantity) {
	if (graph == NULL) return;
	if (components == NULL || sizes == NULL) return;
	if (comp_quantity == 0) return;

	int index = 0;
	//printf("comp_quantity = %zu\n", comp_quantity);
	for (size_t i = 0; i < comp_quantity; i++) {
	//	printf("size[%zu] = %zu\n", i, sizes[i]);
		for (size_t j = 0; j < sizes[i]; j++) {
			//printf("SIZE[%zu] = %zu\n", i, sizes[i]);
			index = (components[i])[j];
			printf("%s  ", graph->verteces[index]->name);
		}
		printf("\n");
	}
}


int max(int *array, size_t size) {
	if (array == NULL) return -1;
	int max = -INT_MAX;
	int index = -1;

	for (size_t i = 0; i < size; i++) {
		if (max < array[i]) {
			max = array[i];
			index = i;
		}
	}
	return index;
}


Graph *reverse(Graph *graph) {
	if (graph == NULL) return NULL;
	Node *curr = NULL;

	Graph *res = createGraph();
	if (res == NULL) return NULL;

	for (size_t i = 0; i < graph->size; i++) {
		insertVertex(res, graph->verteces[i]->name, graph->verteces[i]->port);
	}

	for (size_t i = 0; i < graph->size; i++) {
		curr = graph->verteces[i]->link->head;
		while (curr != NULL) {
			insertEdge(res, curr->edge->vertex, graph->verteces[i]->name, NULL);
			curr = curr->next;
		}
	}
	
	return res;
}


//TODO
int fordBellman(Graph *graph, char *name1, char *name2, size_t port) {
	if (graph == NULL) return ALLOCATION_ERROR;
	if (name1 == NULL || name2 == NULL) return ALLOCATION_ERROR;

	int start = -1;
	int end = -1;

	//check vertices
        for (size_t i = 0; i < graph->size; i++) {
                if (start != -1 && end != -1) {
                        break;
                } else if (strcmp(graph->verteces[i]->name, name1) == 0) {
                        start = i;
                } else if (strcmp(graph->verteces[i]->name, name2) == 0) {
                        end = i;
                }
        }

	// start == end
	if (start != -1 || end != -1) {
		if (strcmp(name1, name2) == 0) {
			printPath(graph, end, NULL, NULL);
			return OK;
		}
	}

	if (start == -1 || end == -1) return VERTEX_NOT_FOUND;

	//create distances and predecessors
	int *dist = (int *)malloc(graph->size * sizeof(int));
	if (dist == NULL) return ALLOCATION_ERROR;

	int *pred = (int *)malloc(graph->size * sizeof(int));
	if (pred == NULL) return ALLOCATION_ERROR;

	for (size_t i = 0; i < graph->size; i++) {
		dist[i] = INT_MAX;
		pred[i] = -1;
	}
	dist[start] = 0;

	//find minimal path
	Node *curr = NULL;
	int v = -1;
	for (size_t i = 0; i < graph->size; i++) {
		if (dist[i] != INT_MAX) {
			curr = graph->verteces[i]->link->head;
			while (curr != NULL) {
				v = search(graph, curr->edge->vertex);
				if (accecible(graph, i, v) && graph->verteces[v]->port == port) {
					if (dist[i] + 1 < dist[v]) {
						dist[v] = dist[i] + 1;
						pred[v] = i;
					}
				}
				curr = curr->next;
			}
		}
	}
	
	printPath(graph, end, pred, dist);
	return OK;
}


void printPath(Graph *graph, int end, int *pred, int *dist) {
	if (graph == NULL) return;
	if (pred == NULL || dist == NULL) {
		printf("MINIMAL PATH LENGTH: 0\n");
		return;
	}

	if (dist[end] == INT_MAX) {
		printf("PATH WAS NOT FOUND\n");
	} else {
		printf("MINIMAL PATH LENGTH: %d\n", dist[end]);

		int *path = (int *)malloc(graph->size * sizeof(int));
		if (path == NULL) return;

		int i = end;
		int index = 0;
		while (i != -1) {
			path[index++] = i;
			i = pred[i];
		}

		for (int i = index - 1; i >= 0; i--) {
			printf("%s  ", graph->verteces[path[i]]->name);
		}
		printf("\n");

		free(path);
	}
}
	
	
int visualiseGraph(Graph *graph, char *filename) {
	if (graph == NULL || filename == NULL) return ALLOCATION_ERROR;
	if (graph->size == 0) return EMPTY;
	
	FILE *file = fopen(filename, "w");
	if (file == NULL) return READING_FILE_ERROR;

	fprintf(file, "digraph test_graph {\n");
	Node *curr = NULL;
	
	for (size_t i = 0; i < graph->size; i++) {
		fprintf(file, "\t%s;\n", graph->verteces[i]->name);

		curr = graph->verteces[i]->link->head;
		while (curr != NULL) {
			fprintf(file, "\t%s -> %s;\n", graph->verteces[i]->name, curr->edge->vertex);
			curr = curr->next;
		}
	}

	fprintf(file, "}\n");
	fclose(file);

	return OK;
}

