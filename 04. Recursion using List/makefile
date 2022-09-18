# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
        
# Rule to link object code files to create executable file
josephus: josephus.o
	$(CXX) $(CXXFLAGS) -o josephus $^

# Rules to compile source code file to object code
josephus.o: josephus.cc josephus.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f josephus *.o
