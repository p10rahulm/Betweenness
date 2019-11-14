#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "BFS.h"


typedef struct simpleQueue {
    int QCurrentSize;
    int QMaxSize;
    int maxHit;
    int QStartIndex;
    int QEndIndex;
    int *nodesArray;
} simpleQueue;


simpleQueue *initializeSimpleQueue(int num_vertices) {
    simpleQueue *out = (simpleQueue *) calloc(1, sizeof(simpleQueue));
    out->QMaxSize = num_vertices;
    out->nodesArray = (int *) calloc(num_vertices, sizeof(int));
    //rest are all initialized to 0 due to calloc
    return out;
}


int Qempty(simpleQueue *sq) {
    if (sq->QCurrentSize == 0) { return 1; }
    return 0;
}

int Qpop(simpleQueue *sq) {
    if (Qempty(sq)) {
        printf("Cannot Pop an empty Q");
        return -1;
    }
    int out = sq->nodesArray[sq->QStartIndex];
    sq->QCurrentSize--;
    sq->QStartIndex++;
    return out;
}

int Qpush(simpleQueue *sq, int number_to_add) {
    if (sq->maxHit) {
        printf("Cannot Add. Queue's capacity hit");
        return 0;
    }
    sq->nodesArray[sq->QEndIndex] = number_to_add;
    sq->QCurrentSize++;
    sq->QEndIndex++;
    if (sq->QMaxSize == sq->QEndIndex) {
        sq->maxHit = 1;
    }
    return 1;
}


void freeQ(simpleQueue *QtoFree) {
    free(QtoFree->nodesArray);
    free(QtoFree);
}

void resetQ(simpleQueue *QtoReset) {
    memset(QtoReset->nodesArray, 0, sizeof(QtoReset->nodesArray));
    QtoReset->QStartIndex = 0;
    QtoReset->QEndIndex = 0;
    QtoReset->maxHit = 0;
    QtoReset->QCurrentSize = 0;
}


typedef struct BFSVertex {
    int distance;
    int visited;
    int predecessor;
} BFSVertex;


typedef struct BFSArray {
    int num_vertices;
    BFSVertex *bfsvertices;
} bfsArray;

bfsArray *initializeBFSArray(int num_vertices) {
    bfsArray *out = (bfsArray *) calloc(1, sizeof(bfsArray));
    out->num_vertices = num_vertices;
    out->bfsvertices = (BFSVertex *) calloc(num_vertices, sizeof(BFSVertex));
    for (int i = 0; i < num_vertices; ++i) {
        out->bfsvertices[i].predecessor = -1;
        out->bfsvertices[i].distance = INT_MAX;
        //out->bfsvertices[i].visited = 0; //Taken Care of by calloc
    }
    return out;
}

void freeBFSArray(bfsArray *bfsarray) {
    free(bfsarray->bfsvertices);
    free(bfsarray);
}

void resetBFSArray(bfsArray *arrayToReset) {
    for (int i = 0; i < arrayToReset->num_vertices; ++i) {
        arrayToReset->bfsvertices[i].visited = 0;
        arrayToReset->bfsvertices[i].predecessor = -1;
        arrayToReset->bfsvertices[i].distance = INT_MAX;
    }
}


void BFS(int sourceIndex, processedGraph* pg, simpleQueue *sq, bfsArray *bfsa) {

    graph* g = pg->Graph;
    nodesArray* na = pg->nodesarray;
    pathMatrix* pm = pg->pathmatrix;

    bfsa->bfsvertices[sourceIndex].visited = 1;
    bfsa->bfsvertices[sourceIndex].distance = 0;
    Qpush(sq, sourceIndex);
    while (!Qempty(sq)) {
        int currentNodeIndex = Qpop(sq);

        adjlistNode *Rover = g->vertexList[currentNodeIndex].head;
        while (Rover) {
            int nextNodeIndex = Rover->destination - 1;
            if (!bfsa->bfsvertices[nextNodeIndex].visited) {
                // WHat all we have to do for current node?
                // 1. We have to update distance from sourceIndex,
                // 2. we have to update number of shortest paths if current is shortest path.
                // 3. We have to update predecessor vertex
                // 4. We have to mark as visited
                bfsa->bfsvertices[nextNodeIndex].visited = 1;
                bfsa->bfsvertices[nextNodeIndex].predecessor = currentNodeIndex;
                bfsa->bfsvertices[nextNodeIndex].distance = bfsa->bfsvertices[currentNodeIndex].distance + 1;
                if (sourceIndex != nextNodeIndex) {
                    na->vvnodes[arrayIndex(sourceIndex, nextNodeIndex)].shortestPath_distance =
                            bfsa->bfsvertices[currentNodeIndex].distance + 1;
                    if (sourceIndex != currentNodeIndex) {
                        na->vvnodes[arrayIndex(sourceIndex, nextNodeIndex)].num_shortest_paths =
                                na->vvnodes[arrayIndex(sourceIndex, currentNodeIndex)].num_shortest_paths;

                        freesubGraphNodeList(pm->matrix[sourceIndex][nextNodeIndex].lastHopList);
                        pm->matrix[sourceIndex][nextNodeIndex].lastHopList = createNewNode(currentNodeIndex,NULL);
                    } else {
                        na->vvnodes[arrayIndex(sourceIndex, nextNodeIndex)].num_shortest_paths = 1;
                        //pm->matrix[sourceIndex][nextNodeIndex].lastHopList = createNewNode(sourceIndex,NULL);
                    }

                }

                int noerror = Qpush(sq, nextNodeIndex);
                if (!noerror) {
                    printf("Error. Q is full");
                    exit(0);
                }

            } else if (bfsa->bfsvertices[nextNodeIndex].visited) {
                if (bfsa->bfsvertices[nextNodeIndex].distance == bfsa->bfsvertices[currentNodeIndex].distance + 1) {
                    if (sourceIndex != nextNodeIndex && sourceIndex != currentNodeIndex) {
                        na->vvnodes[arrayIndex(sourceIndex, nextNodeIndex)].num_shortest_paths +=
                                na->vvnodes[arrayIndex(sourceIndex, currentNodeIndex)].num_shortest_paths;
                        pm->matrix[sourceIndex][nextNodeIndex].lastHopList =
                                addNode(currentNodeIndex,pm->matrix[sourceIndex][nextNodeIndex].lastHopList);
                    }

                };

            }
            Rover = Rover->next;
        }
    }
}

processedGraph* processGraphBFS(graph *input) {

    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    pathMatrix* pathmatrix = initializePathMatrix(num_vertices);
    initializeNodesArrayPathsMatrixwGraph(outnodesArray,pathmatrix, input);
    processedGraph* pg = createProcessedGraph(input, outnodesArray,pathmatrix);


    simpleQueue *sq = initializeSimpleQueue(num_vertices);
    bfsArray *bfsa = initializeBFSArray(num_vertices);

    for (int nodeIndex = 0; nodeIndex < num_vertices; ++nodeIndex) {
        resetBFSArray(bfsa);
        resetQ(sq);
        BFS(nodeIndex, pg, sq, bfsa);
    }
    freeQ(sq);
    freeBFSArray(bfsa);
    return pg;
}