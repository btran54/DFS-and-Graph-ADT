/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA3
* Graph.c
* Graph file containing the operations of functions.
***/ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj {
    List* neighbor;
    int* color;
    int* parent;
    int* discover;
    int* finish;

    int order;
    int size;
} GraphObj;

typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    G->neighbor = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        G->neighbor[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;

        G->order = n;
        G->size = 0;
    }

    return G;
}

void freeGraph(Graph* pG) {
    Graph ptr = *pG;

    for (int i = 1; i <= getOrder(ptr); i++) {
        freeList(&(ptr->neighbor[i]));
    }

    free(ptr->neighbor);
    free(ptr->color);
    free(ptr->parent);
    free(ptr->discover);
    free(ptr->finish);
    free(*pG);
}

int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling getOrder() on NULL graph reference.\n");
        exit(1);
    }

    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling getOrder() on NULL graph reference.\n");
        exit(1);
    }

    return G->size;
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Calling getParent() on NULL graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannot call getParent(). u is out of bounds.\n");
        exit(1);
    }

    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Calling getDiscover() on NULL graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannot call getDiscover(). u is out of bounds.\n");
        exit(1);
    }

    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: Calling get finish on NULL graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannot call getFinish(). u is out of bounds.\n");
        exit(1);
    }

    return G->finish[u];
}

bool sortedEdge(List L, int v) {
    if (L == NULL) {
        printf("Graph Error: Calling sortedEdge on NULL list reference.\n");
        exit(1);
    }

    if (length(L) == 0) {
        append(L, v);
        return true;
    }
    moveFront(L);

    while (index(L) != -1) {

        if (v == get(L)) {
            return false;
        }

        if (v < get(L)) {
            insertBefore(L, v);
            return true;
        }

        moveNext(L);
    }

    append(L, v);
    return true;
}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: Calling addArc() on NULL graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannot call addArc(). u is out of bounds.\n");
        exit(1);
    }

    if (!(1 <= v && v <= getOrder(G))) {
        printf("Graph Error: Cannot call addArc(). v is out of bounds.\n");
        exit(1);
    }

    if (sortedEdge(G->neighbor[u], v)) {
        G->size++;
    }
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: Calling addEdge() on NULL Graph reference.\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: Cannor call addArc(). u is out of bounds.\n");
        exit(1);
    }

    if (!(1 <= v && v <= getOrder(G))) {
        printf("Graph Error: Cannot call addArc(). v is out of bounds.\n");
        exit(1);
    }

    sortedEdge(G->neighbor[u], v);
    sortedEdge(G->neighbor[v], u);
    G->size++;
}

void visit(Graph G, List S, int u, int *time) {
    if (G == NULL) {
        printf("Graph Error: Calling DFS() on NULL graph reference.\n");
        exit(1);
    }

    if (S == NULL) {
        printf("List Error: Calling DFS() on NULL list reference.\n");
        exit(1);
    }

    G->discover[u] = ++*time;
    G->color[u] = GRAY;
    moveFront(G->neighbor[u]);

    while (index(G->neighbor[u]) >= 0) {
        int y = get(G->neighbor[u]);

        if (G->color[y] == WHITE) {
            G->parent[y] = u;
            visit(G, S, y, time);
        }

        moveNext(G->neighbor[u]);
    }

    G->color[u] = BLACK;
    G->finish[u] = ++*time;
    prepend(S, u);
}

void DFS (Graph G, List S) {
    if (G == NULL) {
        printf("Graph Error: Calling DFS() on NULL graph reference.\n");
        exit(1);
    }

    if (S == NULL) {
        printf("List Error: Calling DFS() on NULL list reference.\n");
        exit(1);
    }

    if (length(S) != getOrder(G)) {
        printf("Graph Error: Cannot call DFS if length(S) != getOrder(G).\n");
        exit(1);
    }

    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    int time = 0;
    moveFront(S);

    while (index(S) >= 0) {
        int u = get(S);

        if (G->color[u] == WHITE) {
            visit(G, S, u, &time);
        }

        moveNext(S);
    }

    for (int size = length(S) / 2; size > 0; --size) {
        deleteBack(S);
    }
}

Graph transpose(Graph G) {
    Graph T = newGraph(getOrder(G));
    
    for (int i = 1; i <= getOrder(G); ++i) {
        moveFront(G->neighbor[i]);

        while (index(G->neighbor[i]) != -1) {
            addArc(T, get(G->neighbor[i]), i);
            moveNext(G->neighbor[i]);
        }
    }

    return T;
}

Graph copyGraph(Graph G) {
    Graph C = newGraph(getOrder(G));

    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->neighbor[i]);

        if (length(G->neighbor[i]) == 0) {
            continue;
        }

        else {

            while (index(G->neighbor[i]) >= 0) {
                addArc(C, i, get(G->neighbor[i]));
                moveNext(G->neighbor[i]);
            }
        }
    }

    return C;
}

void printGraph(FILE* out , Graph G) {
    if (G == NULL) {
        printf("Graph Error: Calling printGraph() on NULL graph reference.\n");
        exit(1);
    }

    for (int i = 1; i <= getOrder(G); i++) {
        List list = G->neighbor[i];
        fprintf(out, "%d:", i);
        moveFront(list);

        while (index(list) != -1) {
            fprintf(out, " %d", get(list));
            moveNext(list);
        }

        fprintf(out, "\n");
    }
}