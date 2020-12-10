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
    strEdges.push_back(Edge<string>("a", "c", 1));

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

Graph<string> makeEmptyGraph() {
    vector<Edge<string>> strEdges;

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

} // namespace BetweenessTestHelpers

/////////////////////////////////////
////////////// BASIC ////////////////
/////////////////////////////////////

TEST_CASE("Betweeness Centrality Basic", "[Betweeness]") {
    Graph<string> stringGraph = BetweenessTestHelpers::makeBasicGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    REQUIRE(centralVertex == "a");
}
