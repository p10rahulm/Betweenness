#ifndef BETWEENNESSCENTRALITY_BETWEENNESSCENTRALITY_H
#define BETWEENNESSCENTRALITY_BETWEENNESSCENTRALITY_H


#include "ProcessedGraph.h"

// Computation of BetweennessCentrality

float *betweenness_centrality(processedGraph *pg);

float *betweenness_centralityLowMem(processedGraph *pg);

void print_betweenness(float *betweennessCentralityArray, int num_vertices);

void print_betweenness_normalized(float *betweennessCentralityArray, int num_vertices);

void print_betweenness_normalizedTo1(float *betweennessCentralityArray, int num_vertices);


#endif //BETWEENNESSCENTRALITY_BETWEENNESSCENTRALITY_H
