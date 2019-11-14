#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../common_header.h"



prevHopNode* create_PrevHopNode(unsigned short prevHopNodeNo){
    prevHopNode* output = calloc(1,sizeof(prevHopNode));
    output->node_no = prevHopNodeNo;
    return output;
}


/*
 * Assume 0 based indexing of row and column for correct values


    *   *   *   *
    0   *   *   *
    1   2   *   *
    3   4   5   *

 */
int arrayIndex(int row,int col){
    if(row==col){return -1;}
    if (row<col){
        return (col*(col-1))/2 + row;
    } else{
        return (row*(row-1))/2 + col;
    }
}

nodesArray* initialize_nodesArray(int num_vertices){
    nodesArray* output = (nodesArray*) malloc(sizeof(nodesArray));
    output->number_of_vertices = num_vertices;
    output->num_elements = (num_vertices*num_vertices-1)/2;
    output->vvnodes = (vvNode*) malloc(output->num_elements*sizeof(vvNode));
    for (int i = 0; i < output->num_elements; ++i) {
        output->vvnodes[i].shortestPath_distance = INT_MAX;
    }
    return output;
}

void printNodesArray(nodesArray* nodesarray){
    printf("\nPrinting Matrix with %d vertices\n",nodesarray->number_of_vertices);
    int num_vertices = nodesarray->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        //printf("\n-------------Source Vertex No: %d-------------\n",i+1);
        for (int j = 0; j < num_vertices; ++j) {
            if(i==j){printf("%d, %d, %d, %d\n", i+1,j+1,0,0);continue;}
            printf("%d, %d, %d, %d",
                   i+1,j+1, nodesarray->vvnodes[arrayIndex(i,j)].shortestPath_distance,
                   nodesarray->vvnodes[arrayIndex(i,j)].num_shortest_paths);
            prevHopNode* prevHopNodeRover;
            if(nodesarray->vvnodes[arrayIndex(i,j)].previous_hop){
                prevHopNodeRover = nodesarray->vvnodes[arrayIndex(i,j)].previous_hop;
                int num_short_path = 1;
                while(prevHopNodeRover){
                    printf(", %d",prevHopNodeRover->node_no);
                    prevHopNodeRover = prevHopNodeRover->next;
                    num_short_path++;
                }
            }

            printf("\n");
        }
        printf("\n");
    }
}



void printNodesMatrix(nodesMatrix* matrix){
    printf("\nPrinting Matrix with %d vertices\n",matrix->number_of_vertices);
    int num_vertices = matrix->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        //printf("\n-------------Source Vertex No: %d-------------\n",i+1);
        for (int j = 0; j < num_vertices; ++j) {
            printf("%d, %d, %d, %d", i+1,j+1,matrix->matrix[i][j].shortestPath_distance,
                   matrix->matrix[i][j].num_shortest_paths);
            prevHopNode* prevHopNodeRover;
            if(matrix->matrix[i][j].previous_hop){
                prevHopNodeRover = matrix->matrix[i][j].previous_hop;
                int num_short_path = 1;
                while(prevHopNodeRover){
                    printf(", %d",prevHopNodeRover->node_no);
                    prevHopNodeRover = prevHopNodeRover->next;
                    num_short_path++;
                }
            }

            printf("\n");
        }
        printf("\n");
    }
}

void free_shortestPathsNodesList(prevHopNode* head) {
    printf("f1");
    prevHopNode* tmp;
    printf("f2");
    while (head != NULL){
        printf("f3");
        tmp = head;
        head = head->next;
        free(tmp);
    }

}

void free_shortestPathsNodesList1(prevHopNode* prevNode){
    printf("free1");
    prevHopNode* current = prevNode;
    prevHopNode* next;
    if(current){
        next = current->next;
    }
    int i =0;
    printf("free8");
    while(current){
        printf("loop no = %d\n",i);
        free(current);
        current = next;
        if(current){
            next = current->next;
        } else{
            continue;
        }
        i++;
    }
    printf("free9");
}


