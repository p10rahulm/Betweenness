
#ifndef BETWEENNESSCENTRALITY_PROCESSEDGRAPH_H
#define BETWEENNESSCENTRALITY_PROCESSEDGRAPH_H

//// The following are required headers to make processed graphs work

#include "graphFunctions.h"

//// These are the structures we will use to process graphs


typedef struct VVNode {
    int shortestPath_distance;
    unsigned short num_shortest_paths;
} vvNode;

//This is a holding structure for our VV Matrix, consisting mainly of nodes.
//Each of these nodes contain shortest path distance and number of shortest paths.

typedef struct NodesArray {
    unsigned short number_of_vertices;
    int num_elements;
    vvNode *vvnodes;
} nodesArray;


//This is a single node in our vertex-vertex (VV) matrix storing shortest path distance and numeber of shortest paths
typedef struct subGraphNode {
    int subGraphNodeIndex;
    struct subGraphNode *next;
} subGraphNode;


typedef struct PathMatrixNode {
    subGraphNode *lastHopList;
} pmNode;

typedef struct PathMatrix {
    unsigned short number_of_vertices;
    pmNode** matrix;
} pathMatrix;


typedef struct processedGraph{
    graph* Graph;
    nodesArray* nodesarray;
    pathMatrix* pathmatrix;
} processedGraph;


//// These are the functions we use on the above structures

nodesArray *initialize_nodesArray(int num_vertices);

void initializeNodesArraywGraph(nodesArray *nodesarray, graph *input_graph);

processedGraph* createProcessedGraph(graph* Graph, nodesArray* nodesarray,pathMatrix* pathmatrix);

int arrayIndex(int row, int col);

void printNodesArray(nodesArray *nodesarray);

void printNodesArray_detailed(nodesArray *nodesarray, pathMatrix* pathmatrix);

void printProcessedGraph(processedGraph* pg);

pathMatrix* initializePathMatrix(int num_vertices);

void initializePathMatrixwGraph(pathMatrix* pathmatrix, graph *input_graph);

void initializeNodesArrayPathsMatrixwGraph(nodesArray *nodesarray,pathMatrix* pathmatrix, graph *input_graph);

void free_nodesArray(nodesArray *arraytoFree);

void freesubGraphNodeList(subGraphNode *head);

void freePathMatrix(pathMatrix* pathmatrix);

void freeProcessedGraph(processedGraph* pg);

void freeProcessedGraphwithoutGraph(processedGraph* pg);

subGraphNode *insertTopList(int subGraphNodeIndex, subGraphNode *head);

subGraphNode *copyList(subGraphNode *head);

subGraphNode *sortedMergeLists(subGraphNode *newHead, subGraphNode *oldHead);

subGraphNode* createNewNode(int nodeIndex,subGraphNode* nextPointer);

subGraphNode *addNode(int nodeIndextoAdd, subGraphNode* subGraphNodeList);



#endif //BETWEENNESSCENTRALITY_PROCESSEDGRAPH_H
