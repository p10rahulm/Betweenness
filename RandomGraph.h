
#ifndef BETWEENNESSCENTRALITY_RANDOMGRAPHHEADER_H
#define BETWEENNESSCENTRALITY_RANDOMGRAPHHEADER_H


//// We need structues defined in the following header
#include "graphFunctions.h"


float rand01();
float std_gaussian();
float gaussian(float mean, float variance);
float lognormal(float mean, float variance);
int lognormal_int(float mean, float variance);



graph *generate_random_graph(unsigned short num_vertices, float probability_of_edge, float mean, float variance);
graph *generate_unweighted_random_graph(unsigned short num_vertices, float probability_of_edge);

int *connected_components(const graph *input_graph);
void print_connected_components(int *components, int num_vertices);
int *join_components(graph *randomgraph, int *connected_components);

//Random Graph Generation
graph *random_connected_graph_generator(unsigned short num_vertices, float probability_of_edge);


#endif //BETWEENNESSCENTRALITY_RANDOMGRAPHHEADER_H