void free_nodesMatrix(nodesMatrix* input){
    int num_vertices = input->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            free_shortestPathsNodesList(input->matrix[i][j].previous_hop);
        }
    }
    for (int i = 0; i < input->number_of_vertices; i++) {
        free(input->matrix[i]);
    }
    free(input->matrix);
    free(input);

}

void free_nodesArray(nodesArray* arraytoFree){
    int num_elements = arraytoFree->num_elements;
    for (int i = 0; i < num_elements; ++i) {
        free_shortestPathsNodesList(arraytoFree->vvnodes[i].previous_hop);
    }
    free(arraytoFree->vvnodes);
    free(arraytoFree);
}

void initializeNodesMatrixwGraph(nodesMatrix* matrix, graph* input_graph){
    int num_vertices = input_graph->num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        int destination, source = i+1;
        adjlistNode* adjlistRover = input_graph->vertexList[i].head;
        while (adjlistRover){
            destination = adjlistRover->destination;
            matrix->matrix[source-1][destination-1].num_shortest_paths = 1;
            matrix->matrix[source-1][destination-1].shortestPath_distance = 1;
            matrix->matrix[source-1][destination-1].previous_hop = create_PrevHopNode(source);
            adjlistRover = adjlistRover->next;
        }
    }

}

void initializeNodesArraywGraph(nodesArray* nodesarray, graph* input_graph){
    int num_vertices = input_graph->num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        int destination, source = i+1;
        adjlistNode* adjlistRover = input_graph->vertexList[i].head;
        while (adjlistRover){
            destination = adjlistRover->destination;
            if(source==destination){
                adjlistRover = adjlistRover->next;
                continue;
            }
            printf("REACHED HERE DURING INITIALIZATION, i = %d, j = %d\n",source,destination);
            vvNode* currentNode = &(nodesarray->vvnodes[arrayIndex(source-1,destination-1)]);
            currentNode->num_shortest_paths =1;
            currentNode->shortestPath_distance =1;
            currentNode->previous_hop = create_PrevHopNode(source);
            printf("nodesarray->vvnodes[arrayIndex(source,destination)].shortestPath_distance = %d\n",nodesarray->vvnodes[arrayIndex(source,destination)].shortestPath_distance);
            printf("nodesarray->vvnodes[arrayIndex(source,destination)].num_shortest_paths = %d\n",nodesarray->vvnodes[arrayIndex(source,destination)].num_shortest_paths);
            adjlistRover = adjlistRover->next;
        }
    }

}


int find_in_previous_hops_list(prevHopNode* list_node, unsigned short num_to_find){
    //1 means found, 0 means not found
    if(!list_node){
        return 0;
    }
    while (list_node){
        if(list_node->node_no==num_to_find){return 1;}
        list_node = list_node->next;
    }
    return 0;
}


