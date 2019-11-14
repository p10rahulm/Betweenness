#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "BetweennessCentrality.h"

void dfs_recursor_nodewise_btnC(float* betweennessCentrality, processedGraph* processedgraph,
                                unsigned short sourceIndex,unsigned short destinationIndex,
                                unsigned short interIndex,int* nodeVisitTime,int num_shortest_paths){
    //if(destinationIndex==interIndex){return;}
    nodesArray* vvArray = processedgraph->nodesarray;
    pathMatrix* pathmatrix = processedgraph->pathmatrix;
    unsigned short num_vertices = vvArray->number_of_vertices;
    if (interIndex == sourceIndex || nodeVisitTime[interIndex] >= sourceIndex * num_vertices + destinationIndex) {return;}

    vvNode* ijnode = &vvArray->vvnodes[arrayIndex(sourceIndex,destinationIndex)];
    vvNode* iknode = &vvArray->vvnodes[arrayIndex(sourceIndex,interIndex)];
    vvNode* kjnode = &vvArray->vvnodes[arrayIndex(interIndex,destinationIndex)];

    int sourcePathNode_numSPs = iknode->num_shortest_paths;
    int pathNodeDest_numSPs = kjnode->num_shortest_paths;

    betweennessCentrality[interIndex] += (float) sourcePathNode_numSPs * (float) pathNodeDest_numSPs / num_shortest_paths;
    nodeVisitTime[interIndex] = sourceIndex*num_vertices + destinationIndex;


    subGraphNode* prevhop = pathmatrix->matrix[sourceIndex][interIndex].lastHopList;

    if(!prevhop){return;}
    if(prevhop->subGraphNodeIndex ==sourceIndex){ return;}
    while(prevhop){

        unsigned short pathNodeIndex = prevhop->subGraphNodeIndex;
        if(pathNodeIndex==sourceIndex || nodeVisitTime[pathNodeIndex] >= sourceIndex*num_vertices + destinationIndex){
            prevhop = prevhop->next;
            continue;
        }

        if(sourcePathNode_numSPs*pathNodeDest_numSPs > num_shortest_paths){
            printf("\nEncountered ERROR. sourcenode = %d, destnode = %d, pathnode = %d,"
                   "sourcePathNode_numSPs = %d, pathNodeDest_numSPs = %d, num_shortest_paths = %d\n",sourceIndex,destinationIndex,pathNodeIndex,sourcePathNode_numSPs,pathNodeDest_numSPs,num_shortest_paths);
        }
        dfs_recursor_nodewise_btnC( betweennessCentrality, processedgraph,sourceIndex,destinationIndex,pathNodeIndex,nodeVisitTime,num_shortest_paths);

        prevhop = prevhop->next;
    }
}


float* betweenness_centrality(processedGraph* pg){
    nodesArray* nodesarray = pg->nodesarray;
    pathMatrix* pathmatrix = pg->pathmatrix;

    unsigned short num_vertices = nodesarray->number_of_vertices;
    float* betweennessCentrality = (float*) calloc(num_vertices, sizeof(float));
    int* nodeVisitTime = (int*) calloc(num_vertices, sizeof(int));
    for (int i = 0; i < num_vertices; ++i) {
        betweennessCentrality[i]=0;
        nodeVisitTime[i]=-1;
    }
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i+1; j < num_vertices; j++) {
            if(i!=j){
                int num_shortest_paths = nodesarray->vvnodes[arrayIndex(i,j)].num_shortest_paths;
                subGraphNode* subGraphNodeRover = pathmatrix->matrix[i][j].lastHopList;
                while(subGraphNodeRover){
                    if(subGraphNodeRover->subGraphNodeIndex!=i && subGraphNodeRover->subGraphNodeIndex!=j)
                        dfs_recursor_nodewise_btnC(betweennessCentrality, pg,i,j,subGraphNodeRover->subGraphNodeIndex,nodeVisitTime,num_shortest_paths);
                    subGraphNodeRover = subGraphNodeRover->next;
                }

            }
        }
    }
    free(nodeVisitTime);
    return betweennessCentrality;
}

float *betweenness_centralityLowMem(processedGraph *pg) {
    nodesArray *nodesarray = pg->nodesarray;
    int num_vertices = nodesarray->number_of_vertices;
    float *betweennessValues = calloc(num_vertices, sizeof(float));
    for (int i = 0; i < num_vertices; ++i) {
        betweennessValues[i] = 0.0;
    }
    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            if (i == k) { continue; }
            for (int j = i+1; j < num_vertices; ++j) {
                if (j == k) { continue; }
                vvNode *ijNode = &nodesarray->vvnodes[arrayIndex(i, j)];
                vvNode *ikNode = &nodesarray->vvnodes[arrayIndex(i, k)];
                vvNode *kjNode = &nodesarray->vvnodes[arrayIndex(k, j)];
                if (ijNode->shortestPath_distance == ikNode->shortestPath_distance + kjNode->shortestPath_distance) {
                    betweennessValues[k] += (ikNode->num_shortest_paths * (float) kjNode->num_shortest_paths) /
                                            (float) ijNode->num_shortest_paths;
                }
            }
        }
    }
    return betweennessValues;
}

void print_betweenness(float *betweennessCentralityArray, int num_vertices) {
    printf("\n");
    for (int i = 0; i < num_vertices; ++i) {
        printf("(%d,%f)", i + 1, betweennessCentralityArray[i]);
        if (i != num_vertices - 1)printf("\n");
    }
    printf("\n");
}

void print_betweenness_normalized(float *betweennessCentralityArray, int num_vertices) {
    printf("\n");
    float normalization_factor = (num_vertices-1)*(num_vertices-2)/2;
    for (int i = 0; i < num_vertices; i++) {
        printf("(%d,%f)", i + 1, betweennessCentralityArray[i]/normalization_factor);
        if (i != num_vertices - 1)printf("\n");
    }
    printf("\n");
}

void print_betweenness_normalizedTo1(float *betweennessCentralityArray, int num_vertices) {
    printf("\n");
    float max_betweenness =-1,min_betweenness=INT_MAX,normalized_betweenness, range_betweenness;

    for (int i = 0; i < num_vertices; i++){
        if(betweennessCentralityArray[i]>max_betweenness){
            max_betweenness = betweennessCentralityArray[i];
        }
        if(betweennessCentralityArray[i]<min_betweenness){
            min_betweenness = betweennessCentralityArray[i];
        }
    }
    range_betweenness = max_betweenness - min_betweenness;

    for (int i = 0; i < num_vertices; ++i) {
        normalized_betweenness = (betweennessCentralityArray[i] - min_betweenness)/range_betweenness;
        printf("(%d,%f)", i + 1, normalized_betweenness);
        if (i != num_vertices - 1)printf("\n");
    }
    printf("\n");
}