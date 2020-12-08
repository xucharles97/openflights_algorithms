#include "../algorithms/Dijkstra.hpp"
#include "../graph/Graph.h"
#include "../graph/Edge.h"

#include "../catch/catch.hpp"
#include <vector>
#include <iostream>

TEST_CASE("Dijkstra get distance for unweighted simple graph", "[Dijkstra][Distance]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b"));

    Graph<std::string> graph(edges);
    double distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "b");

    REQUIRE(distance == 1.0);

    graph.insertEdge("b", "c");
    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "c");
    REQUIRE(distance == 2.0);

    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "c", "a");
    REQUIRE(distance == -1.0); //path doesn't exist b/c it's a directed graph

}

TEST_CASE("Dijkstra get distance for unweighted complex graph", "[Dijkstra][Distance]") {
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
    
    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "f", "e");
    REQUIRE(distance == 3.0);

    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "e", "f");
    REQUIRE(distance == -1.0); //path does not exist 
}

TEST_CASE("Dijkstra get path for unweighted single edge graph", "[Dijkstra][Path]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b"));

    Graph<std::string> graph(edges);
    std::vector<Edge<std::string>> path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "b");
    REQUIRE(path.size() == 1);
    auto iter = path.begin();
    REQUIRE((*iter).source == "a");
    REQUIRE((*iter).dest == "b");
    REQUIRE((*iter).getWeight() == 1);


    graph.insertEdge("b", "c");
    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "c");
    REQUIRE(path.size() == 2);
    iter = path.begin();
    REQUIRE((*iter).source == "a");
    REQUIRE((*iter).dest == "b");
    REQUIRE((*iter).getWeight() == 1);
    ++iter;

    REQUIRE((*iter).source == "b");
    REQUIRE((*iter).dest == "c");
    REQUIRE((*iter).getWeight() == 1);

    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "c");
    REQUIRE(path.size() == 0); //path doesn't exist b/c it's a directed graph

}


TEST_CASE("Dijkstra get path for unweighted complex graph", "[Dijkstra][Distance]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b"));
    edges.push_back(Edge<std::string>("b", "c"));
    edges.push_back(Edge<std::string>("c", "d"));
    edges.push_back(Edge<std::string>("a", "d"));


    Graph<std::string> graph(edges);
    std::vector<Edge<std::string>> path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "d");

    REQUIRE(path.size() == 1.0);
    auto iter = path.begin();
    REQUIRE((*iter).source == "a");
    REQUIRE((*iter).dest == "d");

    graph.insertEdge("f", "c");
    graph.insertEdge("d", "e");

    std::vector<pair<std::string, double>> weighted = graph.getAdjacentWeighted("f");
    // for (pair<std::string, double> edge : weighted) {
    //     std::cout << edge.first << std::endl;
    // }
    
    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "f", "e");
    REQUIRE(path.size() == 3.0);
    iter = path.begin();
    REQUIRE((*iter).source == "f");
    REQUIRE((*iter).dest == "c");
    REQUIRE((*iter).getWeight() == 1);
    ++iter;

    REQUIRE((*iter).source == "c");
    REQUIRE((*iter).dest == "d");
    REQUIRE((*iter).getWeight() == 1);
    ++iter;

    REQUIRE((*iter).source == "d");
    REQUIRE((*iter).dest == "e");
    REQUIRE((*iter).getWeight() == 1);

    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "e", "f");
    REQUIRE(path.size() == 0.0); //path does not exist 
}