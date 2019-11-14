//
// Created by rmaddy on 11-10-2019.
//

#ifndef BETWEENNESSCENTRALITY_FLOYDWARSHALL_H
#define BETWEENNESSCENTRALITY_FLOYDWARSHALL_H

////Data Structures to Process Graph
#include "ProcessedGraph.h"
#include "Reachables.h"

////Function to process graph with the FloydWarshall Algorithm
processedGraph* processGraphFW(graph *input);
processedGraph* processGraphFWLowMem(graph *input);
processedGraph* processGraphFWLowMemReachables(graph *input);
processedGraph* processGraphFWReachablesPathMatrix(graph *input, float heuristic);

#endif //BETWEENNESSCENTRALITY_FLOYDWARSHALL_H
