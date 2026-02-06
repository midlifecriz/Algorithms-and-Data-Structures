#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include "errors.h"
#include "my_readline.h"
#include "input.h"
#include "graph.h"

#define OPTIONS  "(1)Print graph\n(2)Insert new vertex\n(3)Delete vertex\n(4)Insert edge\n(5)Delete edge\n(6)Print edge\n(7)Change data in the vertex\n(8)Change data in the edge\n(9)Visualize graph\n(10)Traverse graph (BFS)\n(11)Find connected component\n(12)Find minimal path\n(13)End of program\n"


enum {
	PRINT = 1,
	INSERT_VERTEX,
	DELETE_VERTEX,
	INSERT_EDGE,
	DELETE_EDGE,
	PRINT_EDGE,
	CHANGE_VERTEX,
	CHANGE_EDGE,
	VISUALIZE,
	TRAVERSE,
	COMPONENT,
	PATH,
	END
};


int main() {
	int status = OK;
	int option = 0;
	size_t port = 0;
	size_t quantity = 0;
	int near = -1;
	size_t comp_quantity = 0;

	char *name = NULL;
	char *name1 = NULL;
	char *name2 = NULL;
	Array *ports = NULL;
	int **components = NULL;
	size_t *sizes = NULL;

	Graph *graph = createGraph();
	if (graph == NULL) return ALLOCATION_ERROR;
	
	while (option != END) {
		printf("____MENU____\n");
		printf("%s", OPTIONS);

		status = getInt(&option, PRINT, END);
		if (status == EOF) {
			destroyGraph(graph);
			return OK;
		}

		switch (option) {
			case PRINT:
				printGraph(graph);
				break;

			case INSERT_VERTEX:
				getchar();
				name = Readline("Input name of new vertex:\n");
				if (name == NULL) {
					destroyGraph(graph);
					return OK;
				}
				
				printf("Input number of active port:\n");
				status = getSize_t(&port, 1, ULONG_MAX);	
				if (status == EOF) {
					destroyGraph(graph);
					return OK;
				}

				status = insertVertex(graph, name, port);
				handleErrors(status);

				if (status == ALLOCATION_ERROR) {
					free(name);
					destroyGraph(graph);
					return ALLOCATION_ERROR;
				}

				free(name);
				break;
		
			case DELETE_VERTEX:
				getchar();
				name = Readline("Input name of vertex:\n");
				if (name == NULL) {
					destroyGraph(graph);
					return OK;
				}

				status = deleteVertex(graph, name);
				handleErrors(status);
				break;

			case INSERT_EDGE:
				getchar();
				name1 = Readline("Input name of first vertex:\n");
				if (name1 == NULL) {
					destroyGraph(graph);
					return OK;
				}
				
				name2 = Readline("Input name of second vertex:\n");
				if (name2 == NULL) {
					destroyGraph(graph);
					return OK;
				}

				printf("Input quantity of ports:\n");
				status = getSize_t(&quantity, 1, ULONG_MAX);
				if (status == EOF) {
					free(name1);
					free(name2);
					destroyGraph(graph);
					return OK;
				}

				ports = inputArray(quantity);
				if (ports == NULL) {
					free(name1);
					free(name2);
					destroyGraph(graph);
					return ALLOCATION_ERROR;
				}

				status = insertEdge(graph, name1, name2, ports);
				handleErrors(status);
				if (status == ALLOCATION_ERROR) {
					free(name1);
					free(name2);
					destroyGraph(graph);
					return ALLOCATION_ERROR;
				}

				destroyArray(ports);
				free(name1);
				free(name2);
				break;

			case DELETE_EDGE:
				getchar();
				name1 = Readline("Input name of first vertex:\n");
				if (name1 == NULL) {
					destroyGraph(graph);
					return OK;
				}
				
				name2 = Readline("Input name of second vertex:\n");
				if (name2 == NULL) {
					destroyGraph(graph);
					return OK;
				}

				status = deleteEdge(graph, name1, name2);
				handleErrors(status);
				free(name1);
				free(name2);
				break;

                        case PRINT_EDGE:
                                getchar();
                                name1 = Readline("Input name of first vertex:\n");
                                if (name1 == NULL) {
                                        destroyGraph(graph);
                                        return OK;
                                }

                                name2 = Readline("Input name of second vertex:\n");
                                if (name2 == NULL) {
					free(name1);
                                        destroyGraph(graph);
                                        return OK;
                                }

                                status = printEdge(graph, name1, name2);
                                handleErrors(status);
                                free(name1);
                                free(name2);
                                break;

			case CHANGE_VERTEX:
				getchar();
				name = Readline("Input name of vertex:\n");
				if (name == NULL) {
					destroyGraph(graph);
					return OK;
				}

				printf("Input number of active port:\n");
				status = getSize_t(&port, 1, ULONG_MAX);
				if (status == EOF) {
					destroyGraph(graph);
					return OK;
				}

				status = changeVertex(graph, name, port);
				handleErrors(status);
				free(name);
				break;
			
			case CHANGE_EDGE: //TODO
				getchar();
				name1 = Readline("Input name of first vertex:\n");
				if (name1 == NULL) {
					destroyGraph(graph);
					return OK;
				}

				name2 = Readline("Input name of second vertex:\n");
				if (name2 == NULL) {
					free(name1);
					destroyGraph(graph);
					return OK;
				}
				
				printf("Input quantity of ports:\n");
				status = getSize_t(&quantity, 1, ULONG_MAX);
				if (status == EOF) {
					free(name1);
					free(name2);
					destroyGraph(graph);
					return OK;
				}

				ports = inputArray(quantity);
				if (ports == NULL) {
					free(name1);
					free(name2);
					destroyGraph(graph);
					return OK;
				}

				status = changeEdge(graph, name1, name2, ports);
				handleErrors(status);
				destroyArray(ports);
				free(name1);
				free(name2);
				break;

			case VISUALIZE:
				status = visualiseGraph(graph, "graph.gv");
				handleErrors(status);
				break;

			case TRAVERSE:
				getchar();
				name = Readline("Input name of vertex:\n");
				if (name == NULL) {
					destroyGraph(graph);
					return OK;
				}

				status = BFS(graph, name, &near);
				handleErrors(status);
				
				if (near != -1) printf("Nearest computer is %s\n", graph->verteces[near]->name);
				near = -1;
				free(name);
				break;

			case COMPONENT:
				status = component(graph, &components, &comp_quantity, &sizes);
				if (status == ALLOCATION_ERROR) {
					destroyGraph(graph);
					return ALLOCATION_ERROR;
				}
				handleErrors(status);

				printComponents(graph, components, sizes, comp_quantity);
				for (size_t i = 0; i < comp_quantity; i++) {
					free(components[i]);
				}
				free(components);
				free(sizes);
				break;

			case PATH:
                                getchar();
                                name1 = Readline("Input name of first vertex:\n");
                                if (name1 == NULL) {
                                        destroyGraph(graph);
                                        return OK;
                                }

                                name2 = Readline("Input name of second vertex:\n");
                                if (name2 == NULL) {
                                        free(name1);
                                        destroyGraph(graph);
                                        return OK;
                                }

                                printf("Input allowed port:\n");
                                status = getSize_t(&port, 1, ULONG_MAX);
                                if (status == EOF) {
                                        free(name1);
                                        free(name2);
                                        destroyGraph(graph);
                                        return OK;
                                }

                                status = fordBellman(graph, name1, name2, port);
                                handleErrors(status);
				if (status == ALLOCATION_ERROR) {
                                	destroyGraph(graph);
                                	free(name1);
                                	free(name2);
					return ALLOCATION_ERROR;
				}

				free(name1);
				free(name2);
                                break;

			case END:
				break;
		}
	}

	destroyGraph(graph);
	return OK;
}

