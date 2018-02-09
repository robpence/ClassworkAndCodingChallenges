//loadWgtGraph.h
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

#ifndef C101loadGraph
#define C101loadGraph


//structs and stuff
typedef char * Cstring;

//access functions
int parseN(Cstring lineRtrn);

int loadEdges(FILE *inbuf, EdgeList* origGraph, int TASK);

EdgeList* initEdges(int n);

#endif