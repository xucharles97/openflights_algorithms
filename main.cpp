#include "algorithms/BetweennessCentrality.hpp"
#include "algorithms/Dijkstra.hpp"
#include "graph/Edge.h"
#include "graph/Graph.h"
#include "graph/Parsing.hpp"
#include <iostream>
#include <random>

using std::string;

//////////////////////////////////////////////////
///////////// FORWARD DECLARATIONS ///////////////
//////////////////////////////////////////////////

Graph<string> buildGraph(string airportsFileName, string routesFileName) {

    std::cout << "Building graph from airports data at " << airportsFileName
              << " and routes data at " << routesFileName << std::endl;

    Graph<string> graph = Parsing::buildGraphFromFiles<string>(airportsFileName, routesFileName);

    std::cout << "Finished building graph! There were " << graph.getVertices().size()
              << " airports and " << graph.getEdges().size() << " routes between them."
              << std::endl;
    std::cout << std::endl;

    return graph;
}

void runDijkstras(Graph<string>& graph) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, graph.getVertices().size() - 1);

    string dijkstraSource = graph.getVertices()[dis(gen)];

    std::cout << "Running Dijkstra's Algorithm for airport " << dijkstraSource << std::endl;
    std::cout << std::endl;

    Dijkstra::printDijkstraData(graph, dijkstraSource);
    std::cout << "Finished running Dijkstra's Algorithm for airport " << dijkstraSource
              << std::endl;
    std::cout << std::endl;
    Dijkstra::printShortestDijkstraDistance(graph, dijkstraSource, graph.getVertices()[dis(gen)]);
    Dijkstra::printShortestDijkstraPath(graph, dijkstraSource, graph.getVertices()[dis(gen)]);
    std::cout << std::endl;
}

void runBetweennessCentrality(Graph<string>& graph) {
    std::cout << "Computing the most central airport. Hold on! This can take a while..."
              << std::endl;

    string centralVertex = BetweennessCentrality::mostCentralVertex(graph);

    std::cout << "Most Central Airport: " << centralVertex << std::endl;
    std::cout << "This means that " << centralVertex
              << " is most likely to be part of the shortest route between 2 other airports."
              << std::endl;
}

//////////////////////////////////////////////////
//////////////// DRIVER FUNCTION /////////////////
//////////////////////////////////////////////////

int main() {
    string airportFile = "datasets/airports.txt";
    string routeFile = "datasets/routes.txt";

    Graph<string> graph = buildGraph(airportFile, routeFile);

    runDijkstras(graph);
    runBetweennessCentrality(graph);
    std::cout << std::endl;
}
