#include "graph/Graph.h"
#include "graph/Edge.h"
#include "graph/Parsing.hpp"

int main() {
    std::string airportFile = "datasets/airports.txt";
    std::string routeFile = "datasets/routes.txt";
    Graph<std::string> graph = Parsing::buildGraphFromFiles<std::string>(airportFile, routeFile);
}