nodesArray* floydWarshall (graph* input){
    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    initializeNodesArraywGraph(outnodesArray,input);
    graph* reachables_graph = copyGraph(input);
    for (int interIndex = 0; interIndex < num_vertices; ++interIndex) {
        adjlistNode* firstIterator = reachables_graph->vertexList[interIndex].head;
        while(firstIterator){
            adjlistNode* secondIterator = firstIterator->next;
            while(secondIterator){
                //first and second iterator are connected through the interIndex Node. So check everything.
                int i = firstIterator->destination-1,j=secondIterator->destination-1,k = interIndex;
                //Check to ensure that nodesarray is not hit with equal values
                if(i==j||j==k||k==i){secondIterator = secondIterator->next;continue;}
                vvNode* ijNode = &(outnodesArray->vvnodes[arrayIndex(i,j)]);
                vvNode* ikNode = &(outnodesArray->vvnodes[arrayIndex(i,k)]);
                vvNode* kjNode = &(outnodesArray->vvnodes[arrayIndex(k,j)]);
                if(ijNode->shortestPath_distance==INT_MAX){
                    if(i==j){
                        printf("ERROR,ERROR, k = %d, i = %d, j = %d",k,i,j);
                        secondIterator = secondIterator->next;
                        continue;
                    }
                    addUndirectedUnweightedEdge(reachables_graph, i+1, j+1);
                }
                if(ikNode->shortestPath_distance ==INT_MAX || kjNode->shortestPath_distance ==INT_MAX){printf("ERROR,ERROR, k = %d, i = %d, j = %d",k,i,j);exit(0);}
                if (ikNode->shortestPath_distance + kjNode->shortestPath_distance< ijNode->shortestPath_distance){
                    ijNode->shortestPath_distance = ikNode->shortestPath_distance + kjNode->shortestPath_distance;
                    ijNode->num_shortest_paths = ikNode->num_shortest_paths * kjNode->num_shortest_paths;
                } else if (ikNode->shortestPath_distance + kjNode->shortestPath_distance == ijNode->shortestPath_distance){
                    ijNode->num_shortest_paths+=ikNode->num_shortest_paths*kjNode->num_shortest_paths;

                }
                secondIterator = secondIterator->next;
            }
            firstIterator = firstIterator->next;
        }
    }

    return outnodesArray;
}



