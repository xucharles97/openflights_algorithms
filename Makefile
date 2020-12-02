#!/bin/bash
EXENAME = final
GRAPH_OBJS = graph.o

SHELL := /bin/bash # Use bash syntax

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
CXXBASICFLAGS = -g -Wall
LD = clang++
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
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

test: test.o catchmain.o
	$(CXX) $(LDFLAGS) -o test graph_tests.o BFS_and_DFS_tests.o catchmain.o

test.o: tests/graph_tests.cpp tests/BFS_and_DFS_tests.cpp traversals/BFS.hpp traversals/DFS.hpp traversals/GraphTraversal.hpp graph/Graph.h graph/Edge.h
	$(CXX) $(CXXFLAGS) tests/graph_tests.cpp tests/BFS_and_DFS_tests.cpp

catchmain.o: catch/catchmain.cpp catch/catch.hpp
	$(CXX) $(CXXFLAGS) -c catch/catchmain.cpp

clean:
	-rm -f *.o $(EXENAME) test