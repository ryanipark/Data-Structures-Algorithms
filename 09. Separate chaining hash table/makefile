OBJS	= hashmain.o htable.o
SOURCE	= hashmain.cc htable.cc
HEADER	= hashmain.h entry.h htable.h
OUT	= hash
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

hashmain.o: hashmain.cc
	$(CC) $(FLAGS) hashmain.cc -std=c++11

htable.o: htable.cc
	$(CC) $(FLAGS) htable.cc -std=c++11


clean:
	rm -f $(OBJS) $(OUT)