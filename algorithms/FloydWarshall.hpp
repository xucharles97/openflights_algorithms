//
// Created by Madhav on 12/06/20.
//

#include <limits>
#include <unordered_map>
#include <vector>

#include "../graph/Edge.h"
#include "../graph/Graph.h"

#include "../traversals/BFS.hpp"
#include "../traversals/DFS.hpp"

using std::numeric_limits;
using std::unordered_map;
using std::vector;

namespace FloydWarshall {

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

template <class Vertex>
unordered_map<Vertex, unordered_map<Vertex, Vertex>>
shortestPathBetweenAllVertices(Graph<Vertex>& graph) {
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge<Vertex>> edges = graph.getEdges();

    // Init map (each vertex to every vertex) of min distances to infinity
    // Init map (each vertex to every vertex) of min path to its destination vertex
    unordered_map<Vertex, unordered_map<Vertex, Vertex>> minPaths;
    unordered_map<Vertex, unordered_map<Vertex, double>> minDistances; // Auxiliary variable
    for (Edge<Vertex> edge : edges) {
        minDistances[edge.source][edge.dest] = edge.getWeight();
        minPaths[edge.source][edge.dest] = edge.dest;
    }

    // Init distances to self to 0 and path to self to self
    for (Vertex v : vertices) {
        minDistances[v][v] = 0;
        minPaths[v][v] = v;
    }

    // Find the minimum distance from each vertex to every other vertex
    // Consider a different number of vertices along the path each time
    for (Vertex v : vertices)
        for (Vertex u : vertices)
            for (Vertex w : vertices)
                if (minDistances[u][v] + minDistances[v][w] < minDistances[u][w]) {
                    // Shorter path
                    minDistances[u][w] = minDistances[u][v] + minDistances[v][w];
                    minPaths[u][w] = minPaths[u][v];
                }

    // Now the map contains shortest distance for each Vertex v to Vertex u
    return minPaths;
}

template <class Vertex>
vector<Vertex>
shortestPathBetweenTwoVertices(unordered_map<Vertex, unordered_map<Vertex, Vertex>>& minPaths,
                               Vertex source, Vertex dest) {
    vector<Vertex> shortestPath; // To return

    if (minPaths.find(source) == minPaths.end())
        return shortestPath; // Source doesn't exist
    if (minPaths[source].find(dest) == minPaths[source].end())
        return shortestPath; // Path from source to dest doesn't exist

    shortestPath.push_back(source);
    while (source != dest) {
        source = minPaths[source][dest];
        shortestPath.push_back(source);
    }

    return shortestPath;
}

} // namespace FloydWarshall
