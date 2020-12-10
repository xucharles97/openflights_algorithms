#include "graph/Edge.h"
#include "graph/Graph.h"
#include "graph/Parsing.hpp"
#include "algorithms/BetweenessCentrality.hpp"
#include <iostream>

int main() {
    std::string airportFile = "datasets/airports.txt";
    std::string routeFile = "datasets/routes.txt";
    Graph<std::string> graph = Parsing::buildGraphFromFiles<std::string>(airportFile, routeFile);

    std::string centralVertex = BetweenessCentrality::mostCentralVertex(graph);
    std::cout << "Central vertex: " << centralVertex << std::endl;
}