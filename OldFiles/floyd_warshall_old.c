#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "../common_header.h"

//Source and destination need not be stored as we will
// just be using the matrix indices as the source and destination indices


double time_spent_on_initialize_nodesMatrix=0,time_spent_on_free_nodesMatrix=0,time_spent_on_create_PrevHopNode=0,
        time_spent_on_initializeNodesMatrixwGraph=0,time_spent_on_free_shortestPathsNodesList=0,
        time_spent_on_find_in_previous_hops_list=0,time_spent_on_updateSPMatrix=0,
        time_spent_on_updateSPMatrixEquality=0,time_spent_on_floydWarshall=0;
//time_spent_on_initialize_nodesMatrix=0.0;time_spent_on_free_nodesMatrix=0.0;time_spent_on_create_PrevHopNode=0.0;
//        time_spent_on_initializeNodesMatrixwGraph=0.0;time_spent_on_free_shortestPathsNodesList=0.0;
//        time_spent_on_find_in_previous_hops_list=0.0;time_spent_on_updateSPMatrix=0.0;
//        time_spent_on_updateSPMatrixEquality=0.0;time_spent_on_floydWarshall=0.0;

nodesMatrix* initialize_nodesMatrix(int num_vertices){
    clock_t begin = clock();

    nodesMatrix* output = malloc(sizeof(nodesMatrix));
    output->number_of_vertices = num_vertices;
    output->matrix = malloc(num_vertices* sizeof(vvNode*));
    for (int i = 0; i < num_vertices; i++) {
        output->matrix[i] = malloc(num_vertices* sizeof(vvNode));
    }
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            output->matrix[i][j].num_shortest_paths=0;
            if(i==j){
                output->matrix[i][j].shortestPath_distance=0;
            } else {
                //flag for infinity
                output->matrix[i][j].shortestPath_distance=INT_MAX;
            }
            output->matrix[i][j].previous_hop=NULL;
        }
    }

    clock_t end = clock();
    time_spent_on_initialize_nodesMatrix += (double)(end - begin) / CLOCKS_PER_SEC;
    return output;
}
void free_nodesMatrix(nodesMatrix* input){
    clock_t begin = clock();

    for (int i = 0; i < input->number_of_vertices; i++) {
        free(input->matrix[i]);
    }
    free(input->matrix);
    free(input);

    clock_t end = clock();
    time_spent_on_free_nodesMatrix+= (double)(end - begin) / CLOCKS_PER_SEC;

}

prevHopNode* create_PrevHopNode(unsigned short prevHopNodeNo,prevHopNode* next_pointer){
    clock_t begin = clock();


    prevHopNode* output = malloc(sizeof(prevHopNode));
    output->node_no = prevHopNodeNo;
    output->next = next_pointer;

    clock_t end = clock();
    time_spent_on_create_PrevHopNode+= (double)(end - begin) / CLOCKS_PER_SEC;


    return output;

}

void initializeNodesMatrixwGraph(nodesMatrix* matrix, graph* input_graph){
    clock_t begin = clock();

    int num_vertices = input_graph->num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        int destination, weight,source = input_graph->vertexList[i].source;
        adjlistNode* adjlistRover = NULL;
        if(input_graph->vertexList[i].head){
            adjlistRover = input_graph->vertexList[i].head;
        } else {continue;}
        while (adjlistRover){
            destination = adjlistRover->destination;
            weight = adjlistRover->weight;
            matrix->matrix[source-1][destination-1].num_shortest_paths = 1;
            matrix->matrix[source-1][destination-1].shortestPath_distance = weight;
            matrix->matrix[source-1][destination-1].previous_hop = create_PrevHopNode(source,NULL);
            adjlistRover = adjlistRover->next;
        }
    }

    clock_t end = clock();
    time_spent_on_initializeNodesMatrixwGraph+= (double)(end - begin) / CLOCKS_PER_SEC;


}


