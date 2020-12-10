// Created by Charles Xu on December 7, 2020

#pragma once

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Dijkstra {

/**
 * Uses Dijkstra's algorithm to get the distances of ALL vertices from the given point
 * @return unordered_map where the key is the Vertex and the value is a pair of the corresponding
 * distance from the source and the previous vertex If source vertex isn't in the graph, returns an
 * empty map
 */
template <class Vertex>
std::unordered_map<Vertex, std::pair<double, Vertex>> getDistanceDataForVertex(Graph<Vertex>& g_,
                                                                               Vertex source) {

    // key data structures to be used

    // map to return. Key is vertex, value is pair of distance and previous Vertex
    std::unordered_map<Vertex, std::pair<double, Vertex>> distances;

    // Keeps track of which vertices haven't been visited. Once a vertex has been visited, its
    // corresponding element is deleted
    std::unordered_map<Vertex, double>
        not_visited; // key is Vertex, value is current distance to source (to make it easier to
                     // check for next node to visit)

    // check for empty graph
    if (g_.getVertices().size() == 0) {
        return distances;
    }

    // if the source isn't in the graph, return empty map
    if (!g_.vertexExists(source)) {
        return distances;
    }

    // populate data structures with vertex data
    std::vector<Vertex> vertices = g_.getVertices();
    for (Vertex v : vertices) {
        // Default distance value is -1.0 - use to track if no path to the vertex has been found
        not_visited.insert(std::make_pair(v, -1.0));
        distances.insert(std::make_pair(v, std::make_pair(-1.0, Edge<Vertex>().source)));
    }

    // set source as starting vertex, update distance to 0
    Vertex current = source;
    distances[current].first = 0.0;
    distances[current].second = source;

    while (not_visited.size() != 0) {
        // Update weights for nodes adjacent to current
        // Find unvisited node with next smallest distance, set to current

        std::vector<std::pair<Vertex, double>> adjacent = g_.getAdjacentWeighted(current);
        double currentDistance = distances[current].first;

        // iterate through adjacent vertices, update distance/previous vertex as needed
        for (std::pair<Vertex, double> adj : adjacent) {

            Edge<Vertex> currentEdge = g_.getEdge(current, adj.first);
            // check if the edge connecting the current vertex to the adjacent one is outgoing
            if (currentEdge.source != current) {
                // if there is no outgoing edge to the adjacent vertex, skip this vertex
                continue;
            }

            // update distance/previous vertex if:
            // 1) vertex doesn't have a path yet or 2) vertex has a path to source, but is longer
            // than the current path must also be in not_visited
            if ((distances[adj.first].first == -1.0 ||
                 distances[adj.first].first > currentDistance + adj.second) &&
                not_visited.find(adj.first) != not_visited.end()) {
                not_visited[adj.first] = currentDistance + adj.second;
                distances[adj.first].first = currentDistance + adj.second;
                distances[adj.first].second = current; // set previous vertex to current
            }
        }

        // determine next vertex to visit
        double nextShortest = -1.0;
        Vertex nextVertex = current;

        // delete current vertex from not_visited so it doesn't accidentally get chosen
        not_visited.erase(current);

        // if current vertex is last one, exit loop
        if (not_visited.empty()) {
            break;
        }

        // iterate throuth not_visited to find vertex with shortest distance
        for (std::pair<Vertex, double> v : not_visited) {
            if (not_visited.size() == 1) {
                // if there's only one vertex left, then visit it if it has a path to the source
                if (v.second != -1.0) {
                    nextVertex = v.first;
                }
            } else {
                // set vertex to nextVertex if it's the first vertex with a path to the source, or
                // if it's not the first but it has a shorter path to the vertex
                if ((nextShortest == -1.0 && v.second != -1.0) ||
                    (nextShortest != -1.0 && v.second != -1.0 && v.second < nextShortest)) {
                    nextVertex = v.first;
                    nextShortest = v.second;
                }
            }
        }
        // if no remaining vertices have a path to the source, break
        if (nextVertex == current) {
            break;
        }

        current = nextVertex;
    }
    return distances;
}

/**
 * Uses Dijkstra's algorithm to get the distance of the shortest path between two points
 * @return shortest distance between two points as a double. Returns -1.0 if one of the inputs is
 * invalid or if there is no path between the two
 */
template <class Vertex>
double getDistanceBetweenPoints(Graph<Vertex>& g_, Vertex source, Vertex sink) {

    // get data to derive distance
    std::unordered_map<Vertex, std::pair<double, Vertex>> distances =
        Dijkstra::getDistanceDataForVertex(g_, source);

    // if the destination is not in the graph, return -1
    if (distances.find(sink) == distances.end()) {
        return -1.0;
    }

    // return the double in the value pair of the distance map. Will be -1 if there is no path to
    // the source
    return distances[sink].first;
}

/**
 * Uses Dijkstra's algorithm to get the shortest path between two points
 * @return shortest path between two points as a vector of Vertex objects. Returns empty vector if
 * one of the inputs is invalid
 */
template <class Vertex>
std::vector<Edge<Vertex>> getPathBetweenPoints(Graph<Vertex>& g_, Vertex source, Vertex sink) {

    // get data to derive path from
    std::unordered_map<Vertex, std::pair<double, Vertex>> distances =
        getDistanceDataForVertex(g_, source);

    // if destination is not in the graph, return empty vector
    if (distances.find(sink) == distances.end()) {
        return std::vector<Edge<Vertex>>();
    }

    std::vector<Edge<Vertex>> path; // vector to return

    // start at element of last element, work backwards, and reverse the vector in the end
    std::pair<double, Vertex> data = distances[sink];
    Vertex current = sink;
    while (current != source) {
        data = distances[current];

        // check to make sure the edge is valid. If invalid, return empty vector
        if (!g_.edgeExists(data.second, current)) {
            return std::vector<Edge<Vertex>>();
        }

        // insert edge to the back of the vector, update current vertex to the one that leads into
        // the current one
        path.push_back(g_.getEdge(data.second, current));
        current = data.second;
    }

    // reverse the path vector to get the correct order
    std::reverse(path.begin(), path.end());
    return path;
}

template <class Vertex>
std::string getPrintStatementForDijkstraPath(Graph<Vertex>& g_, Vertex source, Vertex sink) {
    std::vector<Edge<Vertex>> path = getPathBetweenPoints(g_, source, sink);
    if (path.size() == 0) {
        std::stringstream ss;
        ss << "There is no path from " << source << " to " << sink;
        return ss.str();
    }
    std::stringstream ss;
    ss << "The shortest path from " << source << " to " << sink << " is: " << source;
    for (Edge<Vertex> edge : path) {
        ss << "->" << edge.dest;
    }
    return ss.str();
}

template <class Vertex>
void printShortestDijkstraPath(Graph<Vertex>& g_, Vertex source, Vertex sink) {
    std::cout << getPrintStatementForDijkstraPath(g_, source, sink) << std::endl;
}

template <class Vertex>
std::string getPrintStatementForDijkstraDistance(Graph<Vertex>& g_, Vertex source, Vertex sink) {
    double distance = getDistanceBetweenPoints(g_, source, sink);
    if (distance == -1) {
        return std::string("There is no path from ").append(source).append(" to ").append(sink);
    }
    std::string str = std::string("The shortest distance from ")
                          .append(source)
                          .append(" to ")
                          .append(sink)
                          .append(" is: ") +
                      std::to_string(distance);

    return str;
}

template <class Vertex>
void printShortestDijkstraDistance(Graph<Vertex>& g_, Vertex source, Vertex sink) {
    std::cout << getPrintStatementForDijkstraDistance(g_, source, sink) << std::endl;
}

template <class Vertex>
std::string getPrintStatementForDijkstraData(Graph<Vertex>& g_, Vertex source) {
    std::unordered_map<Vertex, std::pair<double, Vertex>> data =
        getDistanceDataForVertex(g_, source);

    std::stringstream ss;
    ss << "From source vector " << source << ":";
    for (std::pair<Vertex, std::pair<double, Vertex>> d : data) {
        if (d.second.first == -1.0) {
            ss << "\nThere is no path to " << d.first;
        } else {
            if (d.first == source) {
                continue;
            }
            ss << "\nVertex " << d.first << " is " << d.second.first << " away, coming from vertex "
               << d.second.second;
        }
    }

    return ss.str();
}

template <class Vertex> void printDijkstraData(Graph<Vertex>& g_, Vertex source) {
    std::cout << getPrintStatementForDijkstraData(g_, source) << std::endl;
}

} // namespace Dijkstra