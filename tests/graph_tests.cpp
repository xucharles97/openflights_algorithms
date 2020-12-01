//
// Created by elia on 11/29/20.
//

#include "../graph/Edge.h"
#include "../graph/Graph.h"

#include "../catch/catch.hpp"

#include <iostream>
#include <vector>

TEST_CASE("GRAPH CONSTRUCTOR WORKS")
{
    std::vector<int> v;
    std::vector<Edge<int>> edges;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    edges.push_back(Edge<int>(0, 1, 0.5));
    edges.push_back(Edge<int>(1, 2));
    edges.push_back(Edge<int>(2, 0, 3));
    Graph<int> g(v, edges);
    REQUIRE(g.edgeExists(1, 2));
    REQUIRE(g.getEdgeWeight(0, 1) == 0.5);
    std::cout << "FIRST SHITTY TEST DONE WILL FIX LATER BUT WANT TO MAKE SURE THIS WORKS FOR THE MOST PART" << std::endl;
}