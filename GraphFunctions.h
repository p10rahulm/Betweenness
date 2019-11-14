#ifndef BETWEENNESSCENTRALITY_GRAPHFUNCTIONS_H
#define BETWEENNESSCENTRALITY_GRAPHFUNCTIONS_H



// Structures for graph

typedef struct AdjListNode {
    unsigned short destination;
    int weight;
    struct AdjListNode *next;
} adjlistNode;


// This is the adjacency list structure which is a list of nodes that every source node is connected to in Graph
typedef struct AdjList {
    unsigned short source;
    unsigned short num_edges;
    adjlistNode *head;
} adjList;


// Graph Structure
typedef struct Graph {
    unsigned short num_vertices;
    adjList *vertexList;
} graph;


//Functions on those structures

graph *createEmptyGraph(int num_vertices);

void addUndirectedEdge(struct Graph *graph, int source, int destination, int weight);

void addUndirectedUnweightedEdge(struct Graph *graph, int source, int destination);

void printUnweightedGraph(graph *input);

void freeGraph(graph *graphToFree);

graph *copyGraph(graph *graphtoCopy);


//building the graph

graph *build_graph(const char *filename, int num_vertices);

graph *build_unweighted_graph(const char *filename, int num_vertices);

#endif //BETWEENNESSCENTRALITY_GRAPHFUNCTIONS_H
