#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ProcessedGraph.h"


/*
 * Assume 0 based indexing of row and column for correct values


    *   *   *   *
    0   *   *   *
    1   2   *   *
    3   4   5   *

 */
int arrayIndex(int row, int col) {
    if (row == col) { return -1; }
    if (row < col) {
        return (col * (col - 1)) / 2 + row;
    } else {
        return (row * (row - 1)) / 2 + col;
    }
}

nodesArray *initialize_nodesArray(int num_vertices) {
    nodesArray *output = (nodesArray *) calloc(1, sizeof(nodesArray));
    output->number_of_vertices = num_vertices;
    output->num_elements = (num_vertices * num_vertices - 1) / 2;
    output->vvnodes = (vvNode *) calloc(output->num_elements, sizeof(vvNode));
    for (int i = 0; i < output->num_elements; ++i) {
        output->vvnodes[i].shortestPath_distance = INT_MAX;
        output->vvnodes[i].num_shortest_paths = 0;
    }
    return output;
}

pathMatrix* initializePathMatrix(int num_vertices){

    pathMatrix* output = (pathMatrix*) calloc(1,sizeof(pathMatrix));
    output->number_of_vertices = num_vertices;
    output->matrix = (pmNode**) calloc(num_vertices, sizeof(pmNode*));
    for (int i = 0; i < num_vertices; i++) {
        output->matrix[i] = (pmNode*)calloc(num_vertices, sizeof(pmNode));
    }
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            output->matrix[i][j].lastHopList=NULL;
        }
    }
    return output;
}


void printNodesArray(nodesArray *nodesarray) {
    printf("\nPrinting Matrix with %d vertices\n", nodesarray->number_of_vertices);
    int num_vertices = nodesarray->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        //printf("\n-------------Source Vertex No: %d-------------\n",i+1);
        for (int j = 0; j < num_vertices; ++j) {
            if (i == j) {
                printf("%d, %d, %d, %d\n", i + 1, j + 1, 0, 0);
                continue;
            }
            printf("%d, %d, %d, %d",
                   i + 1, j + 1, nodesarray->vvnodes[arrayIndex(i, j)].shortestPath_distance,
                   nodesarray->vvnodes[arrayIndex(i, j)].num_shortest_paths);
            printf("\n");
        }
        printf("\n");
    }
}

void printProcessedGraph(processedGraph* pg) {
    nodesArray* nodesarray = pg->nodesarray;
    pathMatrix* pathmatrix = pg->pathmatrix;
    printf("\nPrinting Matrix with %d vertices\n", nodesarray->number_of_vertices);
    int num_vertices = nodesarray->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        //printf("\n-------------Source Vertex No: %d-------------\n",i+1);
        for (int j = 0; j < num_vertices; ++j) {
            if (i == j) {
                printf("%d, %d, %d, %d\n", i + 1, j + 1, 0, 0);
                continue;
            }
            printf("%d, %d, %d, %d",
                   i + 1, j + 1, nodesarray->vvnodes[arrayIndex(i, j)].shortestPath_distance,
                   nodesarray->vvnodes[arrayIndex(i, j)].num_shortest_paths);

            subGraphNode* subGraphNodeRover;
            if(pathmatrix && pathmatrix->matrix[i][j].lastHopList){
                subGraphNodeRover = pathmatrix->matrix[i][j].lastHopList;
                printf("||");
                while(subGraphNodeRover){
                    printf(", %d",subGraphNodeRover->subGraphNodeIndex+1);
                    subGraphNodeRover = subGraphNodeRover->next;
                }
            }
            printf("||\n");
        }
        printf("\n");
    }
}


void freesubGraphNodeList(subGraphNode *head) {
    subGraphNode *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void free_nodesArray(nodesArray *arraytoFree) {
    free(arraytoFree->vvnodes);
    free(arraytoFree);
}

void freePathMatrix(pathMatrix* pathmatrix){
    int num_vertices = pathmatrix->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            freesubGraphNodeList(pathmatrix->matrix[i][j].lastHopList);
        }
    }
    for (int i = 0; i < num_vertices; ++i) {
        free(pathmatrix->matrix[i]);
    }
    free(pathmatrix->matrix);
    free(pathmatrix);
}

void freeProcessedGraph(processedGraph* pg){
    freeGraph(pg->Graph);
    if(pg->nodesarray){free_nodesArray(pg->nodesarray);}
    if(pg->pathmatrix){freePathMatrix(pg->pathmatrix);}
    free(pg);
}

void freeProcessedGraphwithoutGraph(processedGraph* pg){
    if(pg->nodesarray){free_nodesArray(pg->nodesarray);}
    if(pg->pathmatrix){freePathMatrix(pg->pathmatrix);}
    free(pg);
}


subGraphNode *insertTopList(int subGraphNodeIndex, subGraphNode *head) {
    subGraphNode *new_node;
    new_node = (subGraphNode *) calloc(1, sizeof(subGraphNode));
    new_node->subGraphNodeIndex = subGraphNodeIndex;
    new_node->next = head;
    return new_node;
}

