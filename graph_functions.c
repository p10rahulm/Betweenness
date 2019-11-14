#include <stdio.h>
#include <stdlib.h>
#include "GraphFunctions.h"

void free_adjListNodes(adjlistNode *adjlistStart) {
    adjlistNode *current = adjlistStart;
    adjlistNode *next;
    if (current) {
        next = current->next;
    }

    while (current) {
        free(current);
        current = next;
        if (current) {
            next = current->next;
        } else { continue; }
    }
}

void freeGraph(graph *graphToFree) {
    int num_vertices = graphToFree->num_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        free_adjListNodes(graphToFree->vertexList[i].head);
    }
    free(graphToFree->vertexList);
    free(graphToFree);

}

graph *createEmptyGraph(int num_vertices) {
    graph *output = (graph *) malloc(sizeof(graph));
    output->num_vertices = (unsigned short) num_vertices;
    output->vertexList = (adjList *) malloc(num_vertices * sizeof(adjList));
    for (int i = 0; i < num_vertices; i++) {
        output->vertexList[i].source = (unsigned short) i + 1;
        output->vertexList[i].head = NULL;
        output->vertexList[i].num_edges = 0;
    }
    return output;
}

adjlistNode *create_new_node(int destination, int weight, adjlistNode *next) {
    adjlistNode *new_node_pointer = (adjlistNode *) malloc(sizeof(adjlistNode));
    new_node_pointer->destination = (unsigned short) destination;
    new_node_pointer->weight = weight;
    new_node_pointer->next = next;
    return new_node_pointer;
}

adjlistNode *create_new_unweighted_node(int destination, adjlistNode *next) {
    adjlistNode *new_node_pointer = (adjlistNode *) calloc(1, sizeof(adjlistNode));
    new_node_pointer->destination = (unsigned short) destination;
    new_node_pointer->next = next;
    return new_node_pointer;
}

graph *copyGraph(graph *graphtoCopy) {
    int num_vertices = graphtoCopy->num_vertices;
    graph *output = createEmptyGraph(num_vertices);
    output->num_vertices = num_vertices;

    for (int i = 0; i < num_vertices; ++i) {
        output->vertexList[i].source = graphtoCopy->vertexList[i].source;
        output->vertexList[i].num_edges = graphtoCopy->vertexList[i].num_edges;
        if (!graphtoCopy->vertexList[i].head) { continue; }
        adjlistNode *Copied = graphtoCopy->vertexList[i].head;
        adjlistNode *Copier = create_new_node(Copied->destination, Copied->weight, NULL);
        output->vertexList[i].head = Copier;
        Copied = Copied->next;
        while (Copied) {
            Copier->next = create_new_node(Copied->destination, Copied->weight, NULL);
            Copier = Copier->next;
            Copied = Copied->next;
        }

    }
    return output;

}


void addEdge(struct Graph *graph, int source, int destination, int weight) {
    //adjlistNode *old_list_head = NULL;
    adjlistNode *old_list_head = graph->vertexList[source - 1].head;
    adjlistNode *newNode = create_new_node(destination, weight, old_list_head);
    graph->vertexList[source - 1].head = newNode;
    graph->vertexList[source - 1].num_edges += 1;
}

// Adds an edge to an undirected graph.
// Returns 1 if successful or 0 if not successful
int addEdge_atend(struct Graph *graph, int source, int destination, int weight) {
    adjlistNode *rover = graph->vertexList[source - 1].head;
    while (rover) {
        if (rover->destination == destination) {
            return 0;
        }
    }
    adjlistNode *newNode = create_new_node(destination, weight, NULL);
    rover->next = newNode;
    graph->vertexList[source - 1].num_edges += 1;
    return 1;
}

void addUndirectedEdge_atend(struct Graph *graph, int source, int destination, int weight) {
    if (addEdge_atend(graph, source, destination, weight)) {
        addEdge_atend(graph, destination, source, weight);
    }
}

void addUndirectedEdge(struct Graph *graph, int source, int destination, int weight) {
    addEdge(graph, source, destination, weight);
    addEdge(graph, destination, source, weight);
}

void addUnweightedEdge(struct Graph *graph, int source, int destination) {
    adjlistNode *old_list_head = graph->vertexList[source - 1].head;
    adjlistNode *newNode = create_new_unweighted_node(destination, old_list_head);
    graph->vertexList[source - 1].head = newNode;
    graph->vertexList[source - 1].num_edges += 1;
}

void addUndirectedUnweightedEdge(struct Graph *graph, int source, int destination) {
    addUnweightedEdge(graph, source, destination);
    addUnweightedEdge(graph, destination, source);
}

void printGraph(graph *input) {
    printf("\n------------GRAPH: Number of Vertices = %d------------\n", input->num_vertices);
    for (int i = 0; i < input->num_vertices; i++) {
        adjlistNode *rover;
        if (input->vertexList[i].head) {
            rover = input->vertexList[i].head;
        } else { continue; }
        printf("\n Adjacency list of vertex: %d\t\t ", input->vertexList[i].source);
        while (rover) {
            printf("-> (edge = %d,wt = %d)", rover->destination, rover->weight);
            rover = rover->next;
        }
        printf("\n");
    }
    printf("-----------------------------------------------------\n");
}


void printUnweightedGraph(graph *input) {
    printf("\n------------GRAPH: Number of Vertices = %d------------\n", input->num_vertices);
    for (int i = 0; i < input->num_vertices; i++) {
        adjlistNode *rover;
        if (input->vertexList[i].head) {
            rover = input->vertexList[i].head;
        } else { continue; }
        printf("\n Adjacency list of vertex: %d, NumVertices = %d\t\t ", input->vertexList[i].source,
               input->vertexList[i].num_edges);
        while (rover) {
            printf("-> %d", rover->destination);
            rover = rover->next;
        }
        printf("\n");
    }
    printf("-----------------------------------------------------\n");
}
