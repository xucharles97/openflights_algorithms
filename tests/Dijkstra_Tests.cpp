#include "../algorithms/Dijkstra.hpp"
#include "../graph/Graph.h"
#include "../graph/Edge.h"

#include "../catch/catch.hpp"
#include <vector>
#include <iostream>

TEST_CASE("DIJKSTRA DISTANCE IN SINGLE EDGE GRAPH", "[Dijkstra]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b"));
    // edges.push_back(Edge<std::string>("b", "c"));
    // edges.push_back(Edge<std::string>("c", "d"));
    // edges.push_back(Edge<std::string>("a", "d"));

    Graph<std::string> graph(edges);
    // std::vector<std::string> vertices = graph.getVertices();
    // for (std::string str : vertices) {
    //     std::cout << str << std::endl;
    // }

    // std::vector<Edge<std::string>> edgelist = graph.getEdges();
    // for (Edge<std::string> edge : edgelist) {
    //     std::cout << edge.source << " to " << edge.dest << std::endl;
    // }
    double distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "b");

    REQUIRE(distance == 1.0);


}