#include <stdio.h>
#include <stdlib.h>
#include "FloydWarshall.h"
#include "BFS.h"
#include "BetweennessCentrality.h"
#include <time.h>

int main() {
    printf("Please enter the full path of the file with the graph\n"
           "Each row in the file should contain edges in the format\n"
           "from_vertex to_vertex edge_weight\n\n"
           "Please note that the current implementation of the function ignores edge weights\n");

    char filename[100]="";
    scanf("%s",filename);
    int num_nodes;
    printf("Please enter the number of nodes in the graph as an integer\n");
    scanf("%d",&num_nodes);

    {
        clock_t t = clock();
        printf("Started Betweenness Centrality through the Floyd Warshall Method\n"
               "----------------------------------------------------------------\n");



        graph *Graph = build_unweighted_graph(filename, num_nodes);
        printUnweightedGraph(Graph);
        processedGraph* pg = processGraphFWLowMem(Graph);
        printProcessedGraph(pg);
        printf("Betweenness Centrality Values from FLoyd Warshall Method\n");
        float* betweenness_array = betweenness_centralityLowMem(pg);
        print_betweenness(betweenness_array, num_nodes);

        double time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time Taken : %f\n", time_taken);
        freeProcessedGraph(pg);
        free(betweenness_array);
    }
    {
        clock_t t = clock();
        printf("Started Betweenness Centrality BFS");
        int num_nodes = 7;
        graph *Graph = build_unweighted_graph(filename, num_nodes);
        processedGraph* pg = processGraphBFS(Graph);
        printProcessedGraph(pg);

        printf("Betweenness Centrality Values from BFS by Method 2\n");
        float* betweenness_array = betweenness_centrality(pg);
        print_betweenness(betweenness_array, num_nodes);

        double time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time Taken : %f\n", time_taken);
        freeProcessedGraph(pg);
        free(betweenness_array);
   }

}
