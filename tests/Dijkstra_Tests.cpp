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
    
    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "f", "e");
    std::vector<Edge<std::string>> path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "f", "e");
    REQUIRE(distance == 3.0);

    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "e", "f");
    REQUIRE(distance == -1.0); //path does not exist 
}

TEST_CASE("Dijkstra get distance for weighted simple graph", "[Dijkstra][Distance]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b", 3));

    Graph<std::string> graph(edges);
    double distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "b");

    REQUIRE(distance == 3.0);

    graph.insertEdge("b", "c", 2);
    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "c");
    REQUIRE(distance == 5.0);

    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "c", "a");
    REQUIRE(distance == -1.0); //path doesn't exist b/c it's a directed graph

}

TEST_CASE("Dijkstra get distance for weighted complex graph", "[Dijkstra][Distance]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b", 2));
    edges.push_back(Edge<std::string>("b", "c", 1.5));
    edges.push_back(Edge<std::string>("c", "d", 3));
    edges.push_back(Edge<std::string>("a", "d", 10));


    Graph<std::string> graph(edges);
    double distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "d");
    REQUIRE(distance == 6.5);

    graph.insertEdge("f", "c", 0.5);
    graph.insertEdge("d", "e", 2.1);
    
    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "f", "e");
    std::vector<Edge<std::string>> path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "f", "e");
    REQUIRE(distance == 5.6);

    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "e", "f");
    REQUIRE(distance == -1.0); //path does not exist 

    graph.insertEdge("a", "f", 0.7);
    distance = Dijkstra::getDistanceBetweenPoints<std::string>(graph, "a", "f");
    REQUIRE(distance == 0.7);

    
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

    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "c", "a");
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

TEST_CASE("Dijkstra get path for weighted single edge graph", "[Dijkstra][Path]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b", 1.9));

    Graph<std::string> graph(edges);
    std::vector<Edge<std::string>> path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "b");
    REQUIRE(path.size() == 1);
    auto iter = path.begin();
    REQUIRE((*iter).source == "a");
    REQUIRE((*iter).dest == "b");
    REQUIRE((*iter).getWeight() == 1.9);


    graph.insertEdge("b", "c", 0.3);
    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "c");
    REQUIRE(path.size() == 2);
    iter = path.begin();
    REQUIRE((*iter).source == "a");
    REQUIRE((*iter).dest == "b");
    REQUIRE((*iter).getWeight() == 1.9);
    ++iter;

    REQUIRE((*iter).source == "b");
    REQUIRE((*iter).dest == "c");
    REQUIRE((*iter).getWeight() == 0.3);

    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "c", "a");
    REQUIRE(path.size() == 0); //path doesn't exist b/c it's a directed graph

}

TEST_CASE("Dijkstra get path for weighted complex graph", "[Dijkstra][Distance]") {
    std::vector<Edge<std::string>> edges;

    edges.push_back(Edge<std::string>("a", "b", 0.3));
    edges.push_back(Edge<std::string>("b", "c", 1.3));
    edges.push_back(Edge<std::string>("c", "d", 2.4));
    edges.push_back(Edge<std::string>("a", "d", 5.9));


    Graph<std::string> graph(edges);
    std::vector<Edge<std::string>> path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "d");

    REQUIRE(path.size() == 3.0);
    auto iter = path.begin();
    REQUIRE((*iter).source == "a");
    REQUIRE((*iter).dest == "b");
    REQUIRE((*iter).getWeight() == 0.3);
    ++iter;

    REQUIRE((*iter).source == "b");
    REQUIRE((*iter).dest == "c");
    REQUIRE((*iter).getWeight() == 1.3);
    ++iter;

    REQUIRE((*iter).source == "c");
    REQUIRE((*iter).dest == "d");
    REQUIRE((*iter).getWeight() == 2.4);
    ++iter;


    graph.insertEdge("f", "c", 10.1);
    graph.insertEdge("d", "e", 3.9);
    
    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "f", "e");

    REQUIRE(path.size() == 3.0);
    iter = path.begin();
    REQUIRE((*iter).source == "f");
    REQUIRE((*iter).dest == "c");
    REQUIRE((*iter).getWeight() == 10.1);
    ++iter;

    REQUIRE((*iter).source == "c");
    REQUIRE((*iter).dest == "d");
    REQUIRE((*iter).getWeight() == 2.4);
    ++iter;

    REQUIRE((*iter).source == "d");
    REQUIRE((*iter).dest == "e");
    REQUIRE((*iter).getWeight() == 3.9);

    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "e", "f");
    REQUIRE(path.size() == 0.0); //path does not exist 
    
    graph.insertEdge("a", "c", 1.5);
    path = Dijkstra::getPathBetweenPoints<std::string, Edge<std::string>>(graph, "a", "d");
    REQUIRE(path.size() == 2.0);
    iter = path.begin();
    REQUIRE((*iter).source == "a");
    REQUIRE((*iter).dest == "c");
    REQUIRE((*iter).getWeight() == 1.5);
    ++iter;

    REQUIRE((*iter).source == "c");
    REQUIRE((*iter).dest == "d");
    REQUIRE((*iter).getWeight() == 2.4);

}