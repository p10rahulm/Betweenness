all : BetweennessCentrality.out test_graph_functions.out test_build_graph.out test_floyd_warshall.out test_random_connected_graph_generator.out test_large_graph_generation.out test_large_graphs.out test_bfs.out
	 
BetweennessCentrality.out    :   main.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o
	gcc -o BetweennessCentrality.out main.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o -lm

test_floyd_warshall.out	: test_floyd_warshall.o build_graph.o graph_functions.o floyd_warshall.o betweennessCentrality.o nodesArrayFunctions.o reachables.o random_connected_graph_generator.o
	gcc -o test_floyd_warshall.out  test_floyd_warshall.o build_graph.o graph_functions.o floyd_warshall.o betweennessCentrality.o nodesArrayFunctions.o reachables.o random_connected_graph_generator.o -lm


test_graph_functions.out	: 	test_graph_functions.o graph_functions.o
	gcc -o test_graph_functions.out test_graph_functions.o graph_functions.o

test_build_graph.out	:	test_build_graph.o build_graph.o graph_functions.o
	gcc -o test_build_graph.out  test_build_graph.o build_graph.o graph_functions.o

test_random_connected_graph_generator.out	:	test_random_connected_graph_generator.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o 
	gcc -o test_random_connected_graph_generator.out test_random_connected_graph_generator.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o -lm

test_large_graph_generation.out	: test_large_graph_generation.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o
	gcc -o test_large_graph_generation.out test_large_graph_generation.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o  -lm

test_large_graphs.out	: test_large_graphs.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o
	gcc -o test_large_graphs.out test_large_graphs.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o  -lm

test_bfs.out: test_bfs.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o 
	gcc -o test_bfs.out test_bfs.o build_graph.o graph_functions.o floyd_warshall.o reachables.o betweennessCentrality.o nodesArrayFunctions.o bfs.o random_connected_graph_generator.o -lm

# now for the dependancies for the above executables

main.o: main.c FloydWarshall.h BFS.h BetweennessCentrality.h
	gcc -c main.c

build_graph.o: build_graph.c GraphFunctions.h
	gcc -c build_graph.c

graph_functions.o: graph_functions.c GraphFunctions.h
	gcc -c graph_functions.c

floyd_warshall.o: floyd_warshall.c FloydWarshall.h
	gcc -c floyd_warshall.c

random_connected_graph_generator.o	: random_connected_graph_generator.c RandomGraph.h
	gcc -c random_connected_graph_generator.c
	
betweennessCentrality.o	: betweennessCentrality.c BetweennessCentrality.h
	gcc -c betweennessCentrality.c

nodesArrayFunctions.o	: nodesArrayFunctions.c ProcessedGraph.h
	gcc -c nodesArrayFunctions.c

reachables.o	:	reachables.c Reachables.h
	gcc -c reachables.c

bfs.o	: bfs.c BFS.h
	gcc -c bfs.c

test_graph_functions.o: test_graph_functions.c GraphFunctions.h
	gcc -c test_graph_functions.c
	
test_build_graph.o:	test_build_graph.c GraphFunctions.h
	gcc -c test_build_graph.c

test_floyd_warshall.o: test_floyd_warshall.c FloydWarshall.h
	gcc -c test_floyd_warshall.c
	
test_random_connected_graph_generator.o	:	test_random_connected_graph_generator.c RandomGraph.h
	gcc -c test_random_connected_graph_generator.c
	
test_large_graph_generation.o: test_large_graph_generation.c RandomGraph.h
	gcc -c test_large_graph_generation.c
	
test_large_graphs.o: test_large_graphs.c FloydWarshall.h BFS.h BetweennessCentrality.h
	gcc -c test_large_graphs.c

test_bfs.o	:	test_bfs.c BFS.h
	gcc -c test_bfs.c