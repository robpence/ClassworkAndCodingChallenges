/*
Robert Pence
CMPS101
rpence
1366060
*/
//edgeList.c

#include <stdio.h>
#include <stdlib.h>
#include "edgeList.h"
#include "loadWgtGraph.h"


/*-------Structs & stuff--------------------------------------------------------------*/
typedef struct EdgeListNode * EdgeList;

extern const EdgeList edgeNil; 
//EdgeList edgeNil = NULL;

/*
typedef struct EdgeInfoStruct{
    int to;
    double wgt;
}EdgeInfo;
*/

//defines the edgeListNode struct
typedef struct EdgeListNode{
	EdgeInfo element;
	EdgeList next;
}EdgeListNode;


/*------------------------------access functions---------------------*/


//returns the element from the start of first edge
EdgeInfo edgeFirst(EdgeList aList){
	return aList->element;
}

//returns the rest of the edges
EdgeList edgeRest(EdgeList aList){
	return aList->next;
}

/*--------------------------constructors---------------------*/
//constructs the actual edge that the edgeList uses
EdgeList edgeCons(EdgeInfo newE, EdgeList oldL){

	EdgeList newList = calloc(1, sizeof(struct EdgeListNode));
	newList->element = newE;
	newList->next = oldL;
	
	return newList;
}


