#include "algorithms/BetweenessCentrality.hpp"
#include "algorithms/Dijkstra.hpp"
#include "graph/Edge.h"
#include "graph/Graph.h"
#include "graph/Parsing.hpp"
#include <iostream>
#include <random>

int main() {
    std::string airportFile = "datasets/airports.txt";
    std::string routeFile = "datasets/routes.txt";

    std::cout << "Building graph from airports data at " << airportFile << " and routes data at "
              << routeFile << std::endl;

    Graph<std::string> graph = Parsing::buildGraphFromFiles<std::string>(airportFile, routeFile);

    std::cout << "Finished building graph! There were " << graph.getVertices().size()
              << " airports and " << graph.getEdges().size() << " routes between them."
              << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, graph.getVertices().size() - 1);

    std::string dijkstraSource = graph.getVertices()[dis(gen)];

    std::cout << "Running Dijkstra's Algorithm for airport " << dijkstraSource
              << std::endl;
    
    Dijkstra::printDijkstraData(graph, dijkstraSource);
    std::cout << "Finished running Dijkstra's Algorithm for airport " << dijkstraSource
              << std::endl;
    Dijkstra::printShortestDijkstraDistance(graph, dijkstraSource, graph.getVertices()[dis(gen)]);
    Dijkstra::printShortestDijkstraPath(graph, dijkstraSource, graph.getVertices()[dis(gen)]);

    std::cout << "Computing the most central airport. Hold on! This can take a while..."
              << std::endl;

    std::string centralVertex = BetweenessCentrality::mostCentralVertex(graph);

    std::cout << "Most Central Airport: " << centralVertex << std::endl;
    std::cout << "This means that " << centralVertex
              << " is most likely to be part of the shortest route between 2 other airports."
              << std::endl;
}
