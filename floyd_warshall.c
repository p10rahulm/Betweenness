#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "FloydWarshall.h"


//We provide four implementations of the Floyd Warshall Method. The tests for speed for each of these has been done in the test_floyd_warshall.c method

processedGraph* processGraphFWLowMem(graph *input) {
    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    pathMatrix* pathmatrix = NULL;
    initializeNodesArraywGraph(outnodesArray,input);
    //initializeNodesArrayPathsMatrixwGraph(outnodesArray,pathmatrix, input);
    processedGraph* pg = createProcessedGraph(input, outnodesArray,pathmatrix);

    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = i+1; j < num_vertices; ++j) {
                if (j == k || k == i) {
                    continue;
                }

                vvNode *ikNode = &(outnodesArray->vvnodes[arrayIndex(i, k)]);
                vvNode *kjNode = &(outnodesArray->vvnodes[arrayIndex(k, j)]);
                if (ikNode->shortestPath_distance == INT_MAX || kjNode->shortestPath_distance == INT_MAX) {
                    continue;
                }
                vvNode *ijNode = &(outnodesArray->vvnodes[arrayIndex(i, j)]);
                if (ikNode->shortestPath_distance + kjNode->shortestPath_distance <
                    ijNode->shortestPath_distance) {
                    ijNode->shortestPath_distance = ikNode->shortestPath_distance + kjNode->shortestPath_distance;
                    ijNode->num_shortest_paths = ikNode->num_shortest_paths * kjNode->num_shortest_paths;
                } else if (ikNode->shortestPath_distance + kjNode->shortestPath_distance ==
                           ijNode->shortestPath_distance) {
                    ijNode->num_shortest_paths += ikNode->num_shortest_paths * kjNode->num_shortest_paths;
                }
            }
        }
    }
    return pg;
}

processedGraph* processGraphFWLowMemReachables(graph *input) {
    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    pathMatrix* pathmatrix = initializePathMatrix(num_vertices);
    initializeNodesArrayPathsMatrixwGraph(outnodesArray,pathmatrix, input);
    processedGraph* pg = createProcessedGraph(input, outnodesArray,pathmatrix);

    reachablesMatrixRow* reachables_graph = reachablesGraph(num_vertices);
    initializeReachableswithGraph(reachables_graph, input);

    for (int k = 0; k < num_vertices; ++k) {
        for (int iIndex = 0; iIndex < reachables_graph[k].num_reachable; ++iIndex) {
            for (int jIndex = iIndex+1; jIndex < reachables_graph[k].num_reachable; ++jIndex) {
                int i = reachables_graph[k].reachables[iIndex];int j = reachables_graph[k].reachables[jIndex];
                if (j == k || k == i) {
                    continue;
                }

                vvNode *ikNode = &(outnodesArray->vvnodes[arrayIndex(i, k)]);
                vvNode *kjNode = &(outnodesArray->vvnodes[arrayIndex(k, j)]);
                if (ikNode->shortestPath_distance == INT_MAX || kjNode->shortestPath_distance == INT_MAX) {
                    continue;
                }
                vvNode *ijNode = &(outnodesArray->vvnodes[arrayIndex(i, j)]);
                if (ikNode->shortestPath_distance + kjNode->shortestPath_distance <
                    ijNode->shortestPath_distance) {
                    if(ijNode->shortestPath_distance == INT_MAX){addReachability(reachables_graph,i,j);}
                    ijNode->shortestPath_distance = ikNode->shortestPath_distance + kjNode->shortestPath_distance;
                    ijNode->num_shortest_paths = ikNode->num_shortest_paths * kjNode->num_shortest_paths;
                } else if (ikNode->shortestPath_distance + kjNode->shortestPath_distance ==
                           ijNode->shortestPath_distance) {
                    ijNode->num_shortest_paths += ikNode->num_shortest_paths * kjNode->num_shortest_paths;
                }
            }
        }
    }

    freereachablesGraph(reachables_graph,num_vertices);
    return pg;
}


