//
// Created by Madhav on 12/06/20.
//

#pragma once

#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

#include "../graph/Edge.h"
#include "../graph/Graph.h"

using std::numeric_limits;
using std::unordered_map;
using std::vector;

namespace FloydWarshall {

/**
 * Returns the distance of the shortest possible path between every vertex and every other vertex.
 * ie. The shortest possible distances. Returns an empty map if graph is empty.
 *
 * @param graph The graph
 * @returns The shortest distances between every vertex and every other vertex, as a
 * map[source][destination] = double
 */
template <class Vertex>
unordered_map<Vertex, unordered_map<Vertex, double>>
shortestDistanceBetweenAllVertices(Graph<Vertex>& graph) {
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge<Vertex>> edges = graph.getEdges();

    // Init map (each vertex to every vertex) of min distances to infinity
    unordered_map<Vertex, unordered_map<Vertex, double>> minDistances; // To return
    for (Vertex v : vertices) {
        for (Vertex u : vertices) {
            if (v == u)
                minDistances[v][u] = 0; // Distance to itself is 0
            else
                minDistances[v][u] = numeric_limits<double>::infinity();
        }
    }

    // Set each distance from Vertex u to Vertex v to be its corresponding edge's weight
    for (Edge<Vertex> edge : edges)
        minDistances[edge.source][edge.dest] = edge.getWeight();

    // Find the minimum distance from each vertex to every other vertex
    // Consider a different number of vertices along the path each time
    for (Vertex v : vertices)
        for (Vertex u : vertices)
            for (Vertex w : vertices)
                if (minDistances[u][v] + minDistances[v][w] < minDistances[u][w])
                    minDistances[u][w] = minDistances[u][v] + minDistances[v][w]; // Shorter path

    // Now the map contains shortest distance for each Vertex v to Vertex u
    return minDistances;
}

/**
 * Returns the shortest possible path between every vertex and every other vertex as a map of next
 * steps. ie. The next vertex to travel to. Returns an empty map if graph is empty.
 *
 * @param graph The graph
 * @returns The shortest path between every vertex and every other vertex, as a
 * map[source][destination] = nextVertex
 */
template <class Vertex>
unordered_map<Vertex, unordered_map<Vertex, Vertex>>
shortestPathBetweenAllVertices(Graph<Vertex>& graph) {
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge<Vertex>> edges = graph.getEdges();

    // Init map (each vertex to every vertex) of min distances to infinity
    unordered_map<Vertex, unordered_map<Vertex, double>> minDistances; // Auxiliary variable
    std::cout << "Initializing distances map..." << std::endl;
    for (Vertex v : vertices)
        for (Vertex u : vertices)
            minDistances[v][u] = numeric_limits<double>::infinity();

    // Init map (each vertex to every vertex) of min path to its destination vertex
    // Also init distances to edge weights for every edge
    std::cout << "Initializing next steps map..." << std::endl;
    unordered_map<Vertex, unordered_map<Vertex, Vertex>> nextStep;
    for (Edge<Vertex> edge : edges) {
        minDistances[edge.source][edge.dest] = edge.getWeight();
        nextStep[edge.source][edge.dest] = edge.dest;
    }

    // Init distances to self to 0 and path from self to self
    std::cout << "Initializing both maps for edge cases..." << std::endl;
    for (Vertex v : vertices) {
        minDistances[v][v] = 0;
        nextStep[v][v] = v;
    }

    // Find the minimum distance from each vertex to every other vertex
    // Consider a different number of vertices along the path each time
    std::cout << "Computing the minimum distances..." << std::endl;
    for (Vertex v : vertices) {
        for (Vertex u : vertices) {
            for (Vertex w : vertices) {
                if (minDistances[u][v] + minDistances[v][w] < minDistances[u][w]) {
                    // Shorter path
                    minDistances[u][w] = minDistances[u][v] + minDistances[v][w];
                    nextStep[u][w] = nextStep[u][v];
                }
            }
        }
    }

    // Now the map contains the best next vertex for each Vertex v to Vertex u
    return nextStep;
}

/**
 * Returns the shortest possible path between 2 given vertices, as a vector representing the path,
 * inclusive of the source and destination. Returns an empty vector if not possible.
 *
 * @param graph The graph
 * @param source The starting vertex
 * @param dest The ending vertex
 * @returns The shortest path between source and dest as a vector of vertices
 */
template <class Vertex>
vector<Vertex> shortestPathBetweenTwoVertices(Graph<Vertex>& graph, Vertex source, Vertex dest) {
    vector<Vertex> shortestPath; // To return

    unordered_map<Vertex, unordered_map<Vertex, Vertex>> nextStep =
        shortestPathBetweenAllVertices(graph);

    if (nextStep.find(source) == nextStep.end())
        return shortestPath; // Source doesn't exist
    if (nextStep.find(dest) == nextStep.end())
        return shortestPath; // Dest doesn't exist

    shortestPath.push_back(source);
    while (source != dest) {
        source = nextStep[source][dest];
        shortestPath.push_back(source);
    }

    return shortestPath;
}

} // namespace FloydWarshall
