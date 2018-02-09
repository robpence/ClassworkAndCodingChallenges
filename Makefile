#Robert Pence
#Program 4
#Makefile for Program 4

# See Cmake/Makefile for a complete commented sample Makefile,
# illustrating separate compilation and dependencies.

# Running "make" can generate many error messages.  Do
#	make edgeList.o >& make.log
# to compile edgeList.c and cause the errors to go into the file make.log.
# When "make" finishes you can read the file with "view", "more", or "less".
#
# Many later error messages can be meaningless because they were caused
# by an earlier error.  Always try to correct errors in order.


CC     = gcc
CFLAGS = -g -Wall -O0

edgeList.o:	edgeList.c  edgeList.h
	${CC}  -c  ${CFLAGS}  edgeList.c
	
loadWgtGraph.o: loadWgtGraph.c loadWgtGraph.h
	${CC} -c ${CFLAGS}	loadWgtGraph.c
	
minPQ.o: minPQ.c minPQ.h
	${CC} -c ${CFLAGS}	minPQ.c
	
graph04.o: graph04.c
		${CC}  -c  ${CFLAGS} graph04.c
		
graph04:  graph04.o edgeList.o loadWgtGraph.o minPQ.o
		${CC}  -o graph04 ${CFLAGS} graph04.o edgeList.o loadWgtGraph.o minPQ.o
		
clean:
	rm -f graph04.o edgeList.o loadWgtGraph.o minPQ.o graph04
	
	
	
	
	
	