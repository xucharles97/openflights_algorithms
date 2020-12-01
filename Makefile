# Executable names:
CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

TEST = test

test: test.o Graph.o 
	$(CXX) $(CXXFLAGS) -o test test.o Graph.o

test.o: graph/tests/test.cpp graph/Graph.h graph/Edge.h
	$(CXX) $(CXXFLAGS) graph/tests/test.cpp Graph.o

Graph.o: graph/Graph.cpp graph/Graph.h graph/Edge.h
	$(CXX) $(CXXFLAGS) graph/Graph.cpp

clean:
	rm *.o && rm test

.PHONY: all clean