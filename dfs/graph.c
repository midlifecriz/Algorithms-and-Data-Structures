#include "graph.h"

#define SPARSE  0.2
#define DENSE   0.8 

Node* createNode(int num) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->number = num;
    node->next = NULL;
    return node;
}


void destroyNode(Node* node) {
    if (node == NULL) return;
    free(node);
}


List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->head = NULL;
    return list;
}


void destroyList(List* list) {
    if (list == NULL) return;
    Node* curr = list->head;
    Node* tmp = curr;
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(list);
}


void push(List* list, int num) {
    if (list == NULL) return;
    Node* node = createNode(num);
    if (node == NULL) return;

    node->next = list->head;
    list->head = node;
}


Graph *createGraph(size_t size) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL) return NULL;
    graph->size = size;

    graph->adj_lists = (List **)malloc(size * sizeof(List*));
    if (graph->adj_lists == NULL) {
        free(graph);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        graph->adj_lists[i] = createList();
        if (graph->adj_lists[i] == NULL) {
            for (size_t j = 0; j < i; j++) destroyList(graph->adj_lists[j]);
            free(graph->adj_lists);
            free(graph);
            return NULL;
        }
    }

    return graph;
}


void addEdge(Graph* graph, int src, int dest) {
    if (graph == NULL) return;
    if (src >= graph->size || dest >= graph->size) return;
    push(graph->adj_lists[src], dest);
}


bool edgeExists(Graph* graph, int src, int dest) {
    if (graph == NULL) return false;
    if (src >= graph->size || dest >= graph->size) return false;

    Node *curr = graph->adj_lists[src]->head;
    while (curr != NULL) {
        if (curr->number == dest) return true;
        curr = curr->next;
    }
    return false;
}


Graph* generateRandomGraph(size_t size) {
    if (size == 0 || size == 1) return NULL;
    Graph* graph = createGraph(size);
    if (graph == NULL) return NULL;

    srand(time(NULL));
    int src = 0;
    int dest = 0;
    int max_possible_edges = size * (size - 1);
    int quantity_of_edges = rand() % max_possible_edges;
    int edges_added = 0;
    int attempts = 0;
    int max_attempts = quantity_of_edges * 10;

    while (edges_added < quantity_of_edges && attempts < max_attempts) {
        attempts++;
        src = rand() % size;
        dest = rand() % size;

        //пропускаем петли и уже существующие ребра
        if (src == dest) continue;
        if (edgeExists(graph, src, dest)) continue;

        addEdge(graph, src, dest);
        edges_added++;
    }

    return graph;
}


//TODO
Graph* generateSparseGraph(size_t size) {
    if (size == 0 || size == 1) return NULL;
    Graph* graph = createGraph(size);
    if (graph == NULL) return NULL;

    srand(time(NULL));
    int src = 0;
    int dest = 0;
    int max_possible_edges = size * (size - 1);
    int quantity_of_edges = (int)(max_possible_edges * SPARSE);
    int edges_added = 0;
    int attempts = 0;
    int max_attempts = quantity_of_edges * 10;

    while (edges_added < quantity_of_edges && attempts < max_attempts) {
        attempts++;
        src = rand() % size;
        dest = rand() % size;

        //пропускаем петли и уже существующие ребра
        if (src == dest) continue;
        if (edgeExists(graph, src, dest)) continue;

        addEdge(graph, src, dest);
        edges_added++;
    }

    return graph;
}


Graph* generateDenseGraph(size_t size) {
    if (size == 0 || size == 1) return NULL;
    Graph* graph = createGraph(size);
    if (graph == NULL) return NULL;

    srand(time(NULL));
    int src = 0;
    int dest = 0;
    int max_possible_edges = size * (size - 1);
    int quantity_of_edges = (int)(max_possible_edges * DENSE);
    int edges_added = 0;
    int attempts = 0;
    int max_attempts = quantity_of_edges * 10;

    while (edges_added < quantity_of_edges && attempts < max_attempts) {
        attempts++;
        src = rand() % size;
        dest = rand() % size;

        //пропускаем петли и уже существующие ребра
        if (src == dest) continue;
        if (edgeExists(graph, src, dest)) continue;

        addEdge(graph, src, dest);
        edges_added++;
    }

    return graph;
}

void destroyGraph(Graph *graph) {
        if (graph == NULL) return;

        for (size_t i = 0; i < graph->size; i++) {
                destroyList(graph->adj_lists[i]);
        }

        free(graph->adj_lists);
        free(graph);
}


void DFS(Graph* graph, int v, int* colour, int* visited, int* visited_count) {
    if (graph == NULL) return;

    //Добавляем текущую вершину v в массив посещенных
    visited[*visited_count] = v;
    (*visited_count)++;

    //Помечаем ее как посещенную
    colour[v] = GREY;

    Node* current = graph->adj_lists[v]->head;
    //Проходим по всем соседям вершины v
    while (current != NULL) {
            if (colour[current->number] == WHITE) {
                    DFS(graph, current->number, colour, visited, visited_count);
            }
            current = current->next;
    }

    //Помечаем как полностью обработанную
    colour[v] = BLACK;
}


void shellForDFS(Graph* graph, int* colour, int* visited, int* visited_count) {
    if (graph == NULL) return;
    
    // Инициализируем все вершины как непосещенные
    for (int i = 0; i < graph->size; i++) {
        colour[i] = WHITE;
    }
    
    // Запускаем DFS для каждой белой вершины
    for (int i = 0; i < graph->size; i++) {
        if (colour[i] == WHITE) {
            DFS(graph, i, colour, visited, visited_count);
        }
    }
}