void printNodesMatrix_detailed(nodesMatrix* matrix){
    printf("\nPrinting Matrix with %d vertices\n",matrix->number_of_vertices);
    int num_vertices = matrix->number_of_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        printf("\n-------------Source Vertex No: %d-------------\n",i+1);
        for (int j = 0; j < num_vertices; ++j) {
            printf("(source = %d, destination = %d, shortest path distance = %d, "
                   "number of shortest paths = %d",
                   i+1,j+1,matrix->matrix[i][j].shortestPath_distance,
                   matrix->matrix[i][j].num_shortest_paths);
            prevHopNode* prevHopNodeRover;
            if(matrix->matrix[i][j].previous_hop){
                prevHopNodeRover = matrix->matrix[i][j].previous_hop;
                int num_short_path = 1;
                while(prevHopNodeRover){
                    printf(", last hop on path %d = %d",num_short_path, prevHopNodeRover->node_no);
                    prevHopNodeRover = prevHopNodeRover->next;
                    num_short_path++;
                }
            }

            printf(")\n");
        }
        printf("\n");
    }
}
void free_shortestPathsNodesList(prevHopNode* subGraphNode){

    clock_t begin = clock();

    prevHopNode* current = subGraphNode;
    prevHopNode* next;
    if(current){
        next = current->next;
    }

    while(current){
        free(current);
        current = next;
        if(current){
            next = current->next;
        } else{ continue;}
    }

    clock_t end = clock();
    time_spent_on_free_shortestPathsNodesList+= (double)(end - begin) / CLOCKS_PER_SEC;


}
int find_in_previous_hops_list(prevHopNode* list_node, unsigned short num_to_find){
    clock_t begin = clock();
    //1 means found, 0 means not found
    if(!list_node){
        clock_t end = clock();
        time_spent_on_find_in_previous_hops_list+= (double)(end - begin) / CLOCKS_PER_SEC;

        return 0;
    }
    while (list_node){
        if(list_node->node_no==num_to_find){
            clock_t end = clock();
            time_spent_on_find_in_previous_hops_list+= (double)(end - begin) / CLOCKS_PER_SEC;


            return 1;
        }
        list_node = list_node->next;
    }
    clock_t end = clock();
    time_spent_on_find_in_previous_hops_list+= (double)(end - begin) / CLOCKS_PER_SEC;


    return 0;
}


void updateSPMatrix(nodesMatrix* nodesMatrix, unsigned short sourceIndex, unsigned short destinationIndex,
        unsigned short interIndex, int sourceInterDistance, int interDestDistance){
    clock_t begin = clock();

    int sourceInterNumSPs = nodesMatrix->matrix[sourceIndex][interIndex].num_shortest_paths;
    int interDestNumSPs = nodesMatrix->matrix[interIndex][destinationIndex].num_shortest_paths;
    nodesMatrix->matrix[sourceIndex][destinationIndex].shortestPath_distance = sourceInterDistance + interDestDistance;
    nodesMatrix->matrix[sourceIndex][destinationIndex].num_shortest_paths=sourceInterNumSPs*interDestNumSPs;
    free_shortestPathsNodesList(nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop);
    //nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop = create_PrevHopNode(nodesMatrix->matrix[interIndex][destinationIndex].previous_hop->node_no,NULL);
    prevHopNode* sourceNode = nodesMatrix->matrix[interIndex][destinationIndex].previous_hop;
    if(!sourceNode){
        clock_t end = clock();
        time_spent_on_updateSPMatrix+= (double)(end - begin) / CLOCKS_PER_SEC;

        return;
    }
    while(sourceNode){
        unsigned short node_no_to_add = sourceNode->node_no;
        prevHopNode* nodetoAdd;
        if(!nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop){
            nodetoAdd = create_PrevHopNode(node_no_to_add,NULL);
        } else {
            nodetoAdd = create_PrevHopNode(node_no_to_add,nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop);
        }
        nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop = nodetoAdd;
        sourceNode = sourceNode->next;
    }

    clock_t end = clock();
    time_spent_on_updateSPMatrix+= (double)(end - begin) / CLOCKS_PER_SEC;



}
void printsubGraphNodeList(prevHopNode* start_of_list){
    if(!start_of_list){
        printf("You have provided an empty list\n");
        return;
    }
    while (start_of_list){
        printf("%d-->",start_of_list->node_no);
        start_of_list = start_of_list->next;
    }
    printf("\n");

}
void updateSPMatrixEquality(nodesMatrix* nodesMatrix, unsigned short sourceIndex, unsigned short destinationIndex,
                            unsigned short interIndex, int sourceInterDistance, int interDestDistance){
    clock_t begin = clock();

    int sourceInterNumSPs = nodesMatrix->matrix[sourceIndex][interIndex].num_shortest_paths;
    int interDestNumSPs = nodesMatrix->matrix[interIndex][destinationIndex].num_shortest_paths;
    nodesMatrix->matrix[sourceIndex][destinationIndex].num_shortest_paths+=sourceInterNumSPs*interDestNumSPs;



    prevHopNode* sourceNode = nodesMatrix->matrix[interIndex][destinationIndex].previous_hop;

    while(sourceNode){
        unsigned short node_no_to_add = sourceNode->node_no;
        if(!nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop){
            nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop = create_PrevHopNode(node_no_to_add,NULL);
            sourceNode = sourceNode->next;
            continue;
        }
        int node_exists_flag = find_in_previous_hops_list(nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop, node_no_to_add);
        if(!node_exists_flag){
            prevHopNode* nodetoAdd = create_PrevHopNode(node_no_to_add,nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop);
            nodesMatrix->matrix[sourceIndex][destinationIndex].previous_hop = nodetoAdd;
        }
        sourceNode = sourceNode->next;
    }
    clock_t end = clock();
    time_spent_on_updateSPMatrixEquality+= (double)(end - begin) / CLOCKS_PER_SEC;

}

