#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "FloydWarshall.h"
#include "BetweennessCentrality.h"

int main() {
    printf("\n----------------------------------------------------------------------------"
           "\nTESTING FLOYD WARSHALL METHOD FOR BETWEENNESS CENTRALITY BETWEEN ALL PAIRS"
           "\n----------------------------------------------------------------------------\n");
    clock_t t = clock();
    printf("Started Betweenness Centrality");
    //int num_nodes = 7;
    int num_nodes = 327;
    graph *Graph = build_unweighted_graph("data/contact-high-school-proj-graph.txt", num_nodes);
    printUnweightedGraph(Graph);

    processedGraph* pg = processGraphFWLowMem(Graph);
    printProcessedGraph(pg);

    float *betweenness_array = betweenness_centralityLowMem(pg);
    printf("Betweenness Centrality Values from FLoyd Warshall Method\n");
    print_betweenness(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized for an undirected Graph\n-----------------\n");
    print_betweenness_normalized(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized to 1\n-----------------\n");
    print_betweenness_normalizedTo1(betweenness_array, num_nodes);
    double time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time Taken : %f\n", time_taken);
    freeProcessedGraph(pg);
    free(betweenness_array);


}