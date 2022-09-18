# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11

# Rule to link object code files to create executable file
parking: parking.o car.o garage.o
	$(CXX) $(CCFLAGS) -o parking $^

# Rules to compile source code files to object code
parking.o: parking.cc garage.h car.h
car.o: car.cc car.h
garage.o: garage.cc garage.h

garage.h: car.h

# Pseudo-target to remove object code and executable files
clean:
	rm -f parking *.o