nodesArray* floydWarshall2(graph* input){
    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    initializeNodesArraywGraph(outnodesArray,input);
    graph* reachables_graph = copyGraph(input);
    printGraph(reachables_graph);
    printNodesArray(outnodesArray);

    /*
         * instead of looping over i j and k, we'll just loop over list of nodes connected with k.
         * ie we are implementing a double iterator on linked list for speed.
         * Note that I already tried regular matrix implementation & got a bad running time of 20 minutes for 5k nodes.
         * Idea is that in the first loop, we are are looping over i*j elements that are connected to k only. Not over
         * 5k*5k = 2.5m elements, especially in the initial phases of our algorithm. We still use matrix as we need
         * instant access to update the number of shortest paths etc. The list is only to see whats connected. In fully
         * connected situations, it devolves back to Floyd Warshall.
         *
         * Note that we are going to be modifying our graph in the process,
         * to instead list all the connected nodes
         * But this is ok as we have no use for it anyway
         *
*/
    printf("Starting the loops\n");
    for (int interIndex = 0; interIndex < num_vertices; ++interIndex) {
        adjlistNode* firstIterator = reachables_graph->vertexList[interIndex].head;
        printf("k = %d\n",interIndex);
        while(firstIterator){
            printf("\n\n\ni = %d\n\n\n",firstIterator->destination);
            adjlistNode* secondIterator = firstIterator->next;
            while(secondIterator){
                printf("j = %d\t",secondIterator->destination);
                //first and second iterator are connected through the interIndex Node. So check everything.
//                printf("h0");
                int i = firstIterator->destination-1,j=secondIterator->destination-1,k = interIndex;
//                printf("h1");
                //Check to ensure that nodesarray is not hit with equal values
                if(i==j||j==k||k==i){
                    secondIterator = secondIterator->next;
                    continue;
                }
//                printf("h2");
                vvNode* ijNode = &(outnodesArray->vvnodes[arrayIndex(i,j)]);
                vvNode* ikNode = &(outnodesArray->vvnodes[arrayIndex(i,k)]);
                vvNode* kjNode = &(outnodesArray->vvnodes[arrayIndex(k,j)]);
//                printf("h3");

                if(ijNode->shortestPath_distance==INT_MAX){
                    if(i==j){printf("ERROR,ERROR, k = %d, i = %d, j = %d",k,i,j);exit(0);}
                    addUndirectedUnweightedEdge(reachables_graph, i+1, j+1);
                }
                if(ikNode->shortestPath_distance ==INT_MAX || kjNode->shortestPath_distance ==INT_MAX){printf("ERROR,ERROR, k = %d, i = %d, j = %d",k,i,j);exit(0);}
//                printf("h4");
                if (ikNode->shortestPath_distance + kjNode->shortestPath_distance< ijNode->shortestPath_distance){
//                    printf("h5");
                    //First Check Less Distance
                    ijNode->shortestPath_distance = ikNode->shortestPath_distance + kjNode->shortestPath_distance;
                    ijNode->num_shortest_paths = ikNode->num_shortest_paths * kjNode->num_shortest_paths;
//                    printf("h51");
//                    free_shortestPathsNodesList(ijNode->previous_hop);
//                    printf("h52");
//                    //Add list of nodes on prev hop on kj side to ij side
//                    prevHopNode* sourceHopList = kjNode->previous_hop;
//                    if(!sourceHopList){
//                        secondIterator = secondIterator->next;
//                        continue;
//                    }
//                    printf("h53");
//                    while(sourceHopList){
//                        printf("h54");
//                        unsigned short node_no_to_add = sourceHopList->node_no;
//                        prevHopNode* nodetoAdd;
//                        printf("h55");
//                        if(!ijNode->previous_hop){
//                            nodetoAdd = create_PrevHopNode(node_no_to_add);
//                        } else {
//                            nodetoAdd = create_PrevHopNode(node_no_to_add);
//                            nodetoAdd->next = ijNode->previous_hop;
//                        }
//                        printf("h56");
//                        ijNode->previous_hop = nodetoAdd;
//                        printf("h57");
//                        sourceHopList = sourceHopList->next;
//                    }

                    //updateSPMatrix(nodesMatrix, i, j, k, ik_dist, kj_dist);
                } else if (ikNode->shortestPath_distance + kjNode->shortestPath_distance == ijNode->shortestPath_distance){
//                    printf("h6");
                    //Then Check Distance Equality
                    ijNode->num_shortest_paths+=ikNode->num_shortest_paths*kjNode->num_shortest_paths;
//                    printf("h61");
//                    prevHopNode* sourceNode = kjNode->previous_hop;
//                    printf("h62");
//                    while(sourceNode){
//                        printf("h63");
//                        unsigned short node_no_to_add = sourceNode->node_no;
//                        printf("h64");
//                        if(!ijNode->previous_hop){
//                            ijNode->previous_hop = create_PrevHopNode(node_no_to_add);
//                            sourceNode = sourceNode->next;
//                            continue;
//                        }
//                        printf("h65");
//                        int node_exists_flag = find_in_previous_hops_list(ijNode->previous_hop, node_no_to_add);
//                        printf("h67");
//                        if(!node_exists_flag){
//                            printf("h68");
//                            prevHopNode* newnode = create_PrevHopNode(node_no_to_add);
//                            printf("h69");
//                            newnode->next = ijNode->previous_hop;
//                            ijNode->previous_hop = newnode;
//                        }
//                        printf("h691");
//                        sourceNode = sourceNode->next;
//                    }

                }
//                printf("h9");
                secondIterator = secondIterator->next;
            }
            firstIterator = firstIterator->next;
        }
    }

    return outnodesArray;
}



