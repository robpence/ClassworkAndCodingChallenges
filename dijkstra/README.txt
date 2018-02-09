# Robert Pence
# rpence
# CMPS 101 Spring 2015
# Dr. Allen Van Gelder
# graph04 Programming Assignment 4

What Does This Program do?

This program runs Prims and Dijkstras Algorithm.

How to you use it.
make sure you have these files:
	Makefile
	graph04.c
	graph04.h
	edgeList.h
	edgeList.c
	loadWgtGraph.c
	loadWgtGraph.h
	minPQ.c
	minPQ.h
	test1.in (or other properly formatted input files).

Compile with the "make graph04"

Then type graph04 "-D or -P" "Vertex" "input file"
an example would be:
	graph04 -P 7 test1.in
	or
	graph04 -D 1 test1.in
	
an example of the output for graph04 -P 1 test4.in would look something like this
n = 5
m = 14
Vertex Priority Status Parent
1:	0.000000,	t,	-1
2:	2.000000,	t,	1
3:	7.000000,	t,	4
4:	1.000000,	t,	5
5:	3.000000,	t,	2

an example of the output for graph04 -D 1 test4.in would look something like this
n = 5
m = 14
Vertex Priority Status Parent
1:	0.000000,	t,	-1
2:	2.000000,	t,	1
3:	9.000000,	t,	1
4:	6.000000,	t,	5
5:	5.000000,	t,	2
The weight of the Shortest Path is 16.000000

n is the number of Verticies
m is the number of edges
priority is the weight or distance for each edge
status: t means its in the tree and was taken
		f means its a fringe
		u means it was undiscovered
parent is the parent of the vertex. 
a -1 for the parent means it has no parent and is the starting vertex.
if the parent is 0 then it doesn't have a parent.

The program should print out the arrays for the vertex, the weight, the parent, and the status.
if you run with -P it will run Prims algorithm on a weighted graph.
if you run with -D it will run Dijkstras algorithm on a weighted graph.





