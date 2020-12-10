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

Graph<string> makeStickWithShortcutGraph() {
    vector<Edge<string>> strEdges;
    strEdges.push_back(Edge<string>("a", "b", 1));
    strEdges.push_back(Edge<string>("b", "a", 1));
    strEdges.push_back(Edge<string>("b", "c", 1));
    strEdges.push_back(Edge<string>("c", "b", 1));

    Graph<string> stringGraph(strEdges);

    return stringGraph;
}

Graph<string> makeNegWeightGraph() {
    vector<Edge<string>> strEdges;

    // TODO

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

// TEST_CASE("Betweeness Centrality Basic", "[Betweeness]") {
//     Graph<string> stringGraph = BetweenessTestHelpers::makeBasicGraph();

//     string centralVertex = mostCentralVertex(stringGraph);

//     REQUIRE(centralVertex == "a");
// }
