
#ifndef BETWEENNESSCENTRALITY_COMMON_HEADER_H
#define BETWEENNESSCENTRALITY_COMMON_HEADER_H



//First we declare the graph structures

// This is a node in the adjacency list in the array of
// adjacency lists (which is the graph). It contains the
// destination node number, and the weight of the edge.
typedef struct AdjListNode {
    //we use unsigned short as the number of vertices is said to be lower than 20k. unsigned short goes till 65535
    unsigned short destination;
    int weight;
    struct AdjListNode *next;
} adjlistNode;

// This is the adjacency list structure which depicts the
// node name (source), the number of edges going out from it,
// and a pointer to the first node in the list pointed to.
typedef struct AdjList {
    unsigned short source;
    unsigned short num_edges;
    adjlistNode *head;
} adjList;

//This is the main holding structure for the graph which contains an array of adjacency lists
typedef struct Graph {
    unsigned short num_vertices;
    adjList *vertexList;
} graph;


//Declare the structure type. More info in the floyd_warshall.c file.
typedef struct PrevHopNode {
    unsigned short node_no;
    struct PrevHopNode *next;
} prevHopNode;


typedef struct VVNode {
    int shortestPath_distance;
    unsigned short num_shortest_paths;
    prevHopNode *previous_hop;
} vvNode;

typedef struct NodesMatrix {
    unsigned short number_of_vertices;
    vvNode **matrix;
} nodesMatrix;

typedef struct NodesArray {
    unsigned short number_of_vertices;
    int num_elements;
    vvNode *vvnodes;
} nodesArray;

//graph functions
graph *createEmptyGraph(int num_vertices);
void addUndirectedEdge_atend(struct Graph *graph, int source, int destination, int weight);
int addEdge_atend(struct Graph *graph, int source, int destination, int weight);
void addUndirectedEdge(struct Graph *graph, int source, int destination, int weight);
void addUndirectedUnweightedEdge(struct Graph *graph, int source, int destination);
void addEdge(struct Graph *graph, int source, int destination, int weight);
void addUnweightedEdge(struct Graph *graph, int source, int destination);
void printGraph(graph *input);
void printUnweightedGraph(graph *input);
void freeGraph(graph *graphToFree);
graph *copyGraph(graph *graphtoCopy);

//building the graph
graph *build_graph(const char *filename, int num_vertices);
graph *build_unweighted_graph(const char *filename, int num_vertices);

//FloydWarshall
void printNodesArray(nodesArray *nodesarray);
nodesArray *floydWarshall(graph *input);

float *betweenness_centrality(nodesArray *nodesarray);

void print_betweenness(float *betweennessCentralityArray, int num_vertices);
void print_betweenness_normalized(float *betweennessCentralityArray, int num_vertices);
void print_betweenness_normalizedTo1(float *betweennessCentralityArray, int num_vertices);

//NodesArrayFunctions
int arrayIndex(int row, int col);

void initializeNodesArraywGraph(nodesArray *nodesarray, graph *input_graph);

void free_nodesArray(nodesArray *arraytoFree);

nodesArray *initialize_nodesArray(int num_vertices);


//BFS
nodesArray *buildNodesArrayBFS(graph *input);


//random
float rand01();

float std_gaussian();

float gaussian(float mean, float variance);

float lognormal(float mean, float variance);

int lognormal_int(float mean, float variance);

graph *generate_random_graph(unsigned short num_vertices, float probability_of_edge, float mean, float variance);

graph *generate_unweighted_random_graph(unsigned short num_vertices, float probability_of_edge);

graph *random_connected_graph_generator(unsigned short num_vertices, float probability_of_edge);

int *connected_components(const graph *input_graph);

void print_connected_components(int *components, int num_vertices);

int *join_components(graph *randomgraph, int *connected_components);

#endif //BETWEENNESSCENTRALITY_COMMON_HEADER_H
