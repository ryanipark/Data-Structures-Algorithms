# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
        
# Rule to Link
all: stack

stack: main.o rational.o
	$(CXX) $(CXXFLAGS) -o stack $^

# Compile to obj
main.o: main.cc stack.h rational.h
rational.o: rational.cc rational.h
   
# make clean
clean:
	rm -f stack *.o