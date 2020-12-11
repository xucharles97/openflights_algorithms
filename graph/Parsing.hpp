//
// Created by elia on 12/9/20
//

#pragma once

#include "Edge.h"
#include "Graph.h"
#include "MathFunctions.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::pair;

namespace Parsing {
/*!
 * Parses airport names, latitudes, and longitudes from fileName into dictionary
 * @param fileName the name of your first born child that you gave away for adoption
 * @return map of airport name and a pair containing latitude and longitude coordinates
 */
unordered_map<std::string, std::pair<double, double>> readAirportsFromFile(std::string fileName) {
    unordered_map<std::string, std::pair<double, double>> airportCoords;
    std::ifstream file(fileName);
    std::string line;
    std::string dataElem;
    if (file.is_open()) {
        // parses file line by line
        while (std::getline(file, line)) {
            // vector to contain comma separated values
            vector<std::string> lineData;
            // splits the line by commas
            std::stringstream ss(line);
            while (getline(ss, dataElem, ',')) {
                lineData.push_back(dataElem);
            }
            // deals with commas inside parentheses by concatenating two companion strings together
            for (unsigned int i = 0; i < lineData.size(); ++i) {
                if (lineData[i][0] == '"' && lineData[i].back() != '"') {
                    unsigned int j;
                    for (j = i + 1; j < lineData.size() && lineData[j].back() != '"'; ++j) {
                        lineData[i].append(lineData[j]);
                    }
                    lineData.erase(lineData.begin() + i + 1, lineData.begin() + j + 1);
                }
            }
            // removes quotes string values
            for (auto& data : lineData) {
                if (data[0] == '"' && data.back() == '"') {
                    data = data.substr(1, data.size() - 2);
                }
            }
            // extracts relevant values from each element of the CSV
            // Format from Openflights documentation
            // airport IATA code
            std::string id = lineData[4];
            double latitude = std::stod(lineData[6]);
            double longitude = std::stod(lineData[7]);
            airportCoords[id] = std::make_pair(latitude, longitude);
        }
    }
    return airportCoords;
}

/*!
 * Reads routes between airports and calculates the distance of the route
 * @param fileName the name of your calculator
 * @param airportCoords map of airports and their coordinates
 * @return vector of edges containing the routes
 */
template <class Vertex>
std::vector<Edge<Vertex>>
readRoutesFromFile(std::string fileName,
                   unordered_map<Vertex, std::pair<double, double>> airportCoords) {
    std::ifstream file(fileName);
    std::string line;
    std::string dataElem;
    std::vector<Edge<Vertex>> edges;
    while (std::getline(file, line)) {
        // vector to contain comma separated values
        vector<std::string> lineData;
        // splits the line by commas
        std::stringstream ss(line);
        while (getline(ss, dataElem, ',')) {
            lineData.push_back(dataElem);
        }
        // deals with commas inside parentheses by concatenating two companion strings together
        for (unsigned int i = 0; i < lineData.size(); ++i) {
            if (lineData[i][0] == '"' && lineData[i].back() != '"') {
                unsigned int j;
                for (j = i + 1; j < lineData.size() && lineData[j].back() != '"'; ++j) {
                    lineData[i].append(lineData[j]);
                }
                lineData.erase(lineData.begin() + i + 1, lineData.begin() + j + 1);
            }
        }
        // removes quotes string values
        for (auto& data : lineData) {
            if (data[0] == '"' && data.back() == '"') {
                data = data.substr(1, data.size() - 2);
            }
        }
        // airport IATA code
        std::string source_id = lineData[2];
        std::string dest_id = lineData[4];
        std::pair<double, double> latLng1 = airportCoords[source_id];
        std::pair<double, double> latLng2 = airportCoords[dest_id];
        double dist = distanceLatLng(latLng1.first, latLng1.second, latLng2.first, latLng2.second);
        edges.push_back(Edge<Vertex>(source_id, dest_id, dist));
    }

    return edges;
}

/*!
 * Build a graph from the routes file
 * @param fileName the 3 numbers on the back of your credit card
 * @param g empty graph to pass in
 * @param airportCoords airportCoords map of airports and their coordinates
 */
template <class Vertex>
void buildGraphFromFile(std::string fileName, Graph<Vertex>& g,
                        unordered_map<std::string, std::pair<double, double>> airportCoords) {
    std::ifstream file(fileName);
    std::string line;
    std::string dataElem;
    std::vector<Edge<Vertex>> edges;
    while (std::getline(file, line)) {
        // vector to contain comma separated values
        vector<std::string> lineData;
        // splits the line by commas
        std::stringstream ss(line);
        while (getline(ss, dataElem, ',')) {
            lineData.push_back(dataElem);
        }
        // deals with commas inside parentheses by concatenating two companion strings together
        for (unsigned int i = 0; i < lineData.size(); ++i) {
            if (lineData[i][0] == '"' && lineData[i].back() != '"') {
                unsigned int j;
                for (j = i + 1; j < lineData.size() && lineData[j].back() != '"'; ++j) {
                    lineData[i].append(lineData[j]);
                }
                lineData.erase(lineData.begin() + i + 1, lineData.begin() + j + 1);
            }
        }
        // removes quotes string values
        for (auto& data : lineData) {
            if (data[0] == '"' && data.back() == '"') {
                data = data.substr(1, data.size() - 2);
            }
        }
        // airport IATA code
        std::string source_id = lineData[2];
        std::string dest_id = lineData[4];
        std::pair<double, double> latLng1 = airportCoords[source_id];
        std::pair<double, double> latLng2 = airportCoords[dest_id];
        double dist = distanceLatLng(latLng1.first, latLng1.second, latLng2.first, latLng2.second);
        g.insertEdge(Edge<Vertex>(source_id, dest_id, dist));
    }
}

/**
 * Custom comparator helper for pruneGraphMaxVertices()
 * @param a pair 1
 * @param b pair 2
 * @returns less whether a is less than b
 */
template <class Vertex> bool cmp(pair<Vertex, int>& a, pair<Vertex, int>& b) {
    return a.second < b.second;
}

/**
 * Prunes vertices until there are max N vertices in the given graph. Keeps the most connected
 * vertices first.
 * @param graph Graph to prune
 * @param N Max number of vertices
 * @returns A pruned Graph with at most N vertices
 */
template <class Vertex> Graph<Vertex> pruneGraphMaxVertices(Graph<Vertex>& graph, int N) {
    std::unordered_map<Vertex, int> counts;
    for (auto v : graph.getVertices()) {
        counts[v] = graph.getAdjacent(v).size();
    }

    std::sort(counts.begin(), counts.end(), cmp<Vertex>);

    // Only keep the largest N nodes
    std::unordered_map<Vertex, bool> largestN;
    int i = 0;
    for (auto it = counts.begin(); i < N && it != counts.end(); ++it) {
        largestN[it->first] = true;
        ++i;
    }

    // Prune edges
    vector<Edge<Vertex>> prunedEdges;
    for (auto v : largestN) {
        for (auto e : graph.getAdjacent(v.first)) {
            if (largestN.find(e) != largestN.end()) {
                prunedEdges.push_back(graph.getEdge(v.first, e));
            }
        }
    }

    // Make graph to return
    Graph<Vertex> prunedGraph(prunedEdges);

    return prunedGraph;
}

/*!
 * Builds a graph from the airport file and route file
 * @param airportFile
 * @param routeFile
 * @return graph of the airport routes
 */
template <class Vertex>
Graph<Vertex> buildGraphFromFiles(std::string airportFile, std::string routeFile) {
    Graph<Vertex> g;
    unordered_map<std::string, std::pair<double, double>> airports =
        readAirportsFromFile(airportFile);
    buildGraphFromFile<Vertex>(routeFile, g, airports);
    return g;
}
} // namespace Parsing
