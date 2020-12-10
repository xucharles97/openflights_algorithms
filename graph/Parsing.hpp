//
// Created by elia on 12/9/20
//
#pragma once

#include "Edge.h"
#include "Graph.h"
#include "MathFunctions.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

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
            for (auto &data : lineData) {
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
        for (auto &data : lineData) {
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
        for (auto &data : lineData) {
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

template <class Vertex>
Graph<Vertex> buildGraphFromFiles(std::string airportFile, std::string routeFile) {
    Graph<Vertex> g;
    unordered_map<std::string, std::pair<double, double>> airports =
        readAirportsFromFile(airportFile);
    buildGraphFromFile<Vertex>(routeFile, g, airports);
    return g;
}
} // namespace Parsing