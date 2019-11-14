#include <stdio.h>
#include <stdlib.h>

#include "GraphFunctions.h"

void parseline(char* line, int* source, int* destination, int* weight) {
    *source = 0;*destination = 0;*weight = 0;int i;
    for (i = 0; line[i] != ' '; i++) { *source = *source * 10 + (line[i] - '0'); }
    for (i++; line[i] != ' '; i++) { *destination = *destination * 10 + (line[i] - '0'); }
    for (i++; line[i] != ' ' && line[i] != '\n'; i++) { *weight = *weight * 10 + (line[i] - '0'); }
}

void readfile_add_tograph_unweighted(graph* input,const char* filename){
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int source,destination,weight;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\nPlease input a valid filename.\n");
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        parseline(line,&source,&destination,&weight);
        addUndirectedEdge(input,source,destination,1);
    }
    fclose(fp);
    if (line){free(line);}

}

void readfile_add_tograph(graph* input,const char* filename){
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int source,destination,weight;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\nPlease input a valid filename.\n");
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        parseline(line,&source,&destination,&weight);
        addUndirectedEdge(input,source,destination,weight);
    }
    fclose(fp);
    if (line){free(line);}

}


graph* build_graph(const char* filename, int num_vertices){
    graph* graph = createEmptyGraph(num_vertices);
    readfile_add_tograph(graph,filename);
    return graph;
}

graph* build_unweighted_graph(const char* filename, int num_vertices){
    graph* graph = createEmptyGraph(num_vertices);
    readfile_add_tograph_unweighted(graph,filename);
    return graph;
}
