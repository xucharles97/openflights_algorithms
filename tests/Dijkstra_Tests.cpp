#include "../algorithms/Dijkstra.hpp"
#include "../graph/Graph.h"
#include "../graph/Edge.h"

#include "../catch/catch.hpp"
#include <vector>
#include <iostream>

TEST_CASE("DIJKSTRA UNWEIGHTED SINGLE EDGE GRAPH DISTANCE", "[Dijkstra]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b"));

    Graph<std::string> graph(edges);
    double distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "b");

    REQUIRE(distance == 1.0);

    graph.insertEdge("b", "c");
    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "c");

    REQUIRE(distance == 2.0);

}

TEST_CASE("DIJKSTRA UNWEIGHTED DIVERGING PATHS DISTANCE", "[Dijkstra]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b"));
    edges.push_back(Edge<std::string>("b", "c"));
    edges.push_back(Edge<std::string>("c", "d"));
    edges.push_back(Edge<std::string>("a", "d"));


    Graph<std::string> graph(edges);
    double distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "d");

    REQUIRE(distance == 1.0);

    graph.insertEdge("f", "c");
    graph.insertEdge("d", "e");
    // std::vector<std::string> vertices = graph.getVertices();
    // for (std::string str : vertices) {
    //     std::cout << str << std::endl;
    // }
    //     std::vector<Edge<std::string>> edgelist = graph.getEdges();
    // for (Edge<std::string> edge : edgelist) {
    //     std::cout << edge.source << " to " << edge.dest << std::endl;
    // }


    std::vector<pair<std::string, double>> weighted = graph.getAdjacentWeighted("f");
    // for (pair<std::string, double> edge : weighted) {
    //     std::cout << edge.first << std::endl;
    // }
    
    //distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "f", "c");
    //REQUIRE(distance == 1.0);

    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "e", "f");
    REQUIRE(distance == 3.0);




}
