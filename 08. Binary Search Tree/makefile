OBJS	= bst.o
SOURCE	= bst.cc
HEADER	= BinaryTree.h bst.h node.h binarysearchtree.h
OUT	= bst
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

bst.o: bst.cc
	$(CC) $(FLAGS) bst.cc 


clean:
	rm -f $(OBJS)