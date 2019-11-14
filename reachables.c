#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "GraphFunctions.h"

typedef struct ReachablesMatrixRow {
    int num_reachable;
    int* reachables;
} reachablesMatrixRow;


reachablesMatrixRow* reachablesGraph(int num_vertices){
    reachablesMatrixRow* output = (reachablesMatrixRow*) calloc(num_vertices, sizeof(reachablesMatrixRow));
    for (int i = 0; i < num_vertices; i++) {
        output[i].reachables = (int*) calloc(num_vertices, sizeof(int));
    }
    return output;
}

void freereachablesGraph(reachablesMatrixRow* input,int num_vertices){
    for (int i = 0; i < num_vertices; ++i) {
        free(input[i].reachables);
    }
    free(input);
}

void addReachability(reachablesMatrixRow* input,int sourceIndex, int destinationIndex){
    if(sourceIndex==destinationIndex){
        printf("Implementation does not support sourceIndex == destinationIndex\n");
        return;
    }
    input[sourceIndex].reachables[input[sourceIndex].num_reachable] = destinationIndex;
    input[sourceIndex].num_reachable++;

    input[destinationIndex].reachables[input[destinationIndex].num_reachable] = sourceIndex;
    input[destinationIndex].num_reachable++;

}

void initializeReachableswithGraph(reachablesMatrixRow* rm, graph* input_graph){
    int num_vertices = input_graph->num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        int destination, source = i + 1;
        adjlistNode *adjlistRover = input_graph->vertexList[i].head;
        while (adjlistRover) {
            destination = adjlistRover->destination;
            if (source == destination) {
                adjlistRover = adjlistRover->next;
                continue;
            }

            rm[source-1].reachables[rm[source-1].num_reachable] = destination-1;
            rm[source-1].num_reachable++;
            adjlistRover = adjlistRover->next;
        }
    }
}