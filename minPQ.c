/*
Robert Pence
CMPS101
rpence
1366060
*/
//minPQ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "loadWgtGraph.h"
#include "minPQ.h"
#include "edgeList.h"


/*
int numVertices;
int numPQ;
int minVertex;
float infinity;
//arrays
int status[];
int parent[];
double fringeWgt[];
*/

//defines the MinPQNode for minPQ
typedef struct MinPQNode{
    int numVertices;
    int numPQ;
	int minVertex;
	float infinity;
	int * status;
	int * parent;
	double * fringeWgt;
}MinPQNode;


//constructs a priority queue with n vertices
MinPQ createPQ(int n, int status[], double priority[], int parent[]){
	MinPQ pq = calloc(1, sizeof(struct MinPQNode));
	pq->parent = parent;
	pq->fringeWgt = priority;
	pq->status = status;
	
	
	int setThisOne;
	for(setThisOne = 1; setThisOne <= n; setThisOne++){
		pq->status[setThisOne] = UNSEEN; //UNSEEN or 'u' im not sure
	}
	
	pq->numVertices = n;
	pq->numPQ = 0;
	pq->minVertex = -1;
	pq->infinity = INFINITY;
	return pq;
}

//insert things into the queue, id is the spot in the queue, par is the parent, and priority is its weight
void insertPQ(MinPQ pq, int id, double priority, int par){
	//pq->parent[id] = newPar;
	
	//set all the things
	pq->status[id] = FRINGE;
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->minVertex = -1;
	
	pq->numPQ++;
	return;
}

//decrease the queue
void decreaseKey(MinPQ pq, int id, double priority, int par){
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->minVertex = -1;
	return;
}

//delete the mininum in the queue
void delMin(MinPQ pq){
	int oldMin = getMin(pq);
	pq->status[oldMin] = INTREE;
	pq->minVertex = -1;
	pq->numPQ--;
	return;
}

//is the pq empty?
int isEmptyPQ(MinPQ pq){
	if(pq->numPQ == 0){
		return 0;	//yes
	}
	else return 1;	//no
}

//find the minimun weight in the queue
void findMin(MinPQ pq){
	int v;
	double smallWgt;
	
	smallWgt = INFINITY;				//set to infinity
	
	for(v = 1; v <= pq->numVertices; v++){
		if(pq->status[v] == FRINGE){
			if(pq->fringeWgt[v] < smallWgt){
				pq->minVertex = v;
				smallWgt = pq->fringeWgt[v];
			}
		}
	
	}
	return;
}

//get the minimun vertex in the queue
int getMin(MinPQ pq){
	if(pq->minVertex == -1){
		findMin(pq);
	}
	return pq->minVertex;
}

//call to get the status of a element in the queue
int getStatus(MinPQ pq, int id){
	return pq->status[id];
}

//call to get the parent of a element in the queue
int getParent(MinPQ pq, int id){
	return pq->parent[id];
}

//call to get the priority of a element in the queue
double getPriority(MinPQ pq, int id){
	return pq->fringeWgt[id];
}