nodesMatrix* floydWarshall (graph* input){
    clock_t begin = clock();
    int num_vertices = input->num_vertices;
    nodesMatrix* nodesMatrix = initialize_nodesMatrix(num_vertices);
    initializeNodesMatrixwGraph(nodesMatrix,input);

    // Pick all the intermediate nodes
    for (int k = 0; k < num_vertices; k++){
        for (int i = 0; i < num_vertices; i++){
            for (int j = 0; j < num_vertices; j++){
                if(i == j || k == j || i == k){ continue;}
                int ij_dist = nodesMatrix->matrix[i][j].shortestPath_distance;
                int ik_dist = nodesMatrix->matrix[i][k].shortestPath_distance;
                int kj_dist = nodesMatrix->matrix[k][j].shortestPath_distance;
                if(kj_dist == INT_MAX || ik_dist == INT_MAX){ continue;}
                if(kj_dist + ik_dist < 0 ){ continue;} // Checking for overflow
                if (ik_dist + kj_dist < ij_dist){
                    updateSPMatrix(nodesMatrix, i, j, k, ik_dist, kj_dist);
                } else if (ik_dist + kj_dist == ij_dist){
                    updateSPMatrixEquality(nodesMatrix,i,j,k,ik_dist,kj_dist);
                }
            }
        }
    }
    clock_t end = clock();
    time_spent_on_floydWarshall+= (double)(end - begin) / CLOCKS_PER_SEC;



    printf("Time Spent on time_spent_on_initialize_nodesMatrix : %f\n",time_spent_on_initialize_nodesMatrix);
    printf("Time Spent on time_spent_on_free_nodesMatrix : %f\n",time_spent_on_free_nodesMatrix);
    printf("Time Spent on time_spent_on_create_PrevHopNode : %f\n",time_spent_on_create_PrevHopNode);
    printf("Time Spent on time_spent_on_initializeNodesMatrixwGraph : %f\n",time_spent_on_initializeNodesMatrixwGraph);
    printf("Time Spent on time_spent_on_free_shortestPathsNodesList : %f\n",time_spent_on_free_shortestPathsNodesList);
    printf("Time Spent on time_spent_on_find_in_previous_hops_list : %f\n",time_spent_on_find_in_previous_hops_list);
    printf("Time Spent on time_spent_on_updateSPMatrix : %f\n",time_spent_on_updateSPMatrix);
    printf("Time Spent on time_spent_on_updateSPMatrixEquality : %f\n",time_spent_on_updateSPMatrixEquality);
    printf("Time Spent on time_spent_on_floydWarshall : %f\n",time_spent_on_floydWarshall);
    printf("Time Spent on FloydWarshall : %f\n",time_spent_on_floydWarshall);

    return nodesMatrix;
}


