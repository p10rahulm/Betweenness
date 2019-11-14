
#ifndef BETWEENNESSCENTRALITY_REACHABLES_H
#define BETWEENNESSCENTRALITY_REACHABLES_H

typedef struct ReachablesMatrixRow {
    int num_reachable;
    int* reachables;
} reachablesMatrixRow;


reachablesMatrixRow* reachablesGraph(int num_vertices);
void freereachablesGraph(reachablesMatrixRow* input,int num_vertices);
void addReachability(reachablesMatrixRow* input,int sourceIndex, int destinationIndex);
void initializeReachableswithGraph(reachablesMatrixRow* rm, graph* Graph);


#endif //BETWEENNESSCENTRALITY_REACHABLES_H
