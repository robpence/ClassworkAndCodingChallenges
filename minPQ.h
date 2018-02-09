/*
Robert Pence
CMPS101
rpence
1366060
*/

/* minPQ.h (what is the purpose of this file?)
*///This is a Header file for minPQ. it tells the compiler what to expect from the .c file
	//it also tells others who look at it the preconditions and post conditions of functions.

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* Access functions (what are the preconditions?)
*/

/** isEmpty
*///Pre: a priority queue
int isEmptyPQ(MinPQ pq);

/** getMin
*///Pre: a priority queue
int getMin(MinPQ pq);

/** getStatus
*///Pre: a priority queue and a specific node in that queue categorized by id
int getStatus(MinPQ pq, int id);

/** getParent
*///Pre: a priority queue and a specific node in that queue categorized by id
int getParent(MinPQ pq, int id);

/** getPriority
*///Pre: a priority queue and a specific node in that queue categorized by id
double getPriority(MinPQ pq, int id);

/* Manipulation procedures (what are the preconditions and postconditions?)
*/

/** delMin
*///Pre: a pq, Post: the same pq but with the min deleted
void delMin(MinPQ pq);

/** insertPQ
*///Pre: a pq, an id, a priority or weight, and a parent. Post: the updated pq
void insertPQ(MinPQ pq, int id, double priority, int par);

/** decreaseKey
*///Pre: a pq, an id, the priority, and the parent. Post: the updated pq
void decreaseKey(MinPQ pq, int id, double priority, int par);

/* Constructors (what are the preconditions and postconditions?)
*/

/**
*///Pre: the number of vertices, their status, weight, and parent. Post: a priority queue.
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif

