//
// Created by elia on 11/29/20.
//

#include "../graph/Edge.h"
#include "../graph/Graph.h"

#include "../catch/catch.hpp"

#include <iostream>
#include <vector>

TEST_CASE("EDGES WORK WITH INT")
{
    Edge<int> e1(0, 1, 0.5);
    Edge<int> e2(0, 1, 3);
    REQUIRE(e1.getWeight() == 0.5);
    REQUIRE(e1 == e2);
    REQUIRE(e1 < e2);
}

TEST_CASE("GRAPH CONSTRUCTOR WORKS")
{
    std::vector<Edge<int>> edges;
    edges.push_back(Edge<int>(0, 1, 0.5));
    edges.push_back(Edge<int>(1, 2));
    edges.push_back(Edge<int>(2, 0, 3));
    Graph<int> g(edges);
    REQUIRE(g.edgeExists(1, 2));
    REQUIRE(g.getEdgeWeight(0, 1) == 0.5);

    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b", 4));
    strEdges.push_back(Edge<std::string>("b", "c", 2));
    strEdges.push_back(Edge<std::string>("c", "d"));
    strEdges.push_back(Edge<std::string>("d", "b", 1.5));
    Graph<std::string> gString(strEdges);
    for (auto v : gString.getVertices()) {
        std::cout << v << std::endl;
    }
    for (auto e : gString.getEdges()) {
        std::cout << "source: " << e.source << " dest: " << e.dest << " weight: " << e.getWeight() << std::endl;
    }
}