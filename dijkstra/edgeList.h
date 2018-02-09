/*
Robert Pence
CMPS101
rpence
1366060
*/


/* edgeList.h
 * (what is the purpose of this file?)
 *///This is a Header file for edgeList. it is to tell the compiler what to expect from the .c file
	//it also tells others who look at it the preconditions and post conditions of functions

#ifndef C101EdgeList
#define C101EdgeList
/* Multiple typedefs for the same type are an error in C. */

typedef struct EdgeListNode * EdgeList;

typedef struct EdgeInfoStruct{
    int to;
    double wgt;
    }
    EdgeInfo;

/** edgeNil denotes the empty EdgeList */
extern const EdgeList edgeNil;

/* Access functions
 * (what are the preconditions?)
 */

/** first
*///Pre: a EdgeList
EdgeInfo edgeFirst(EdgeList oldL);

/** rest
*///Pre: a EdgeList
EdgeList edgeRest(EdgeList oldL);

/* Constructors
 * (what are the preconditions and postconditions?)
 */

/** cons
*///Pre: a new edge, and a EdgeList. Post: the new EdgeList
EdgeList edgeCons(EdgeInfo newE, EdgeList oldL);

#endif

