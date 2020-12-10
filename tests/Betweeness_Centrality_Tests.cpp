//
// Created by Madhav on 12/09/20.
//

#include <iostream>
#include <string>
#include <vector>

#include "../graph/Edge.h"
#include "../graph/Graph.h"

#include "../algorithms/BetweenessCentrality.hpp"

#include "../catch/catch.hpp"

using std::string;
using std::vector;

using BetweenessCentrality::mostCentralVertex;

namespace BetweenessTestHelpers {

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

} // namespace BetweenessTestHelpers

/////////////////////////////////////
////////////// BASIC ////////////////
/////////////////////////////////////

TEST_CASE("Betweeness Centrality Wheel", "[Betweeness]") {
    Graph<string> stringGraph = BetweenessTestHelpers::makeWheelGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    REQUIRE(centralVertex == "c");
}

TEST_CASE("Betweeness Centrality Stick", "[Betweeness]") {
    Graph<string> stringGraph = BetweenessTestHelpers::makeStickGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    REQUIRE(centralVertex == "b");
}

TEST_CASE("Betweeness Centrality Empty", "[Betweeness]") {
    Graph<string> stringGraph = BetweenessTestHelpers::makeEmptyGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    // Didn't crash!
    REQUIRE(centralVertex == ""); // Empty should return empty constructor of type
}
