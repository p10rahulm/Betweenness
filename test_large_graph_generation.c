#include <stdio.h>
#include <time.h>
#include "RandomGraph.h"

int main(){
    printf("\n-----------------------------------------"
           "\nTESTING GENERATION OF LARGE RANDOM GRAPHS"
           "\n-----------------------------------------\n");
    {
        clock_t t;
        t = clock();
        int i=1000;
        printf("Generating random connected graph of 20pct density and %d nodes\n",i);
        graph* test_graph = random_connected_graph_generator(i,0.2);
        printUnweightedGraph(test_graph);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        printf("Generated Connected Graph of %d Vertices. Time Taken : %f\n",i,time_taken);
        freeGraph(test_graph);
    }
    printf("Testing Large Graph Generation\n");
    for(int i =1000;i<=5000;i+=1000){
        clock_t t;
        t = clock();

        printf("Generating random connected graph of 20pct density and %d nodes\n",i);
        graph* test_graph = random_connected_graph_generator(i,0.2);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        printf("Generated Connected Graph of %d Vertices. Time Taken : %f\n",i,time_taken);
        freeGraph(test_graph);
    }

}