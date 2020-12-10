//
// Created by elia on 11/29/20.
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

TEST_CASE("EDGES WORK WITH INT") {
    Edge<int> e1(0, 1, 0.5);
    Edge<int> e2(0, 1, 3);
    REQUIRE(e1.getWeight() == 0.5);
    REQUIRE(e1 == e2);
    REQUIRE(e1 < e2);
}

TEST_CASE("GRAPH CONSTRUCTOR WORKS") {
    std::vector<Edge<int>> edges;
    edges.push_back(Edge<int>(0, 1, 0.5));
    edges.push_back(Edge<int>(1, 2));
    edges.push_back(Edge<int>(2, 0, 3));
    Graph<int> g(edges);
    REQUIRE(g.edgeExists(1, 2));
    REQUIRE(g.getEdgeWeight(0, 1) == 0.5);

    std::vector<Edge<std::string>> strEdges;
    strEdges.push_back(Edge<std::string>("a", "b", 4));
    strEdges.push_back(Edge<std::string>("b", "c", 2));
    strEdges.push_back(Edge<std::string>("c", "d"));
    strEdges.push_back(Edge<std::string>("d", "b", 1.5));
    Graph<std::string> gString(strEdges);
    std::vector<std::string> expectedOutput1 = {"d", "b", "c", "a"};
    int i = 0;
    for (auto v : gString.getVertices()) {
        // std::cout << v << std::endl;
        REQUIRE(expectedOutput1[i] == v);
        i++;
    }
    std::vector<std::string> expectedOutput2 = {
        "source: d dest: b weight: 1.500000", "source: b dest: c weight: 2.000000",
        "source: c dest: d weight: 1.000000", "source: a dest: b weight: 4.000000"};
    i = 0;
    for (auto e : gString.getEdges()) {
        std::string actualOutput = std::string("source: ") + e.source + " dest: " + e.dest +
                                   " weight: " + std::to_string(e.getWeight());
        REQUIRE(actualOutput == expectedOutput2[i]);
        i++;
    }
}

TEST_CASE("READING GRAPHS WORKS") {
    unordered_map<std::string, std::pair<double, double>> airports =
        readAirportsFromFile("datasets/airports.txt");
    // for (auto elem : airports) {
    //     std::cout << "airport: " << elem.first << "lat: " << elem.second.first
    //               << "long: " << elem.second.second << std::endl;
    // }
}
