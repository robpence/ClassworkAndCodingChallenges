//loadWgtGraph.c
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
#include "edgeList.h"
#include "loadWgtGraph.h"

/*-------Structs & stuff--------------------------------------------------------------*/
typedef char * Cstring;

//struct for an edge, same as the last 3 programs
typedef struct{
	int from;
	int to;
	double weight;
} Edge;

/*------------------------------access functions--------------------------------------*/
//allocates for the edges in the lists
EdgeList* initEdges(int n){
	EdgeList* adjVertices = calloc(n+1, sizeof(EdgeList));
	int i=1;
	while(i<=n){
		//adjVertices[i] = edgeNil;
		adjVertices[i] = NULL;
		i++;
	}
	return adjVertices;
}

//parses in the lines
//uses library function strtok and atoi
int parseN(Cstring lineRtrn){
	char *token;
	token = strtok(lineRtrn, "\n");
	int n = atoi(token);
	return n;
}

//parses in the edges and makes sure that the format of the file is correct
Edge parseEdge(char line[]){
	int numFields;
	Edge newE;
	numFields = sscanf(line, "%d %d %lf %*s", &newE.from, &newE.to, &newE.weight);
	//fields are 3 or 4 instead of 2 or 3 now
	if(numFields < 3 || numFields > 4){
		printf("Bad edge: %s\n", line);
		exit(1);
	}
	return newE;
}

//loops through the edges and connects them to the correct vertices, hopefully
int loadEdges(FILE *inbuf, EdgeList* adjVertices, int TASK){
	int m = 0;
	char line[1024];
	Cstring moreLines = fgets(line, 1024, inbuf);
	while(moreLines != NULL){
		Edge e = parseEdge(line);
		EdgeInfo newE;
		newE.to = e.to;
		
		//set the weight
		newE.wgt = e.weight;
	
		adjVertices[e.from] = edgeCons(newE, adjVertices[e.from]);
		
		//if P make it a undirected graph
		if(TASK == 1){
			newE.to = e.from;
			adjVertices[e.to] = edgeCons(newE, adjVertices[e.to]);
		}
		
		m++;
		moreLines = fgets(line, 1024, inbuf);
	}
	return m;
}




