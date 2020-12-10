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

} // namespace BetweenessTestHelpers

/////////////////////////////////////
////////////// BASIC ////////////////
/////////////////////////////////////

TEST_CASE("Betweeness Centrality Basic", "[Betweeness]") {
    Graph<string> stringGraph = BetweenessTestHelpers::makeBasicGraph();

    string centralVertex = mostCentralVertex(stringGraph);

    REQUIRE(centralVertex == "a");
}
