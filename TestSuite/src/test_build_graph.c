#include "GraphFunctions.h"
#include <stdio.h>

int main() {
    printf("\n--------------------------"
           "\nTESTING BUILDING OF GRAPHS"
           "\n--------------------------");

    {
        graph* graph = build_graph("data/contact-high-school-proj-graph.txt",327);
        printUnweightedGraph(graph);
        freeGraph(graph);
    }
    {
        graph* graph = build_unweighted_graph("data/contact-high-school-proj-graph.txt",327);
        printUnweightedGraph(graph);
        freeGraph(graph);
    }
    /*
     *  Check the last few in the output
     *  310 326 1
     *  311 326 6
     *  24 327 1
     *  51 327 5
     *  91 327 1
     *  95 327 3
     *  96 327 3
     *  157 327 7
     *  158 327 24
     *  164 327 17
     *  165 327 2
     *  169 327 2
     */



}