nodesArray* floydWarshall2(graph* input){
    int num_vertices = input->num_vertices;
    nodesArray* outnodesArray = initialize_nodesArray(num_vertices);
    initializeNodesArraywGraph(outnodesArray,input);
    graph* reachables_graph = copyGraph(input);
    printGraph(reachables_graph);
    printNodesArray(outnodesArray);

    /*
         * instead of looping over i j and k, we'll just loop over list of nodes connected with k.
         * ie we are implementing a double iterator on linked list for speed.
         * Note that I already tried regular matrix implementation & got a bad running time of 20 minutes for 5k nodes.
         * Idea is that in the first loop, we are are looping over i*j elements that are connected to k only. Not over
         * 5k*5k = 2.5m elements, especially in the initial phases of our algorithm. We still use matrix as we need
         * instant access to update the number of shortest paths etc. The list is only to see whats connected. In fully
         * connected situations, it devolves back to Floyd Warshall.
         *
         * Note that we are going to be modifying our graph in the process,
         * to instead list all the connected nodes
         * But this is ok as we have no use for it anyway
         *
*/
    printf("Starting the loops\n");
    for (int interIndex = 0; interIndex < num_vertices; ++interIndex) {
        adjlistNode* firstIterator = reachables_graph->vertexList[interIndex].head;
        printf("k = %d\n",interIndex);
        while(firstIterator){
            printf("\n\n\ni = %d\n\n\n",firstIterator->destination);
            adjlistNode* secondIterator = firstIterator->next;
            while(secondIterator){
                printf("j = %d\t",secondIterator->destination);
                //first and second iterator are connected through the interIndex Node. So check everything.
//                printf("h0");
                int i = firstIterator->destination-1,j=secondIterator->destination-1,k = interIndex;
//                printf("h1");
                //Check to ensure that nodesarray is not hit with equal values
                if(i==j||j==k||k==i){
                    secondIterator = secondIterator->next;
                    continue;
                }
//                printf("h2");
                vvNode* ijNode = &(outnodesArray->vvnodes[arrayIndex(i,j)]);
                vvNode* ikNode = &(outnodesArray->vvnodes[arrayIndex(i,k)]);
                vvNode* kjNode = &(outnodesArray->vvnodes[arrayIndex(k,j)]);
//                printf("h3");

                if(ijNode->shortestPath_distance==INT_MAX){
                    if(i==j){printf("ERROR,ERROR, k = %d, i = %d, j = %d",k,i,j);exit(0);}
                    addUndirectedUnweightedEdge(reachables_graph, i+1, j+1);
                }
                if(ikNode->shortestPath_distance ==INT_MAX || kjNode->shortestPath_distance ==INT_MAX){printf("ERROR,ERROR, k = %d, i = %d, j = %d",k,i,j);exit(0);}
//                printf("h4");
                if (ikNode->shortestPath_distance + kjNode->shortestPath_distance< ijNode->shortestPath_distance){
//                    printf("h5");
                    //First Check Less Distance
                    ijNode->shortestPath_distance = ikNode->shortestPath_distance + kjNode->shortestPath_distance;
                    ijNode->num_shortest_paths = ikNode->num_shortest_paths * kjNode->num_shortest_paths;
//                    printf("h51");
//                    free_shortestPathsNodesList(ijNode->previous_hop);
//                    printf("h52");
//                    //Add list of nodes on prev hop on kj side to ij side
//                    prevHopNode* sourceHopList = kjNode->previous_hop;
//                    if(!sourceHopList){
//                        secondIterator = secondIterator->next;
//                        continue;
//                    }
//                    printf("h53");
//                    while(sourceHopList){
//                        printf("h54");
//                        unsigned short node_no_to_add = sourceHopList->node_no;
//                        prevHopNode* nodetoAdd;
//                        printf("h55");
//                        if(!ijNode->previous_hop){
//                            nodetoAdd = create_PrevHopNode(node_no_to_add);
//                        } else {
//                            nodetoAdd = create_PrevHopNode(node_no_to_add);
//                            nodetoAdd->next = ijNode->previous_hop;
//                        }
//                        printf("h56");
//                        ijNode->previous_hop = nodetoAdd;
//                        printf("h57");
//                        sourceHopList = sourceHopList->next;
//                    }

                    //updateSPMatrix(nodesMatrix, i, j, k, ik_dist, kj_dist);
                } else if (ikNode->shortestPath_distance + kjNode->shortestPath_distance == ijNode->shortestPath_distance){
//                    printf("h6");
                    //Then Check Distance Equality
                    ijNode->num_shortest_paths+=ikNode->num_shortest_paths*kjNode->num_shortest_paths;
//                    printf("h61");
//                    prevHopNode* sourceNode = kjNode->previous_hop;
//                    printf("h62");
//                    while(sourceNode){
//                        printf("h63");
//                        unsigned short node_no_to_add = sourceNode->node_no;
//                        printf("h64");
//                        if(!ijNode->previous_hop){
//                            ijNode->previous_hop = create_PrevHopNode(node_no_to_add);
//                            sourceNode = sourceNode->next;
//                            continue;
//                        }
//                        printf("h65");
//                        int node_exists_flag = find_in_previous_hops_list(ijNode->previous_hop, node_no_to_add);
//                        printf("h67");
//                        if(!node_exists_flag){
//                            printf("h68");
//                            prevHopNode* newnode = create_PrevHopNode(node_no_to_add);
//                            printf("h69");
//                            newnode->next = ijNode->previous_hop;
//                            ijNode->previous_hop = newnode;
//                        }
//                        printf("h691");
//                        sourceNode = sourceNode->next;
//                    }

                }
//                printf("h9");
                secondIterator = secondIterator->next;
            }
            firstIterator = firstIterator->next;
        }
    }

    return outnodesArray;
}


