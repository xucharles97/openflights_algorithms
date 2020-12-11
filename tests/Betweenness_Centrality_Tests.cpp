//
// Created by Madhav on 12/09/20.
//

#include <iostream>
#include <string>
#include <vector>

#include "../graph/Edge.h"
#include "../graph/Graph.h"

#include "../algorithms/BetweennessCentrality.hpp"

#include "../catch/catch.hpp"

using std::string;
using std::vector;

using BetweennessCentrality::mostCentralVertex;

namespace BetweennessTestHelpers {

Graph<string> makeWheelGraph() {
    vector<Edge<string>> strEdges;
    strEdges.push_back(Edge<string>("a", "c", 1));
    strEdges.push_back(Edge<string>("c", "a", 1));
    strEdges.push_back(Edge<string>("d", "c", 1));
    strEdges.push_back(Edge<string>("c", "d", 1));
    strEdges.push_back(Edge<string>("c", "b", 1));
    strEdges.push_back(Edge<string>("b", "c", 1));
    strEdges.push_back(Edge<string>("c", "e", 1));
    strEdges.push_back(Edge<string>("e", "c", 1));

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

Graph<string> makeStickGraph() {
    vector<Edge<string>> strEdges;
    strEdges.push_back(Edge<string>("a", "b", 1));
    strEdges.push_back(Edge<string>("b", "a", 1));
    strEdges.push_back(Edge<string>("b", "c", 1));
    strEdges.push_back(Edge<string>("c", "b", 1));

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

Graph<string> makeEmptyGraph() {
    vector<Edge<string>> strEdges;

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

} // namespace BetweennessTestHelpers

/////////////////////////////////////
////////////// BASIC ////////////////
/////////////////////////////////////

TEST_CASE("Betweenness Centrality Wheel", "[Betweenness]") {
    Graph<string> stringGraph = BetweennessTestHelpers::makeWheelGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    REQUIRE(centralVertex == "c");
}

TEST_CASE("Betweenness Centrality Stick", "[Betweenness]") {
    Graph<string> stringGraph = BetweennessTestHelpers::makeStickGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    REQUIRE(centralVertex == "b");
}

TEST_CASE("Betweenness Centrality Empty", "[Betweenness]") {
    Graph<string> stringGraph = BetweennessTestHelpers::makeEmptyGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    // Didn't crash!
    REQUIRE(centralVertex == ""); // Empty should return empty constructor of type
}
