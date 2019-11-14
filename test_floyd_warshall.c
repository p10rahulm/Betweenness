#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "BetweennessCentrality.h"
#include "FloydWarshall.h"
#include "RandomGraph.h"

int main() {


    clock_t t;
    double time_taken_bg, time_taken_pg, time_taken_bcn;
    float *betweenness_array;
    processedGraph *pg;
    float prob;
    graph* Graph;

    printf("\n----------------------------------------------------------------------------"
           "\nTESTING FLOYD WARSHALL METHOD FOR BETWEENNESS CENTRALITY BETWEEN ALL PAIRS"
           "\n----------------------------------------------------------------------------\n");
    t = clock();
    int num_nodes = 327;
    Graph = build_unweighted_graph("data/contact-high-school-proj-graph.txt", num_nodes);
    printUnweightedGraph(Graph);

    time_taken_bg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to build the graph is %f\n", time_taken_bg);

    //METHOD 1: SUGGESTED METHOD OF LOW MEMORY
    printf("\n---------------------------------------------------------------"
           "\nTESTING FLOYD WARSHALL WITHOUT PATHMATRIX WITHOUT REACHABILITY"
           "\n---------------------------------------------------------------");
    t = clock();

    pg = processGraphFWLowMem(Graph);
    printProcessedGraph(pg);

    time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to process graph without pathmatrix and without reachability is %f\n", time_taken_pg);

    t = clock();

    betweenness_array = betweenness_centralityLowMem(pg);
    printf("Betweenness Centrality Values from FLoyd Warshall Method 1: FLOYD WARSHALL WITHOUT PATHMATRIX WITHOUT REACHABILITY\n");
    print_betweenness(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized for an undirected Graph\n-----------------\n");
    print_betweenness_normalized(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized to 1\n-----------------\n");
    print_betweenness_normalizedTo1(betweenness_array, num_nodes);

    time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to compute betweenness centrality without pathmatrix and without reachability is %f\n",
           time_taken_bcn);
    printf("Total time taken to compute betweenness centrality without pathmatrix and without reachability is %f\n",
           time_taken_bg + time_taken_pg + time_taken_bcn);

    freeProcessedGraphwithoutGraph(pg);
    free(betweenness_array);

    //METHOD 2: BUILDING PATHMATRIX
    printf("\n---------------------------------------------------------------"
           "\nTESTING FLOYD WARSHALL BUILDING PATHMATRIX WITHOUT REACHABILITY"
           "\n---------------------------------------------------------------");

    t = clock();

    pg = processGraphFW(Graph);
    printProcessedGraph(pg);
    time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to process graph with pathmatrix and without reachability is %f\n", time_taken_pg);

    t = clock();

    betweenness_array = betweenness_centrality(pg);
    printf("Betweenness Centrality Values from FLoyd Warshall Method 2: FLOYD WARSHALL BUILDING PATHMATRIX WITHOUT REACHABILITY\n");
    print_betweenness(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized for an undirected Graph\n-----------------\n");
    print_betweenness_normalized(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized to 1\n-----------------\n");
    print_betweenness_normalizedTo1(betweenness_array, num_nodes);


    time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to compute betweenness centrality with pathmatrix and without reachability is %f\n",
           time_taken_bcn);
    printf("Total time taken to compute betweenness centrality with pathmatrix and without reachability is %f\n",
           time_taken_bg + time_taken_pg + time_taken_bcn);

    freeProcessedGraphwithoutGraph(pg);
    free(betweenness_array);

    //METHOD 3: NO PATHMATRIX. REACH ONLY NODES THAT CAN BE REACHED
    printf("\n------------------------------------------------------------------"
           "\nTESTING FLOYD WARSHALL WITHOUT PATHMATRIX USING REACHABILITY GRAPH"
           "\n------------------------------------------------------------------");

    t = clock();
    pg = processGraphFWLowMemReachables(Graph);
    printProcessedGraph(pg);

    time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to process graph without pathmatrix and with reachability is %f\n", time_taken_pg);

    t = clock();
    betweenness_array = betweenness_centralityLowMem(pg);
    printf("Betweenness Centrality Values from Floyd Warshall Method 3: FLOYD WARSHALL WITHOUT PATHMATRIX USING REACHABILITY GRAPH\n");
    print_betweenness(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized for an undirected Graph\n-----------------\n");
    print_betweenness_normalized(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized to 1\n-----------------\n");
    print_betweenness_normalizedTo1(betweenness_array, num_nodes);

    time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to compute betweenness centrality without pathmatrix and with reachability is %f\n",
           time_taken_bcn);
    printf("Total time taken to compute betweenness centrality without pathmatrix and with reachability is %f\n",
           time_taken_bg + time_taken_pg + time_taken_bcn);

    freeProcessedGraphwithoutGraph(pg);
    free(betweenness_array);

    //METHOD 4: WITH PATHMATRIX AND REACHABILITY GRAPH
    printf("\n-------------------------------------------------------------------"
           "\nTESTING FLOYD WARSHALL WITH PATHMATRIX AND USING REACHABILITY GRAPH"
           "\n-------------------------------------------------------------------");

    t = clock();
    pg = processGraphFWReachablesPathMatrix(Graph,0.75);
    printProcessedGraph(pg);

    time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to process graph with pathmatrix and with reachability is %f\n", time_taken_pg);

    t = clock();
    betweenness_array = betweenness_centrality(pg);
    printf("Betweenness Centrality Values from Floyd Warshall Method 4: FLOYD WARSHALL WITH PATHMATRIX AND USING REACHABILITY GRAPH\n");
    print_betweenness(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized for an undirected Graph\n-----------------\n");
    print_betweenness_normalized(betweenness_array, num_nodes);
    printf("\n-----------------\nPrinting Betweenness Centrality Values Normalized to 1\n-----------------\n");
    print_betweenness_normalizedTo1(betweenness_array, num_nodes);

    time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
    printf("Time taken to compute betweenness centrality with pathmatrix and with reachability is %f\n",
           time_taken_bcn);
    printf("Total time taken to compute betweenness centrality with pathmatrix and with reachability is %f\n",
           time_taken_bg + time_taken_pg + time_taken_bcn);

    freeProcessedGraph(pg);
    free(betweenness_array);

    //now that we know all are correct, we will check for optimization of which method to use
    int graph_sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    //int graph_sizes[] = {1000};
    //in case you are testing, 10k and 20k will lead to long waiting time, so testing sub 1k
    for (int i = 0; i < sizeof(graph_sizes) / sizeof(int); ++i) {

        int graph_size = graph_sizes[i];
        t = clock();
        prob = log(graph_size) / graph_size;
        printf("\n------------------\nDOING TESTS ON RANDOM GRAPHS OF SIZE %d, with %f%% PROBABILITY OF EDGE\n------------------\n",
               graph_size, prob * 100);
        Graph = random_connected_graph_generator(graph_size, prob);

        time_taken_bg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time taken to build the graph is %f\n", time_taken_bg);

        //METHOD 1: SUGGESTED METHOD OF LOW MEMORY
        t = clock();
        pg = processGraphFWLowMem(Graph);
        time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time taken to process graph without pathmatrix and without reachability is %f\n", time_taken_pg);
        t = clock();
        betweenness_array = betweenness_centralityLowMem(pg);
        time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time taken to compute betweenness centrality without pathmatrix and without reachability is %f\n",
               time_taken_bcn);
        printf("Total time taken to compute betweenness centrality without pathmatrix and without reachability is %f\n",
               time_taken_bg + time_taken_pg + time_taken_bcn);
        freeProcessedGraphwithoutGraph(pg);
        free(betweenness_array);

        //METHOD 2: BUILDING PATHMATRIX
        t = clock();
        pg = processGraphFW(Graph);
        time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time taken to process graph with pathmatrix and without reachability is %f\n", time_taken_pg);
        t = clock();
        betweenness_array = betweenness_centrality(pg);
        time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time taken to compute betweenness centrality with pathmatrix and without reachability is %f\n",
               time_taken_bcn);
        printf("Total time taken to compute betweenness centrality with pathmatrix and without reachability is %f\n",
               time_taken_bg + time_taken_pg + time_taken_bcn);
        freeProcessedGraphwithoutGraph(pg);
        free(betweenness_array);

        //METHOD 3: NO PATHMATRIX. REACH ONLY NODES THAT CAN BE REACHED
        t = clock();
        pg = processGraphFWLowMemReachables(Graph);
        time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time taken to process graph without pathmatrix and with reachability is %f\n", time_taken_pg);
        t = clock();
        betweenness_array = betweenness_centralityLowMem(pg);
        time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
        printf("Time taken to compute betweenness centrality without pathmatrix and with reachability is %f\n",
               time_taken_bcn);
        printf("Total time taken to compute betweenness centrality without pathmatrix and with reachability is %f\n",
               time_taken_bg + time_taken_pg + time_taken_bcn);
        freeProcessedGraphwithoutGraph(pg);
        free(betweenness_array);


        //METHOD 4: WITH PATHMATRIX AND REACHABILITY GRAPH
        for (float j = 0.1; j <= 1; j+=0.1) {
            t = clock();
            pg = processGraphFWReachablesPathMatrix(Graph,0.75);
            time_taken_pg = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
            printf("Time taken to process graph with pathmatrix and with reachability, where heuristic = %f is %f\n", j,time_taken_pg);
            t = clock();
            betweenness_array = betweenness_centrality(pg);
            time_taken_bcn = ((double) (clock() - t)) / CLOCKS_PER_SEC; // in seconds
            printf("Time taken to compute betweenness centrality with pathmatrix and with reachability is %f\n",
                   time_taken_bcn);
            printf("Total time taken to compute betweenness centrality with pathmatrix and with reachability, where heuristic = %f is %f\n",
                   j, time_taken_bg + time_taken_pg + time_taken_bcn);
            freeProcessedGraphwithoutGraph(pg);
            free(betweenness_array);
        }
        freeGraph(Graph);

    }
}