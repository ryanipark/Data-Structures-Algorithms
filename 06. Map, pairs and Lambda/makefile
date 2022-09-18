# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

# Rule to link object code files to create executable file
wordscanner: wordscanner.o
	$(CXX) $(CCFLAGS) -o wordscanner $^

# Rules to compile source code files to object code
wordscanner.o: wordscanner.cc

# Pseudo-target to remove object code and executable files
clean:
	rm -f wordscanner *.o
