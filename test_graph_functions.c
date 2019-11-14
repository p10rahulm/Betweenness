#include <stdio.h>
#include <stdlib.h>
#include "GraphFunctions.h"

// Driver program to test graph functions
int main(){
    printf("\n---------------------------------------------------"
           "\nTESTING GRAPH FUNCTIONS FOR GENERATING SMALL GRAPHS"
           "\n---------------------------------------------------\n");
    // create the graph given in above fugure
    int num_vertices = 5;
    graph* grapher = createEmptyGraph(num_vertices);
    printUnweightedGraph(grapher);
    addUndirectedEdge(grapher, 1, 2, 10);
    addUndirectedEdge(grapher, 1, 5, 10);
    addUndirectedEdge(grapher, 2, 3, 10);
    addUndirectedEdge(grapher, 2, 4, 10);
    addUndirectedEdge(grapher, 2, 5, 10);
    addUndirectedEdge(grapher, 3, 4, 10);
    addUndirectedEdge(grapher, 4, 5, 10);
    // print the adjacency list representation of the above grapher
    printUnweightedGraph(grapher);
    printf("Testing Copying of Graph");

    graph* grapher2 = copyGraph(grapher);

    printUnweightedGraph(grapher2);
    freeGraph(grapher);
    freeGraph(grapher2);

    return 0;
}