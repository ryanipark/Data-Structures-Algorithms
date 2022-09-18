OBJS	= binarytree.o
SOURCE	= binarytree.cc
HEADER	= btree.h node.h
OUT	= binarytree
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

binarytree.o: binarytree.cc
	$(CC) $(FLAGS) binarytree.cc 


clean:
	rm -f $(OBJS) $(OUT)