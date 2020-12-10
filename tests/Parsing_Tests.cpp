//
// Created by elia on 12/10/20.
//

#include "../catch/catch.hpp"
#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../graph/MathFunctions.hpp"
#include "../graph/Parsing.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>

using Parsing::buildGraphFromFile;
using Parsing::buildGraphFromFiles;
using Parsing::readAirportsFromFile;
using Parsing::readRoutesFromFile;

TEST_CASE("LATLNG MATH CALCULATIONS WORK") {
    REQUIRE((int) distanceLatLng(55.223, 53.543, -33.43, -101.22) == 16903);
}

TEST_CASE("PARSING WORKS") {
unordered_map<std::string, std::pair<double, double>> airports =
        readAirportsFromFile("datasets/airports.txt");
REQUIRE((airports.find("GKA") != airports.end()) == true);
REQUIRE(airports["GKA"].first == -6.081689834590001);
REQUIRE(airports["GKA"].second == 145.391998291);

std::vector<Edge<std::string>> routes = readRoutesFromFile<std::string>("datasets/routes.txt", airports);
REQUIRE(routes.size() != 0);
REQUIRE((routes[0] == Edge<std::string>("AER", "KZN")) == true);
REQUIRE((routes[routes.size() - 1] == Edge<std::string>("OSS", "FRU")) == true);
}

TEST_CASE("BUILDING GRAPH FROM PARSED DATA WORKS") {
Graph<std::string> g = buildGraphFromFiles<std::string>("datasets/airports.txt", "datasets/routes.txt");
REQUIRE(g.edgeExists("AER", "KZN"));
}