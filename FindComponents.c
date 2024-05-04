/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA3
* FindComponents.c
* FindComponents file containing the main execution of functions from Graph.c
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

#define MAX 300

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid Argument.\nUsage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE *in, *out;
    char line[MAX];
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading.\n", argv[1]);
        exit(1);
    }

    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    fgets(line, MAX, in);
    int size = 0;
    sscanf(line, "%d", &size);

    List S = newList();

    for (int i = 1; i <= size; ++i) {
        append(S, i);
    }

    Graph G = newGraph(size);

    while (fgets(line, MAX, in) != NULL) {
        int a = 0;
        int b = 0;
        sscanf(line, "%d %d", &a, &b);

        if (a == 0 && b == 0) {
            break;
        }

        addArc(G, a, b);
    }

    DFS(G, S);

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    Graph T = transpose(G);

    int SCC = 0;
    DFS(T, S);
    moveFront(S);

    while (index(S) >= 0) {

        if (getParent(T, get(S)) == NIL) {
            SCC++;
        }

        moveNext(S);
    }

    List SCCTree[SCC];

    for (int i = 0; i < SCC; ++i) {
        SCCTree[i] = newList();
    }

    moveFront(S);
    int l = SCC;

    while (index(S) >= 0) {

        if(getParent(T, get(S)) == NIL) {
            --l;
        }

        if (l == SCC) {
            break;
        }

        append(SCCTree[l], get(S));
        moveNext(S);
    }

    fprintf(out, "\nG contains %d strongly connected components: ", SCC);

    for (int m = 0; m < SCC; ++m) {
        fprintf(out, "\nComponent %d: ", (m + 1));
        moveFront(SCCTree[m]);

        printList(out, SCCTree[m]);
        
        freeList(&(SCCTree[m]));
    }

    fprintf(out, "\n");
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);

    fclose(in);
    fclose(out);
    return(0);
}