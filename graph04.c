/*
Robert Pence
CMPS101
rpence
1366060
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <unistd.h>
#include "loadWgtGraph.h"
#include "minPQ.h"
#include "edgeList.h"


/*-------Structs & stuff--------------------------------------------------------------*/
typedef char * Cstring;

int TASK;
int sV;
int n;
double newDist;

/*--------Functions-------------------------------------------------------------------*/
/*
//prints the graph, testing purposes.
int printGraph(IntList* origGraph, int j, int n){
		while(j <= n){
			printf("%d\t", j);
			IntList temp = origGraph[j];
			printf("[");
			while(temp != NULL){
				int q = intFirst(temp);
				temp = intRest(temp);
				if(temp != NULL ){
					printf("%d, ", q);
				}
				else {
					printf("%d", q);
				}
			}
		printf("]\n");
		j++;
		}
		return 0;
	}
*/

//calculates the priority.
void calcPriority();

//prints the arrays for priority, status, and parent. also prints the shortest path
//called in greedytree.
void printOutput(MinPQ pq){
	int p;
	printf("Vertex Priority Status Parent\n");
	for(p = 1; p<=n; p++ ){
		printf("%d: %f, %c, %d\n", p, getPriority(pq, p), getStatus(pq, p), getParent(pq, p));
	}
	if(TASK == 0){
		printf("The weight of the Shortest Path is: %f\n", newDist);
	}
	return;
}

//updates the Fringe
void updateFringe(MinPQ pq, EdgeList adjInfoOfV, int v){
	//get the original distance or weight
	double myDistance = getPriority(pq, v);
	EdgeList remAdj;
	remAdj = adjInfoOfV;
	while(remAdj != NULL){
		EdgeInfo wInfo = edgeFirst(remAdj);
		int w = wInfo.to;
		double newWeight = wInfo.wgt;
		if(TASK == 0){
			//if D calculate the shortest path
			newDist = myDistance + wInfo.wgt;
			newWeight = myDistance + wInfo.wgt;
		}
		//double newWeight = wInfo.wgt;
		//if unseen add it to the pq
		if(getStatus(pq, w) == UNSEEN){
			insertPQ(pq, w, newWeight, v);
		}
		//if fringe, run calcPriority
		else if(getStatus(pq, w) == FRINGE){
			if(newWeight < getPriority(pq, w)){
				decreaseKey(pq, w, newWeight, v);
			}
		}
		remAdj = edgeRest(remAdj);
	}
	return;
}

//P or D algorithm that also prints the pq with n, status, parent, and the weight
void greedyTree(EdgeList * adjInfo, int n, int s, int * parent, double * fringeWgt, int * status){
	//create a pq for n, status, fringewgt, and parent
	MinPQ pq = createPQ(n, status, fringeWgt, parent);
	insertPQ(pq, s, 0, -1);
	//check to see if the pq is empty
	while(isEmptyPQ(pq) == 1){
		int smallestV = getMin(pq);
		delMin(pq);
		updateFringe(pq, adjInfo[smallestV], smallestV);
	}
	//print output with this function because we already have the pq with everything in it
	printOutput(pq);
	return;
}



/*-------------------------------Main---------------------------------------------*/
int main ( int argc, char *argv[] ){
	//declaring variables
	//P or D
	int whichone;
	//Number of edges in the graph
	int m;
	
	//allocate space for the input into a list
	EdgeList* THISGRAPH = calloc(1024, sizeof(EdgeList));
	char line[1024];
	
	//if there aren't 4 arguments tell user the correct usage of the program
	if(argc != 4){
		printf("Usage: graph04 -DP StartVertex input.data\n");
		exit(1);
	}
	
	//is the start vertex inputed a valid number for start vertex?
	//uses library function atoi to convert strings to ints.
	sV = atoi(argv[2]);
	if(!sV >= 1){
		printf("Usage: graph04 -DP StartVertex input.data\n");
		exit(1);
	}
	
	//get and check the input file to make sure its not NULL
	FILE *inbuf;
	inbuf = fopen(argv[3], "r");
	if(inbuf == NULL){
		printf("Usage: graph04 -arg StartVertex input.data\n");
		exit(1);
	}
	
	//take in arguments for -D or -P, check to make sure they're valid
	//uses library function getopt
	while((whichone = getopt (argc, argv, "PD:")) != -1){
		switch(whichone){
			case 'P':
				TASK = 1;
				break;
			case 'D':
				TASK = 0;
				break;
			default:
				printf("Usage: graph04 -DP StartVertex input.data\n");
				break;
		}
	}
	
	//fgets to get the lines, print out n and m
	Cstring lineRtrn = (fgets(line, 1024, inbuf));
	//prints out n
	n = parseN(lineRtrn);
	printf("n = %d\n", n);
	THISGRAPH = initEdges(n);
	//prints out m
	m = loadEdges(inbuf, THISGRAPH, TASK);
	fclose(inbuf);
	printf("m = %d\n", m);
	
	//declare all the arrays for parent fringeWgt and status
	int * parent = (int*)calloc(n+1, (n+1)*sizeof(int));
	double * fringeWgt = (double*)calloc(n+1, (n+1)* sizeof(double));
	int * status = calloc(n + 1, (n+1)*sizeof(int));
	
	//greedyTree prints the output of the arrays for me
	//also calls update fringe
	greedyTree(THISGRAPH, n, sV, parent, fringeWgt, status);
	
	return 1;
}
	
