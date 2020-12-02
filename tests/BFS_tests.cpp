//
// Created by Matt on 12/02/20.
//

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../traversals/BFS.hpp"

#include "../catch/catch.hpp"

#include <iostream>
#include <vector>

TEST_CASE("BFS BASIC")
{
    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b", 4));
    strEdges.push_back(Edge<std::string>("b", "c", 2));
    strEdges.push_back(Edge<std::string>("c", "d"));
    strEdges.push_back(Edge<std::string>("d", "b", 1.5));
    Graph<std::string> stringGraph(strEdges);
    
    BFS<std::string> t(stringGraph, stringGraph.getVertices()[1]);
    GraphTraversal<std::string>::Iterator it = t.begin();
    
    // while (it != t.end()) {
    //     std::cout << *it << std::endl;
    //     ++it;
    // }
    
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "d"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE(!(it != t.end()));
}