// Function that takes a linked list & returns its complete copy
subGraphNode *copyList(subGraphNode *head) {
    subGraphNode *current = head;    // used to iterate over original list
    subGraphNode *newList = NULL; // head of the new list
    subGraphNode *tail = NULL;    // point to last node in new list

    while (current != NULL) {
        // special case for the first new Node
        if (newList == NULL) {
            newList = (subGraphNode *) calloc(1, sizeof(subGraphNode));
            newList->subGraphNodeIndex = current->subGraphNodeIndex;
            newList->next = NULL;
            tail = newList;
        } else {
            tail->next = (subGraphNode *) calloc(1, sizeof(subGraphNode));
            tail = tail->next;
            tail->subGraphNodeIndex = current->subGraphNodeIndex;
            tail->next = NULL;
        }
        current = current->next;
    }

    return newList;
}

subGraphNode* createNewNode(int nodeIndex,subGraphNode* nextPointer){
    subGraphNode* newNode = (subGraphNode *) calloc(1, sizeof(subGraphNode));
    newNode->subGraphNodeIndex = nodeIndex;
    newNode->next = nextPointer;
    return newNode;
}

void initializeNodesArraywGraph(nodesArray *nodesarray, graph *input_graph) {
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
            vvNode *currentNode = &(nodesarray->vvnodes[arrayIndex(source - 1, destination - 1)]);
            currentNode->num_shortest_paths = 1;
            currentNode->shortestPath_distance = 1;
            adjlistRover = adjlistRover->next;
        }
    }
}

void initializePathMatrixwGraph(pathMatrix* pathmatrix, graph *input_graph) {
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
            pathmatrix->matrix[source-1][destination-1].lastHopList = createNewNode(destination-1,NULL);
            adjlistRover = adjlistRover->next;
        }
    }

}

processedGraph* createProcessedGraph(graph* Graph, nodesArray* nodesarray,pathMatrix* pathmatrix){
    processedGraph* pg = (processedGraph*) calloc(1, sizeof(processedGraph));
    pg->Graph = Graph;
    pg->nodesarray = nodesarray;
    pg->pathmatrix = pathmatrix;
    return pg;
}

void initializeNodesArrayPathsMatrixwGraph(nodesArray *nodesarray,pathMatrix* pathmatrix, graph *input_graph) {
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
            vvNode *currentNode = &(nodesarray->vvnodes[arrayIndex(source - 1, destination - 1)]);
            currentNode->num_shortest_paths = 1;
            currentNode->shortestPath_distance = 1;
            pathmatrix->matrix[source-1][destination-1].lastHopList = createNewNode(source-1,NULL);
            adjlistRover = adjlistRover->next;
        }
    }
}

//**IMPORTANT FUNCTION BELOW**//
// Adds a copy of new list to old list without duplicates
subGraphNode *sortedMergeLists(subGraphNode *newHead, subGraphNode* oldHead) {
    if (newHead == NULL) { return oldHead; } // nothing to add
    if (oldHead == NULL) { return copyList(newHead); } // return a copy of the new list

    if (newHead->subGraphNodeIndex == oldHead->subGraphNodeIndex) {
        return (sortedMergeLists(newHead->next, oldHead));
    }
    subGraphNode* result;
    /* Pick either newHead or oldHead, and do recursive */
    if (oldHead->subGraphNodeIndex > newHead->subGraphNodeIndex) {
        result = oldHead;
        result->next = sortedMergeLists(newHead, oldHead->next);
    } else {
        result = (subGraphNode*) calloc(1, sizeof(subGraphNode));
        result->subGraphNodeIndex = newHead->subGraphNodeIndex;
        result->next = sortedMergeLists(newHead->next, oldHead);
    }
    return (result);
}

// Adds a copy of new list to old list without duplicates
subGraphNode *addNode(int nodeIndextoAdd, subGraphNode* subGraphNodeList) {
    if (nodeIndextoAdd < 0) { return subGraphNodeList; } // nothing to add
    if (subGraphNodeList == NULL) { return createNewNode(nodeIndextoAdd,NULL); } // return a copy of the new list

    subGraphNode* head = subGraphNodeList;
    subGraphNode* subgraphRoverPrev;
    subGraphNode* subgraphRover = subGraphNodeList;
    if(subgraphRover->subGraphNodeIndex == nodeIndextoAdd){return head;}
    if(subgraphRover->subGraphNodeIndex < nodeIndextoAdd){
        subGraphNode* newnode = createNewNode(nodeIndextoAdd,subgraphRover);
        return newnode;
    }
    if(subgraphRover->subGraphNodeIndex > nodeIndextoAdd){
        subgraphRoverPrev = subgraphRover;
        subgraphRover = subgraphRover->next;
    }

    while(subgraphRover){
        if(subgraphRover->subGraphNodeIndex > nodeIndextoAdd){
            subgraphRoverPrev = subgraphRover;
            subgraphRover = subgraphRover->next;
            continue;
        }
        if(subgraphRover->subGraphNodeIndex == nodeIndextoAdd){return head;}
        if(subgraphRover->subGraphNodeIndex < nodeIndextoAdd){
            subGraphNode* newnode = createNewNode(nodeIndextoAdd,subgraphRover);
            subgraphRoverPrev->next = newnode;
            return head;
        }
    }
    subgraphRoverPrev->next = createNewNode(nodeIndextoAdd,NULL);
    return head;
}