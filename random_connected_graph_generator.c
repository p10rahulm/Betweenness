#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "RandomGraph.h"

float rand01() {
    float random = (float) rand() / RAND_MAX;
    return random;
}

int randbetween(int lo, int hi) {
    //inclusive of high and lo
    int random = rand() % (hi - lo + 1) + lo;
    return random;
}

/* generate a random value weighted within the normal (gaussian) distribution */
float std_gaussian() {
    float x = rand01();
    float y = rand01();
    //Box Muller Transform
    float z = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
    return z;
}


float gaussian(float mean, float variance) {
    return std_gaussian() * sqrtf(variance) + mean;
}

float lognormal(float mean, float variance) {
    return exp(
            log(mean / sqrt(1 + variance / (mean * mean))) + sqrt(log(1 + variance / (mean * mean))) * std_gaussian());
}

int lognormal_int(float mean, float variance) {
    float lognormal_random = exp(
            log(mean / sqrt(1 + variance / (mean * mean))) + sqrt(log(1 + variance / (mean * mean))) * std_gaussian());
    int floored_random = (int) ceil(lognormal_random);
    return floored_random;
}

/* Method:
 *
 * 1. Generate a random Graph of required number of nodes
 * 2. Find the connected components (and importantly disconnected components)
 * 3. Connect the disconnected components to main graph randomly
 * 4. Find the bridge edges in graph
 * 4. Remove those many number of non-bridge edges as number of edges added in step 3
 *
 * You end up with graph with:
 * a) exact number of nodes
 * b) exact probability of edges as needed
 *
 *
*/


graph *generate_random_graph(unsigned short num_vertices, float probability_of_edge, float mean, float variance) {
    graph *randomGraph = createEmptyGraph(num_vertices);
    //seeding random generator
    srand(time(0));
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = i + 1; j < num_vertices; ++j) {

            if (i != j && rand01() < probability_of_edge) {
                addUndirectedEdge(randomGraph, i + 1, j + 1, lognormal_int(mean, variance));
            }
        }
    }
    return randomGraph;
}

graph *generate_unweighted_random_graph(unsigned short num_vertices, float probability_of_edge) {
    graph *randomGraph = createEmptyGraph(num_vertices);
    //seeding random generator
    srand(time(0));
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = i + 1; j < num_vertices; ++j) {

            if (i != j && rand01() < probability_of_edge) {
                addUndirectedEdge(randomGraph, i + 1, j + 1, 1);
            }
        }
    }
    return randomGraph;
}

void DFS_recursive(const graph *input_graph, unsigned short sourceIndex, int *components_array, int num_vertices,
                   char *nodeVisitedfromS, unsigned short recursorIndex) {
    if (recursorIndex >= num_vertices) {
        printf("Calling DFS with input node greater than number of vertices");
        return;
    }
    components_array[recursorIndex] = sourceIndex;
    nodeVisitedfromS[recursorIndex] = 1;
    adjlistNode *listRover = input_graph->vertexList[recursorIndex].head;
    while (listRover) {
        unsigned short destinationNodeIndex = listRover->destination - 1;
        if (!nodeVisitedfromS[destinationNodeIndex]) {
            DFS_recursive(input_graph, sourceIndex, components_array, num_vertices, nodeVisitedfromS,
                          destinationNodeIndex);
        }
        listRover = listRover->next;
    }
}

// DFS traversal of the vertices reachable from v. It uses recursive DFS_recursive()
void DFS(const graph *input_graph, unsigned short sourceIndex, int *components_array, int num_vertices) {
    // Mark all the vertices as not visited
    char *nodeVisitedfromS = (char *) malloc(num_vertices * sizeof(char));
    for (int i = 0; i < num_vertices; i++) { nodeVisitedfromS[i] = 0; }
    DFS_recursive(input_graph, sourceIndex, components_array, num_vertices, nodeVisitedfromS, sourceIndex);
    free(nodeVisitedfromS);
}

int *connected_components(const graph *input_graph) {
    unsigned short num_vertices = input_graph->num_vertices;
    int *components = (int *) malloc(num_vertices * sizeof(int));
    for (int i = 0; i < num_vertices; ++i) {
        components[i] = i;
    }
    for (int i = 0; i < num_vertices; ++i) {
        if (components[i] < i) { continue; }
        DFS(input_graph, i, components, num_vertices);
    }
    return components;
}

void print_connected_components(int *components, int num_vertices) {
    printf("\n---------------------------\nPrinting Connected Components of graph\n---------------------------\nVertex No\tComponentNo\n");
    for (int i = 0; i < num_vertices; ++i) {
        printf("%d\t%d\n", i + 1, components[i] + 1);
    }
    printf("\n");
}

int check_connected(int* connected_components,int num_elements){
    for (int i = 1; i < num_elements; ++i) {
        if(connected_components[i-1]!=connected_components[i]){
            return 0;
        }
    }
    return 1;
}

int *join_components(graph *randomgraph, int *connectedComponentsArray) {
    int num_vertices = randomgraph->num_vertices;
    int num_components = 0;
    for (int i = 0; i < num_vertices; ++i) {
        if (connectedComponentsArray[i] == i) {
            num_components++;
        }
    }
    int* connected_comps=connectedComponentsArray;

    srand(time(0));
    int randomLowerIndex = 0;
    while(!check_connected(connected_comps,num_vertices)){
        for (int i = 1, j = 1; i < num_vertices && j < num_components; ++i) {
            if (connectedComponentsArray[i] == i) {
                randomLowerIndex = randbetween(1, i);
                addUndirectedEdge(randomgraph, randomLowerIndex, i + 1, 1);
                j++;
            }
        }
        free(connected_comps);
        connected_comps = connected_components(randomgraph);
    }

    return (connected_comps);
}



graph *random_connected_graph_generator(unsigned short num_vertices, float probability_of_edge) {
    graph *randomGraph = generate_unweighted_random_graph(num_vertices, probability_of_edge);
    int *components_RG = connected_components(randomGraph);
    components_RG = join_components(randomGraph, components_RG);
    free(components_RG);
    return randomGraph;
}
