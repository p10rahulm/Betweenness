#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../common_header.h"

/*
 * For each node in i=source, j=target where i!=j and
 * k = intermediate, such that k!=i, k!=j,
 * and betweennessCentrality Vector g,
 *
 * For each i,j
 *      num_shortest_paths = total number of shortest paths through i,j
 *      g(k) += Number of shortest paths
 *
*/

void dfs_recursor_nodewise_btnC(float* betweennessCentrality, nodesArray* vvArray,
                                unsigned short sourceIndex,unsigned short destinationIndex,
                                unsigned short interIndex,int* nodeVisitTime,int num_shortest_paths){
    if(destinationIndex==interIndex){

    }

    vvNode* ijnode = &vvArray->vvnodes[arrayIndex(sourceIndex,destinationIndex)];
    vvNode* iknode = &vvArray->vvnodes[arrayIndex(sourceIndex,interIndex)];
    vvNode* kjnode = &vvArray->vvnodes[arrayIndex(interIndex,destinationIndex)];
    prevHopNode* prevhop = iknode->previous_hop;
    if(!prevhop){return;}
    if(prevhop->node_no-1==sourceIndex){ return;}
    while(prevhop){
        unsigned short num_vertices = vvArray->number_of_vertices;
        unsigned short pathNodeIndex = prevhop->node_no-1;
        if(pathNodeIndex==sourceIndex || nodeVisitTime[pathNodeIndex] >= sourceIndex*num_vertices + destinationIndex){
            prevhop = prevhop->next;
            continue;
        }
        int sourcePathNode_numSPs = iknode->num_shortest_paths;
        int pathNodeDest_numSPs = kjnode->num_shortest_paths;

        betweennessCentrality[pathNodeIndex] += (float) sourcePathNode_numSPs * (float) pathNodeDest_numSPs / num_shortest_paths;
        nodeVisitTime[pathNodeIndex] = sourceIndex*num_vertices + destinationIndex;
        if(sourcePathNode_numSPs*pathNodeDest_numSPs > num_shortest_paths){
            printf("\nEncountered ERROR. sourcenode = %d, destnode = %d, pathnode = %d,"
                   "sourcePathNode_numSPs = %d, pathNodeDest_numSPs = %d, num_shortest_paths = %d\n",sourceIndex,destinationIndex,pathNodeIndex,sourcePathNode_numSPs,pathNodeDest_numSPs,num_shortest_paths);
        }
        dfs_recursor_nodewise_btnC( betweennessCentrality, vvArray,sourceIndex,destinationIndex,pathNodeIndex,nodeVisitTime,num_shortest_paths);
        prevhop = prevhop->next;
    }
}


void dfs_recursor_nodewise_btnC2(float* betweennessCentrality, nodesMatrix* vvmatrix,
                                unsigned short sourceIndex,unsigned short destinationIndex,
                                unsigned short interIndex,int* nodeVisitTime,int num_shortest_paths){
    prevHopNode* prevhop = vvmatrix->matrix[sourceIndex][interIndex].previous_hop;
    if(!prevhop){return;}
    if(prevhop->node_no-1==sourceIndex){ return;}
    while(prevhop){
        unsigned short num_vertices = vvmatrix->number_of_vertices;
        unsigned short pathNodeIndex = prevhop->node_no-1;
        if(pathNodeIndex==sourceIndex || nodeVisitTime[pathNodeIndex] >= sourceIndex*num_vertices + destinationIndex){
            prevhop = prevhop->next;
            continue;
        }
        int sourcePathNode_numSPs = vvmatrix->matrix[sourceIndex][pathNodeIndex].num_shortest_paths;
        int pathNodeDest_numSPs = vvmatrix->matrix[pathNodeIndex][destinationIndex].num_shortest_paths;
        betweennessCentrality[pathNodeIndex] += (float) sourcePathNode_numSPs * (float) pathNodeDest_numSPs / num_shortest_paths;
        nodeVisitTime[pathNodeIndex] = sourceIndex*num_vertices + destinationIndex;
        if(sourcePathNode_numSPs*pathNodeDest_numSPs > num_shortest_paths){
            printf("\nEncountered ERROR. sourcenode = %d, destnode = %d, internode = %d\n",sourceIndex,destinationIndex,pathNodeIndex);
        }
        dfs_recursor_nodewise_btnC2( betweennessCentrality, vvmatrix,sourceIndex,destinationIndex,pathNodeIndex,nodeVisitTime,num_shortest_paths);
        prevhop = prevhop->next;
    }
}



float* betweenness_centrality1(nodesMatrix* nodesMatrix){
    unsigned short num_vertices = nodesMatrix->number_of_vertices;
    float* betweennessCentrality = (float*) malloc(num_vertices* sizeof(float));
    int* nodeVisitTime = (int*) malloc(num_vertices*sizeof(int));
    for (int i = 0; i < num_vertices; ++i) {
        betweennessCentrality[i]=0;
        nodeVisitTime[i]=-1;
    }
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i+1; j < num_vertices; j++) {
            if(i!=j){
                int num_shortest_paths = nodesMatrix->matrix[i][j].num_shortest_paths;
                dfs_recursor_nodewise_btnC2(betweennessCentrality, nodesMatrix,i,j,j,nodeVisitTime,num_shortest_paths);
            }
        }
    }
    free(nodeVisitTime);
    return betweennessCentrality;
}


float* betweenness_centrality2(nodesArray* nodesArray){
    unsigned short num_vertices = nodesArray->number_of_vertices;
    float* betweennessCentrality = (float*) malloc(num_vertices* sizeof(float));
    int* nodeVisitTime = (int*) malloc(num_vertices*sizeof(int));
    for (int i = 0; i < num_vertices; ++i) {
        betweennessCentrality[i]=0;
        nodeVisitTime[i]=-1;
    }
    for (int i = 0; i < num_vertices; i++) {
        for (int j = i+1; j < num_vertices; j++) {
            if(i!=j){
                int num_shortest_paths = nodesArray->vvnodes[arrayIndex(i,j)].num_shortest_paths;
                prevHopNode* subGraphNodeRover = nodesArray->vvnodes[arrayIndex(i,j)].previous_hop;
                while(subGraphNodeRover){
                    if(subGraphNodeRover->node_no-1!=i && subGraphNodeRover->node_no-1!=j)
                        dfs_recursor_nodewise_btnC(betweennessCentrality, nodesArray,i,j,subGraphNodeRover->node_no-1,nodeVisitTime,num_shortest_paths);
                    subGraphNodeRover = subGraphNodeRover->next;
                }

            }
        }
    }
    free(nodeVisitTime);
    return betweennessCentrality;
}


void print_btnC2(float* betweennessCentralityArray,int num_vertices){
    printf("\n");
    for (int i = 0; i < num_vertices; ++i) {
        printf("(%d,%f)",i+1,betweennessCentralityArray[i]);
        if(i!=num_vertices-1)printf("\n");
    }
    printf("\n");
}