int find_in_previous_hops_list2(prevHopNode* list_node, unsigned short num_to_find){
    //1 means found, 0 means not found
    if(!list_node){
        return 0;
    }
    while (list_node){
        if(list_node->node_no==num_to_find){return 1;}
        list_node = list_node->next;
    }
    return 0;
}
void free_shortestPathsNodesList2(prevHopNode* head) {
    printf("f1");
    prevHopNode* tmp;
    printf("f2");
    while (head != NULL){
        printf("f3");
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
void printNodesArray2(nodesArray* nodesarray){
    printf("\nPrinting Matrix with %d vertices\n",nodesarray->number_of_vertices);
    int num_vertices = nodesarray->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        //printf("\n-------------Source Vertex No: %d-------------\n",i+1);
        for (int j = 0; j < num_vertices; ++j) {
            if(i==j){printf("%d, %d, %d, %d\n", i+1,j+1,0,0);continue;}
            printf("%d, %d, %d, %d",
                   i+1,j+1, nodesarray->vvnodes[arrayIndex(i,j)].shortestPath_distance,
                   nodesarray->vvnodes[arrayIndex(i,j)].num_shortest_paths);
            prevHopNode* prevHopNodeRover = nodesarray->vvnodes[arrayIndex(i,j)].previous_hop;
            while(prevHopNodeRover){
                printf(", %d", prevHopNodeRover->node_no);
                prevHopNodeRover = prevHopNodeRover->next;
            }


            printf("\n");
        }
        printf("\n");
    }
}

void initializeNodesArraywGraph(nodesArray* nodesarray, graph* input_graph){
    int num_vertices = input_graph->num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        int destination, source = i+1;
        adjlistNode* adjlistRover = input_graph->vertexList[i].head;
        while (adjlistRover){
            destination = adjlistRover->destination;
            if(source==destination){
                adjlistRover = adjlistRover->next;
                continue;
            }
            printf("REACHED HERE DURING INITIALIZATION, i = %d, j = %d\n",source,destination);
            vvNode* currentNode = &(nodesarray->vvnodes[arrayIndex(source-1,destination-1)]);
            currentNode->num_shortest_paths =1;
            currentNode->shortestPath_distance =1;
            printf("nodesarray->vvnodes[arrayIndex(source,destination)].shortestPath_distance = %d\n",nodesarray->vvnodes[arrayIndex(source-1,destination-1)].shortestPath_distance);
            printf("nodesarray->vvnodes[arrayIndex(source,destination)].num_shortest_paths = %d\n",nodesarray->vvnodes[arrayIndex(source-1,destination-1)].num_shortest_paths);
            adjlistRover = adjlistRover->next;
        }
    }

}

void free_nodesArray(nodesArray* arraytoFree){
    int num_elements = arraytoFree->num_elements;
    for (int i = 0; i < num_elements; ++i) {
        free_shortestPathsNodesList(arraytoFree->vvnodes[i].previous_hop);
    }
    free(arraytoFree->vvnodes);
    free(arraytoFree);
}
