//
// Created by Matt on 12/02/20.
//

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../traversals/BFS.hpp"
#include "../traversals/DFS.hpp"

#include "../catch/catch.hpp"
#include <vector>

Graph<std::string> makeBasicGraph() {
    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b", 4));
    strEdges.push_back(Edge<std::string>("b", "c", 2));
    strEdges.push_back(Edge<std::string>("c", "d"));
    strEdges.push_back(Edge<std::string>("d", "b", 1.5));
    return Graph<std::string>(strEdges);
}

Graph<std::string> makeTreeGraph() {
    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b"));
    strEdges.push_back(Edge<std::string>("a", "c"));
    strEdges.push_back(Edge<std::string>("b", "d"));
    strEdges.push_back(Edge<std::string>("b", "e"));
    strEdges.push_back(Edge<std::string>("c", "f"));
    strEdges.push_back(Edge<std::string>("c", "g"));
    return Graph<std::string>(strEdges);
}

Graph<std::string> makeCircularGraph() {
    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b"));
    strEdges.push_back(Edge<std::string>("b", "c"));
    strEdges.push_back(Edge<std::string>("c", "d"));
    strEdges.push_back(Edge<std::string>("d", "a"));
    return Graph<std::string>(strEdges);
}

Graph<std::string> makeEmptyGraph() {
    std::vector<Edge<std::string>> strEdges;
    return Graph<std::string>(strEdges);
}

TEST_CASE("BFS_BASIC", "[BFS][BASIC]") {
    Graph<std::string> stringGraph = makeBasicGraph();

    BFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

    REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "d"); ++it;
    REQUIRE(!(it != t.end()));
}

TEST_CASE("BFS_TREE_TEST", "[BFS][TREE]") {
    Graph<std::string> stringGraph = makeTreeGraph();

    BFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

    REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "g"); ++it;
    REQUIRE((*it) == "f"); ++it;
    REQUIRE((*it) == "e"); ++it;
    REQUIRE((*it) == "d"); ++it;

    REQUIRE(!(it != t.end()));
}

TEST_CASE("BFS_CIRCULAR_TEST", "[BFS][CIRCULAR]") {
    Graph<std::string> stringGraph = makeCircularGraph();

    BFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

    REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "d"); ++it;

    REQUIRE(!(it != t.end()));
}

TEST_CASE("BFS_EMPTY_TEST", "[BFS][EMPTY]") {
    Graph<std::string> stringGraph = makeEmptyGraph();

    BFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();
    
    REQUIRE(!(it != t.end()));
}

TEST_CASE("DFS BASIC", "[DFS][BASIC]") {
    Graph<std::string> stringGraph = makeBasicGraph();

    DFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

    REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "d"); ++it;
    REQUIRE(!(it != t.end()));
}

TEST_CASE("DFS_TREE_TEST", "[DFS][TREE]") {
    Graph<std::string> stringGraph = makeTreeGraph();

    DFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

    REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "d"); ++it;
    REQUIRE((*it) == "e"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "f"); ++it;
    REQUIRE((*it) == "g"); ++it;

    REQUIRE(!(it != t.end()));
}

TEST_CASE("DFS_CIRCULAR_TEST", "[DFS][CIRCULAR]") {
    Graph<std::string> stringGraph = makeCircularGraph();

    DFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

    REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "d"); ++it;

    REQUIRE(!(it != t.end()));
}

TEST_CASE("DFS_EMPTY_TEST", "[DFS][EMPTY]") {
    Graph<std::string> stringGraph = makeEmptyGraph();

    DFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

    REQUIRE(!(it != t.end()));
}