processedGraph* processGraphFW(graph *input) {
    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    pathMatrix* pathmatrix = initializePathMatrix(num_vertices);
    initializeNodesArrayPathsMatrixwGraph(outnodesArray,pathmatrix, input);
    processedGraph* pg = createProcessedGraph(input, outnodesArray,pathmatrix);

    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = i+1; j < num_vertices; ++j) {
                if (j == k || k == i) {
                    continue;
                }

                vvNode *ikNode = &(outnodesArray->vvnodes[arrayIndex(i, k)]);
                vvNode *kjNode = &(outnodesArray->vvnodes[arrayIndex(k, j)]);
                if (ikNode->shortestPath_distance == INT_MAX || kjNode->shortestPath_distance == INT_MAX) {
                    continue;
                }
                vvNode *ijNode = &(outnodesArray->vvnodes[arrayIndex(i, j)]);
                if (ikNode->shortestPath_distance + kjNode->shortestPath_distance <
                    ijNode->shortestPath_distance) {
                    ijNode->shortestPath_distance = ikNode->shortestPath_distance + kjNode->shortestPath_distance;
                    ijNode->num_shortest_paths = ikNode->num_shortest_paths * kjNode->num_shortest_paths;

                    freesubGraphNodeList(pathmatrix->matrix[i][j].lastHopList);
                    freesubGraphNodeList(pathmatrix->matrix[j][i].lastHopList);
                    pathmatrix->matrix[i][j].lastHopList = copyList(pathmatrix->matrix[k][j].lastHopList);
                    pathmatrix->matrix[j][i].lastHopList = copyList(pathmatrix->matrix[k][i].lastHopList);
                } else if (ikNode->shortestPath_distance + kjNode->shortestPath_distance ==
                           ijNode->shortestPath_distance) {
                    ijNode->num_shortest_paths += ikNode->num_shortest_paths * kjNode->num_shortest_paths;
                    pathmatrix->matrix[i][j].lastHopList = sortedMergeLists(pathmatrix->matrix[k][j].lastHopList, pathmatrix->matrix[i][j].lastHopList);
                    pathmatrix->matrix[j][i].lastHopList = sortedMergeLists(pathmatrix->matrix[k][i].lastHopList, pathmatrix->matrix[j][i].lastHopList);
                }
            }
        }
    }
    return pg;
}

void doloop(nodesArray* outnodesArray,pathMatrix* pathmatrix,reachablesMatrixRow* reachables_graph,int i, int j, int k, int reachables_update){//mode 0 dont update reachables, mode 1 reachables
    if (j == k || k == i) {
        return;
    }

    vvNode *ikNode = &(outnodesArray->vvnodes[arrayIndex(i, k)]);
    vvNode *kjNode = &(outnodesArray->vvnodes[arrayIndex(k, j)]);
    if (ikNode->shortestPath_distance == INT_MAX || kjNode->shortestPath_distance == INT_MAX) {
        return;
    }
    vvNode *ijNode = &(outnodesArray->vvnodes[arrayIndex(i, j)]);
    if (ikNode->shortestPath_distance + kjNode->shortestPath_distance <
        ijNode->shortestPath_distance) {
        if(reachables_update && ijNode->shortestPath_distance == INT_MAX){addReachability(reachables_graph,i,j);}
        ijNode->shortestPath_distance = ikNode->shortestPath_distance + kjNode->shortestPath_distance;
        ijNode->num_shortest_paths = ikNode->num_shortest_paths * kjNode->num_shortest_paths;

        freesubGraphNodeList(pathmatrix->matrix[i][j].lastHopList);
        freesubGraphNodeList(pathmatrix->matrix[j][i].lastHopList);
        pathmatrix->matrix[i][j].lastHopList = copyList(pathmatrix->matrix[k][j].lastHopList);
        pathmatrix->matrix[j][i].lastHopList = copyList(pathmatrix->matrix[k][i].lastHopList);
    } else if (ikNode->shortestPath_distance + kjNode->shortestPath_distance ==
               ijNode->shortestPath_distance) {
        ijNode->num_shortest_paths += ikNode->num_shortest_paths * kjNode->num_shortest_paths;
        pathmatrix->matrix[i][j].lastHopList = sortedMergeLists(pathmatrix->matrix[k][j].lastHopList, pathmatrix->matrix[i][j].lastHopList);
        pathmatrix->matrix[j][i].lastHopList = sortedMergeLists(pathmatrix->matrix[k][i].lastHopList, pathmatrix->matrix[j][i].lastHopList);
    }
}
processedGraph* processGraphFWReachablesPathMatrix(graph *input, float heuristic) {
    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    pathMatrix* pathmatrix = initializePathMatrix(num_vertices);
    initializeNodesArrayPathsMatrixwGraph(outnodesArray,pathmatrix, input);
    processedGraph* pg = createProcessedGraph(input, outnodesArray,pathmatrix);

    reachablesMatrixRow* reachables_graph = reachablesGraph(num_vertices);
    initializeReachableswithGraph(reachables_graph, input);
    int num_reachable_greater_thenhalf =0;
    for (int k = 0; k < num_vertices; ++k) {
        if(!num_reachable_greater_thenhalf){
            if((float) reachables_graph[k].num_reachable/num_vertices>heuristic){ //some heuristic like 50%
                num_reachable_greater_thenhalf=1;
            }
            for (int iIndex = 0; iIndex < reachables_graph[k].num_reachable; ++iIndex) {
                for (int jIndex = iIndex+1; jIndex < reachables_graph[k].num_reachable; ++jIndex) {
                    int i = reachables_graph[k].reachables[iIndex];
                    int j = reachables_graph[k].reachables[jIndex];
                    doloop(outnodesArray,pathmatrix,reachables_graph,i, j, k, 1);
                }
            }
        } else {
            for (int i = 0; i < num_vertices; ++i) {
                for (int j = i+1; j < num_vertices; ++j) {
                    doloop(outnodesArray,pathmatrix,reachables_graph,i, j, k, 0);
                }
            }
        }

    }

    freereachablesGraph(reachables_graph,num_vertices);
    return pg;
}