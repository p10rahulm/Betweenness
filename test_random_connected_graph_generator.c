#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "RandomGraph.h"


int main(){
    printf("\n-------------------------------------------------------"
           "\nTESTING INTERNAL FUNCTIONS FOR RANDOM CONNECTED GRAPHS"
           "\n-------------------------------------------------------\n");
//
//    printf("First Printing 100 Standard Gaussians\n");
//    for (int i = 0; i < 100; ++i) {
//        printf("%f\n",std_gaussian());
//    }
//    printf("First Printing 100 Gaussians with mean 5 and variance 2\n");
//    for (int i = 0; i < 100; ++i) {
//        printf("%f\n",gaussian(5.0,2));
//    }
//    printf("First Printing 100 Gaussians with mean 100 and variance 1000\n");
//    for (int i = 0; i < 100; ++i) {
//        printf("%f\n",gaussian(100.0,1000));
//    }
//    printf("First Printing 100 lognormals with mean 100 and variance 1000\n");
//    for (int i = 0; i < 100; ++i) {
//        printf("%f\n",lognormal(100.0,1000.0));
//    }
//    printf("First Printing 100 lognormals_ints with mean 100 and variance 1000\n");
//    for (int i = 0; i < 100; ++i) {
//        printf("%d\n",lognormal_int(100.0,1000.0));
//    }
//    printf("First Printing 100 lognormals_ints with mean 10 and variance 100\n");
//    for (int i = 0; i < 100; ++i) {
//        printf("%d\n",lognormal_int(10.0,100.0));
//    }
//
//
//    printf("Testing Graph Generation");
//    for(int i =10;i<100;i+=10){
//        for (int j = 0; j < 100; j+=5) {
//            printf("Generating graph of %d vertices with connectivity of %d percent",i,j);
//            graph* test_graph = generate_random_graph(i,(float)j/100,10,100);
//            printUnweightedGraph(test_graph);
//            freeGraph(test_graph);
//        }
//    }
//
//    printf("Testing Connectedness at 0.5 probability");
//    for(int i =10;i<1000;i+=50){
//        graph* test_graph = generate_random_graph(i,0.25,20,100);
//        printf("Testing Connected Components of graph of size %d",i);
//        int* connected_Random = connected_components(test_graph);
//        print_connected_components(connected_Random,test_graph->num_vertices);
//        freeGraph(test_graph);
//        free(connected_Random);
//    }
//
//    printf("Testing Connectedness at 100 nodes");
//    for(int i =0;i<100;i+=1){
//        graph* test_graph = generate_random_graph(100,(float)i/100,10,100);
//        printf("Testing Connected Components at probability of %d percent",i);
//        int* connected_Random = connected_components(test_graph);
//        print_connected_components(connected_Random,test_graph->num_vertices);
//        freeGraph(test_graph);
//        free(connected_Random);
//    }
//
//    printf("Testing Connectedness at 20 nodes");
//    for(int i =0;i<1000;i+=50){
//        printf("Testing Connected Components at probability of %f percent and graph size 20",(float)i/100);
//        graph* test_graph = generate_random_graph(20,(float)i/10000,10,100);
//        printUnweightedGraph(test_graph);
//        int* connected_Random = connected_components(test_graph);
//        print_connected_components(connected_Random,test_graph->num_vertices);
//        freeGraph(test_graph);
//        free(connected_Random);
//    }

    printf("Testing joining Components at 20 nodes");
    //for(int i =10;i<1000;i+=50){
    for(int i =10;i<=10;i+=50){
        printf("Testing Connected Components at probability of %f percent and graph size 20",(float)i/100);
        graph* test_graph = generate_random_graph(20,(float)i/10000,10,100);
        printUnweightedGraph(test_graph);
        int* connected_Random = connected_components(test_graph);
        print_connected_components(connected_Random,test_graph->num_vertices);
        connected_Random = join_components(test_graph,connected_Random);
        printf("Finished Joining Components\n");
        printUnweightedGraph(test_graph);
        print_connected_components(connected_Random,test_graph->num_vertices);
        freeGraph(test_graph);
        free(connected_Random);
    }
//    printf("Generating Random Connected Graphs");
//    for(int i =10;i<100;i+=10){
//        printf("generating random connected graph of 20nodes and %f density\n",i/10000.0);
//        graph* test_graph = random_connected_graph_generator(20,(float)i/10000);
//        printUnweightedGraph(test_graph);
//        int* connected_Random = connected_components(test_graph);
//        print_connected_components(connected_Random,test_graph->num_vertices);
//        freeGraph(test_graph);
//        free(connected_Random);
//    }


}