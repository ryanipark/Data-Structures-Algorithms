OBJS	= graph.o simplegraph.o
SOURCE	= graph.cc simplegraph.cc
HEADER	= graph.h
OUT	= simplegraph
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

graph.o: graph.cc
	$(CC) $(FLAGS) graph.cc 

simplegraph.o: simplegraph.cc
	$(CC) $(FLAGS) simplegraph.cc 


clean:
	rm -f $(OBJS) $(OUT)