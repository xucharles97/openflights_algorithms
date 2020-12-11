#!/bin/bash
EXENAME = main

SHELL := /bin/bash # Use bash syntax

# Compiler/linker config and object/depfile directory:
CXX = clang++
LD = clang++

# -MMD and -MP asks clang++ to generate a .d file listing the headers used in the source code for use in the Make process.
#   -MMD: "Write a depfile containing user headers"
#   -MP : "Create phony target for each dependency (other than main file)"
#   (https://clang.llvm.org/docs/ClangCommandLineReference.html)
DEPFILE_FLAGS = -MMD -MP

# Provide lots of helpful warning/errors:
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

# Flags for compile:
CXXFLAGS = -std=c++1y -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c
# Flags for linking:
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif

# ALL UNDERLYING GRAPH FILES
GRAPH_FILES = graph/Graph.h graph/Edge.h graph/Graph.hpp
# ALL UNDERLYING PARSING FILES
PARSING_FILES = graph/MathFunctions.hpp graph/Parsing.hpp
# ALL UNDERLYING TRAVERSAL FILES
TRAVERSAL_FILES = traversals/BFS.hpp traversals/DFS.hpp traversals/GraphTraversal.hpp
# ALL UNDERLYING ALGORITHM FILES
ALGORITHM_FILES = algorithms/FloydWarshall.hpp algorithms/Dijkstra.hpp algorithms/BetweennessCentrality.hpp

output_msg: ; $(CLANG_VERSION_MSG)

.PHONY: all test clean output_msg

all : $(EXENAME)

# Main Targets

main: output_msg main.o
	$(LD) main.o $(LDFLAGS) -o main

main.o: main.cpp $(GRAPH_FILES) $(PARSING_FILES) $(ALGORITHM_FILES)
	$(CXX) $(CXXFLAGS) -o main.o main.cpp

# Test Targets

test: output_msg catchmain.o graph_tests.o bfs_dfs_tests.o floyd_warshall_tests.o dijkstra_tests.o Betweenness_tests.o parsing_tests.o
	$(LD) catchmain.o graph_tests.o bfs_dfs_tests.o floyd_warshall_tests.o dijkstra_tests.o Betweenness_tests.o parsing_tests.o $(LDFLAGS) -o test

parsing_tests.o: tests/Parsing_Tests.cpp $(GRAPH_FILES) $(PARSING_FILES)
	$(CXX) $(CXXFLAGS) -o parsing_tests.o tests/Parsing_Tests.cpp

graph_tests.o: tests/Graph_Tests.cpp $(GRAPH_FILES) $(PARSING_FILES)
	$(CXX) $(CXXFLAGS) -o graph_tests.o tests/Graph_Tests.cpp

bfs_dfs_tests.o: tests/BFS_and_DFS_tests.cpp $(GRAPH_FILES) $(TRAVERSAL_FILES)
	$(CXX) $(CXXFLAGS) -o bfs_dfs_tests.o tests/BFS_and_DFS_tests.cpp

floyd_warshall_tests.o: tests/Floyd_Warshall_Tests.cpp $(GRAPH_FILES) $(ALGORITHM_FILES)
	$(CXX) $(CXXFLAGS) -o floyd_warshall_tests.o tests/Floyd_Warshall_Tests.cpp

dijkstra_tests.o: tests/Dijkstra_Tests.cpp $(GRAPH_FILES) $(ALGORITHM_FILES)
	$(CXX) $(CXXFLAGS) -o dijkstra_tests.o tests/Dijkstra_Tests.cpp

Betweenness_tests.o: tests/Betweenness_Centrality_Tests.cpp $(GRAPH_FILES) $(ALGORITHM_FILES)
	$(CXX) $(CXXFLAGS) -o Betweenness_tests.o tests/Betweenness_Centrality_Tests.cpp

catchmain.o: catch/catchmain.cpp catch/catch.hpp
	$(CXX) $(CXXFLAGS) catch/catchmain.cpp

# Clean Targets

clean:
	-rm -f *.o *.d $(EXENAME) test