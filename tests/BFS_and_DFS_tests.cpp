//
// Created by Matt on 12/02/20.
//

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../traversals/BFS.hpp"
#include "../traversals/DFS.hpp"

#include "../catch/catch.hpp"
#include <vector>

TEST_CASE("BFS_BASIC", "[BFS]")
{
    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b", 4));
    strEdges.push_back(Edge<std::string>("b", "c", 2));
    strEdges.push_back(Edge<std::string>("c", "d"));
    strEdges.push_back(Edge<std::string>("d", "b", 1.5));
    Graph<std::string> stringGraph(strEdges);
    
    BFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();
    
    // while (it != t.end()) {
    //     std::cout << *it << std::endl;
    //     ++it;
    // }
    
	REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "d"); ++it;
    REQUIRE(!(it != t.end()));
}

TEST_CASE("BFS_TREE_TEST", "[BFS]") {
	std::vector<Edge<std::string>> strEdges;
	strEdges.push_back(Edge<std::string>("a", "b"));
	strEdges.push_back(Edge<std::string>("a", "c"));
	strEdges.push_back(Edge<std::string>("b", "d"));
	strEdges.push_back(Edge<std::string>("b", "e"));
	strEdges.push_back(Edge<std::string>("c", "f"));
	strEdges.push_back(Edge<std::string>("c", "g"));
	Graph<std::string> stringGraph(strEdges);
    
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

TEST_CASE("BFS_CIRCULAR_TEST", "[BFS]") {
	std::vector<Edge<std::string>> strEdges;
	strEdges.push_back(Edge<std::string>("a", "b"));
	strEdges.push_back(Edge<std::string>("b", "c"));
	strEdges.push_back(Edge<std::string>("c", "d"));
	strEdges.push_back(Edge<std::string>("d", "a"));
	Graph<std::string> stringGraph(strEdges);
    
    BFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

	REQUIRE((*it) == "a"); ++it;
	REQUIRE((*it) == "b"); ++it;
	REQUIRE((*it) == "c"); ++it;
	REQUIRE((*it) == "d"); ++it;

    REQUIRE(!(it != t.end()));
}

TEST_CASE("DFS BASIC", "[DFS]")
{
    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b", 4));
    strEdges.push_back(Edge<std::string>("b", "c", 2));
    strEdges.push_back(Edge<std::string>("c", "d"));
    strEdges.push_back(Edge<std::string>("d", "b", 1.5));
    Graph<std::string> stringGraph(strEdges);
    
    DFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();
    
    // while (it != t.end()) {
    //     std::cout << *it << std::endl;
    //     ++it;
    // }
   
    REQUIRE((*it) == "a"); ++it;
    REQUIRE((*it) == "b"); ++it;
    REQUIRE((*it) == "c"); ++it;
    REQUIRE((*it) == "d"); ++it;
    REQUIRE(!(it != t.end()));
}

TEST_CASE("DFS_TREE_TEST", "[DFS]") {
	std::vector<Edge<std::string>> strEdges;
	strEdges.push_back(Edge<std::string>("a", "b"));
	strEdges.push_back(Edge<std::string>("a", "c"));
	strEdges.push_back(Edge<std::string>("b", "d"));
	strEdges.push_back(Edge<std::string>("b", "e"));
	strEdges.push_back(Edge<std::string>("c", "f"));
	strEdges.push_back(Edge<std::string>("c", "g"));
	Graph<std::string> stringGraph(strEdges);
    
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

TEST_CASE("DFS_CIRCULAR_TEST", "[DFS]") {
	std::vector<Edge<std::string>> strEdges;
	strEdges.push_back(Edge<std::string>("a", "b"));
	strEdges.push_back(Edge<std::string>("b", "c"));
	strEdges.push_back(Edge<std::string>("c", "d"));
	strEdges.push_back(Edge<std::string>("d", "a"));
	Graph<std::string> stringGraph(strEdges);
    
    DFS<std::string> t(stringGraph, "a");
    GraphTraversal<std::string>::Iterator it = t.begin();

	REQUIRE((*it) == "a"); ++it;
	REQUIRE((*it) == "b"); ++it;
	REQUIRE((*it) == "c"); ++it;
	REQUIRE((*it) == "d"); ++it;

    REQUIRE(!(it != t.end()));
}