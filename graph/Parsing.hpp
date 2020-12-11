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

unordered_map<std::string, std::pair<double, double>> readAirportsFromFile(std::string fileName) {
    unordered_map<std::string, std::pair<double, double>> airportCoords;
    std::ifstream file(fileName);
    std::string line;
    std::string dataElem;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            vector<std::string> lineData;
            std::stringstream ss(line);
            while (getline(ss, dataElem, ',')) {
                lineData.push_back(dataElem);
            }
            for (unsigned int i = 0; i < lineData.size(); ++i) {
                if (lineData[i][0] == '"' && lineData[i].back() != '"') {
                    unsigned int j;
                    for (j = i + 1; j < lineData.size() && lineData[j].back() != '"'; ++j) {
                        lineData[i].append(lineData[j]);
                    }
                    lineData.erase(lineData.begin() + i + 1, lineData.begin() + j + 1);
                }
            }
            for (auto& data : lineData) {
                if (data[0] == '"' && data.back() == '"') {
                    data = data.substr(1, data.size() - 2);
                }
            }
            // airport IATA code
            std::string id = lineData[4];
            double latitude = std::stod(lineData[6]);
            double longitude = std::stod(lineData[7]);
            airportCoords[id] = std::make_pair(latitude, longitude);
        }
    }
    return airportCoords;
}

template <class Vertex>
std::vector<Edge<Vertex>>
readRoutesFromFile(std::string fileName,
                   unordered_map<Vertex, std::pair<double, double>> airportCoords) {
    std::ifstream file(fileName);
    std::string line;
    std::string dataElem;
    std::vector<Edge<Vertex>> edges;
    while (std::getline(file, line)) {
        vector<std::string> lineData;
        std::stringstream ss(line);
        while (getline(ss, dataElem, ',')) {
            lineData.push_back(dataElem);
        }
        for (unsigned int i = 0; i < lineData.size(); ++i) {
            if (lineData[i][0] == '"' && lineData[i].back() != '"') {
                unsigned int j;
                for (j = i + 1; j < lineData.size() && lineData[j].back() != '"'; ++j) {
                    lineData[i].append(lineData[j]);
                }
                lineData.erase(lineData.begin() + i + 1, lineData.begin() + j + 1);
            }
        }
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

template <class Vertex>
void buildGraphFromFile(std::string fileName, Graph<Vertex>& g,
                        unordered_map<std::string, std::pair<double, double>> airportCoords) {
    std::ifstream file(fileName);
    std::string line;
    std::string dataElem;
    std::vector<Edge<Vertex>> edges;
    while (std::getline(file, line)) {
        vector<std::string> lineData;
        std::stringstream ss(line);
        while (getline(ss, dataElem, ',')) {
            lineData.push_back(dataElem);
        }
        for (unsigned int i = 0; i < lineData.size(); ++i) {
            if (lineData[i][0] == '"' && lineData[i].back() != '"') {
                unsigned int j;
                for (j = i + 1; j < lineData.size() && lineData[j].back() != '"'; ++j) {
                    lineData[i].append(lineData[j]);
                }
                lineData.erase(lineData.begin() + i + 1, lineData.begin() + j + 1);
            }
        }
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

template <class Vertex> bool cmp(pair<Vertex, int>& a, pair<Vertex, int>& b) {
    return a.second < b.second;
}

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

template <class Vertex>
Graph<Vertex> buildGraphFromFiles(std::string airportFile, std::string routeFile) {
    Graph<Vertex> g;
    unordered_map<std::string, std::pair<double, double>> airports =
        readAirportsFromFile(airportFile);
    buildGraphFromFile<Vertex>(routeFile, g, airports);
    return g;
}
} // namespace Parsing
