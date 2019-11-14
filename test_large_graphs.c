#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "FloydWarshall.h"
#include "BFS.h"
#include "BetweennessCentrality.h"
#include "RandomGraph.h"

int main(void) {
    printf("\n-------------------------------------------------------------------------------------------------"
           "\nTESTING BOTH BFS AND FW METHODS on GRAPHS OF SIZES:100, 200, 500, 1000, 2000, 5000, 10000, 20000"
           "\n-------------------------------------------------------------------------------------------------\n");
    processedGraph* pg;
    float* betweenness_array;
    clock_t t;
    double time_taken;
    float prob;
    graph* randomGraph;

    int graph_sizes[] = {100, 200, 500, 1000, 2000}; //in case you are testing, 5k FW, 10k and 20k will lead to long waiting time.
    //int graph_sizes[] = {100, 200, 500, 1000, 2000, 5000,10000,20000};
    for (int i = 0; i < sizeof(graph_sizes) / sizeof(int); ++i) {
        int graph_size = graph_sizes[i];


        t = clock();
        prob = log(graph_size) / graph_size;
        printf("\n------------------\nDOING TESTS ON RANDOM GRAPHS OF SIZE %d, with %f%% PROBABILITY OF EDGE\n------------------\n",graph_sizes[i],prob*100);
        randomGraph = random_connected_graph_generator(graph_size, prob);
        double time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Finished generating graph. Time Taken : %f\n", time_taken);


        t = clock();

        printf("Going to run floydWarshall on graph of %d nodes\n",graph_size);
        pg = processGraphFWLowMem(randomGraph);

        time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Finished Floyd Warshall on %d nodes. Time Taken : %f\n", graph_size, time_taken);


        t = clock();

        printf("Betweenness Centrality Values from FLoyd Warshall Method\n");
        betweenness_array = betweenness_centralityLowMem(pg);
        print_betweenness(betweenness_array, graph_size);

        time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Finished Betweenness Centrality on %d nodes. Time Taken : %f", graph_size, time_taken);

        freeProcessedGraphwithoutGraph(pg);

        free(betweenness_array);

        t = clock();

        printf("Going to run BFS on graph of size %d\n",graph_size);
        pg = processGraphBFS(randomGraph);

        time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Finished BFS to find nodes array on %d nodes. Time Taken : %f\n", graph_size, time_taken);


        t = clock();

        printf("Betweenness Centrality Values from BFS Method\n");
        betweenness_array = betweenness_centrality(pg);
        print_betweenness(betweenness_array, graph_size);

        time_taken = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Finished Betweenness Centrality on %d nodes. Time Taken : %f", graph_size, time_taken);

        freeProcessedGraph(pg);
        free(betweenness_array);
    }
}
