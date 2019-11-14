#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BFS.h"
#include "FloydWarshall.h"
#include "BetweennessCentrality.h"

int main() {
    {
        clock_t t = clock();
        printf("\n--------------------------------------------------------------------"
               "\nTESTING BFS METHOD FOR PROCESSING GRAPHS FOR BETWEENNESS CENTRALITY"
               "\n--------------------------------------------------------------------");
        printf("We Will Compare Results from 1) FW Method and 2) BFS Method\n");
        //int num_nodes = 7;
        int num_nodes = 327;
        graph *Graph = build_unweighted_graph("data/contact-high-school-proj-graph.txt", num_nodes);
        printUnweightedGraph(Graph);
        processedGraph* pg = processGraphFWLowMem(Graph);
        printProcessedGraph(pg);
        float *betweenness_array = betweenness_centralityLowMem(pg);
        printf("Betweenness Centrality Values from FLoyd Warshall Method\n");
        print_betweenness(betweenness_array, num_nodes);
        double time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time Taken : %f\n", time_taken);
        freeProcessedGraph(pg);
        free(betweenness_array);
    }
    {
        clock_t t = clock();
        printf("Started Betweenness Centrality BFS");
        //int num_nodes = 7;
        int num_nodes = 327;
        graph *Graph = build_unweighted_graph("data/contact-high-school-proj-graph.txt", num_nodes);
        processedGraph* pg = processGraphBFS(Graph);
        printProcessedGraph(pg);
        float *betweenness_array = betweenness_centrality(pg);
        printf("Betweenness Centrality Values from BFS Method\n");
        print_betweenness(betweenness_array, num_nodes);
        double time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time Taken : %f\n", time_taken);
        freeProcessedGraph(pg);
        free(betweenness_array);
    }

}
