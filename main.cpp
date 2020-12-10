#include "algorithms/BetweenessCentrality.hpp"
#include "graph/Edge.h"
#include "graph/Graph.h"
#include "graph/Parsing.hpp"
#include <iostream>

int main() {
    std::string airportFile = "datasets/airports.txt";
    std::string routeFile = "datasets/routes.txt";

    std::cout << "Building graph from airports data at " << airportFile << " and routes data at "
              << routeFile << std::endl;

    Graph<std::string> graph = Parsing::buildGraphFromFiles<std::string>(airportFile, routeFile);

    std::cout << "Finished building graph! There were " << graph.getVertices().size()
              << " airports and " << graph.getEdges().size() << " routes between them."
              << std::endl;

    std::cout << "Computing the most central airport. Hold on! This can take a while..."
              << std::endl;

    std::string centralVertex = BetweenessCentrality::mostCentralVertex(graph);

    std::cout << "Most Central Airport: " << centralVertex << std::endl;
    std::cout << "This means that " << centralVertex
              << " is most likely to be part of the shortest route between 2 other airports."
              << std::endl;
}
