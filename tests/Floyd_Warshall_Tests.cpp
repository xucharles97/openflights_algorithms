//
// Created by Madhav on 12/06/20.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../graph/Edge.h"
#include "../graph/Graph.h"

#include "../algorithms/FloydWarshall.hpp"

#include "../catch/catch.hpp"

using std::string;
using std::unordered_map;
using std::vector;

using FloydWarshall::shortestDistanceBetweenAllVertices;
using FloydWarshall::shortestPathBetweenAllVertices;
using FloydWarshall::shortestPathBetweenTwoVertices;

Graph<string> makeBasicGraph() {
    vector<Edge<string>> strEdges;
    strEdges.push_back(Edge<string>("a", "b", 5));
    strEdges.push_back(Edge<string>("b", "d", 1));
    strEdges.push_back(Edge<string>("d", "c", 2));
    strEdges.push_back(Edge<string>("b", "c", 5));
    strEdges.push_back(Edge<string>("c", "b", 5));

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

TEST_CASE("Shortest Distance Basic", "[Distance]") {
    Graph<string> stringGraph = makeBasicGraph();

    unordered_map<string, unordered_map<string, double>> shortestDistances =
        shortestDistanceBetweenAllVertices(stringGraph);

    REQUIRE(shortestDistances["a"]["a"] == 0);
    REQUIRE(shortestDistances["a"]["c"] == 8);
    REQUIRE(shortestDistances["d"]["b"] == 7);
}

TEST_CASE("Shortest Path Between Two Basic #1", "[Path]") {
    Graph<string> stringGraph = makeBasicGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "a", "a");

    // From A to A
    REQUIRE(shortestPath[0] == "a");
}

TEST_CASE("Shortest Path Between Two Basic #2", "[Path]") {
    Graph<string> stringGraph = makeBasicGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "a", "c");

    // From A to C
    REQUIRE(shortestPath[0] == "a");
    REQUIRE(shortestPath[1] == "b");
    REQUIRE(shortestPath[2] == "d");
    REQUIRE(shortestPath[3] == "c");
}

TEST_CASE("Shortest Path Between Two Basic #3", "[Path]") {
    Graph<string> stringGraph = makeBasicGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "d", "b");

    // From D to B
    REQUIRE(shortestPath[0] == "d");
    REQUIRE(shortestPath[1] == "c");
    REQUIRE(shortestPath[2] == "b");
}
