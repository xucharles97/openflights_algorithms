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

Graph<string> makeStickWithShortcutGraph() {
    vector<Edge<string>> strEdges;
    strEdges.push_back(Edge<string>("a", "b", 1));
    strEdges.push_back(Edge<string>("b", "c", 1));
    strEdges.push_back(Edge<string>("c", "d", 1));
    strEdges.push_back(Edge<string>("d", "e", 1));
    strEdges.push_back(Edge<string>("a", "e", 3)); // A shortcut

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

Graph<string> makeTreeGraph() {
    vector<Edge<string>> strEdges;
    strEdges.push_back(Edge<string>("a", "b", 1));
    strEdges.push_back(Edge<string>("b", "e", 2));
    strEdges.push_back(Edge<string>("a", "c", 3));
    strEdges.push_back(Edge<string>("c", "d", 4));

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

Graph<string> makeNegWeightGraph() {
    vector<Edge<string>> strEdges;
    strEdges.push_back(Edge<string>("a", "d", 10));
    strEdges.push_back(Edge<string>("a", "c", 15));
    strEdges.push_back(Edge<string>("a", "b", 25));
    strEdges.push_back(Edge<string>("b", "e", -10));
    strEdges.push_back(Edge<string>("b", "c", 5));
    strEdges.push_back(Edge<string>("c", "e", 3));
    strEdges.push_back(Edge<string>("c", "f", -7));
    strEdges.push_back(Edge<string>("d", "f", 15));

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

/////////////////////////////////////
////////////// BASIC ////////////////
/////////////////////////////////////

TEST_CASE("Shortest Distance Basic", "[Distance]") {
    Graph<string> stringGraph = makeBasicGraph();

    unordered_map<string, unordered_map<string, double>> shortestDistances =
        shortestDistanceBetweenAllVertices(stringGraph);

    REQUIRE(shortestDistances["a"]["a"] == 0);
    REQUIRE(shortestDistances["a"]["c"] == 8);
    REQUIRE(shortestDistances["d"]["b"] == 7);
}

TEST_CASE("Shortest Path Basic #1", "[Path]") {
    Graph<string> stringGraph = makeBasicGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "a", "a");

    // From A to A
    REQUIRE(shortestPath[0] == "a");
}

TEST_CASE("Shortest Path Basic #2", "[Path]") {
    Graph<string> stringGraph = makeBasicGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "a", "c");

    // From A to C
    REQUIRE(shortestPath[0] == "a");
    REQUIRE(shortestPath[1] == "b");
    REQUIRE(shortestPath[2] == "d");
    REQUIRE(shortestPath[3] == "c");
}

TEST_CASE("Shortest Path Basic #3", "[Path]") {
    Graph<string> stringGraph = makeBasicGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "d", "b");

    // From D to B
    REQUIRE(shortestPath[0] == "d");
    REQUIRE(shortestPath[1] == "c");
    REQUIRE(shortestPath[2] == "b");
}

/////////////////////////////////////
////////////// STICK ////////////////
/////////////////////////////////////

TEST_CASE("Shortest Distance Stick With Shortcut", "[Distance]") {
    Graph<string> stringGraph = makeStickWithShortcutGraph();

    unordered_map<string, unordered_map<string, double>> shortestDistances =
        shortestDistanceBetweenAllVertices(stringGraph);

    REQUIRE(shortestDistances["a"]["e"] == 3);
    REQUIRE(shortestDistances["b"]["e"] == 3);
}

TEST_CASE("Shortest Path Stick With Shortcut #1", "[Path]") {
    Graph<string> stringGraph = makeStickWithShortcutGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "a", "e");

    // From A to E
    REQUIRE(shortestPath[0] == "a");
    REQUIRE(shortestPath[1] == "e");
}

TEST_CASE("Shortest Path Stick With Shortcut #2", "[Path]") {
    Graph<string> stringGraph = makeStickWithShortcutGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "b", "e");

    // From B to E
    REQUIRE(shortestPath[0] == "b");
    REQUIRE(shortestPath[1] == "c");
    REQUIRE(shortestPath[2] == "d");
    REQUIRE(shortestPath[3] == "e");
}

/////////////////////////////////////
////////////// TREE /////////////////
/////////////////////////////////////

TEST_CASE("Shortest Distance Tree", "[Distance]") {
    Graph<string> stringGraph = makeTreeGraph();

    unordered_map<string, unordered_map<string, double>> shortestDistances =
        shortestDistanceBetweenAllVertices(stringGraph);

    REQUIRE(shortestDistances["a"]["e"] == 3);
    REQUIRE(shortestDistances["a"]["d"] == 7);
}

TEST_CASE("Shortest Path Tree #1", "[Path]") {
    Graph<string> stringGraph = makeTreeGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "a", "e");

    // From A to E
    REQUIRE(shortestPath[0] == "a");
    REQUIRE(shortestPath[1] == "b");
    REQUIRE(shortestPath[2] == "e");
}

TEST_CASE("Shortest Path Tree #2", "[Path]") {
    Graph<string> stringGraph = makeTreeGraph();

    std::vector<string> shortestPath =
        shortestPathBetweenTwoVertices<string>(stringGraph, "c", "d");

    // From C to D
    REQUIRE(shortestPath[0] == "c");
    REQUIRE(shortestPath[1] == "d");
}

////////////////////////////////////////////////
////////////// NEGATIVE WEIGHT /////////////////
////////////////////////////////////////////////

////////////////////////////////////////////////
///////////////// EDGE CASES ///////////////////
////////////////////////////////////////////////