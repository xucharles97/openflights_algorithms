//
// Created by elia on 11/29/20.
//

#pragma once

#include "Edge.h"
#include "Graph.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::make_pair;
using std::pair;
using std::vector;

template <class Vertex> Graph<Vertex>::Graph(vector<Edge<Vertex>>& edges) {
    for (auto& e : edges) {
        this->insertEdge(e);
    }
}

template <class Vertex> vector<Vertex> Graph<Vertex>::getAdjacent(Vertex src) const {
    // Checks if the vertex exists in the graph
    auto loc = adj.find(src);
    if (loc == adj.end()) {
        return vector<Vertex>();
    }
    // converts unordered map to vector of vertices
    vector<Vertex> vertex_list;
    unordered_map<Vertex, Edge<Vertex>>& source_list = adj[src];
    for (auto& elem : source_list) {
        vertex_list.push_back(elem.first);
    }
    return vertex_list;
}

template <class Vertex>
vector<pair<Vertex, double>> Graph<Vertex>::getAdjacentWeighted(Vertex src) const {
    // Checks if the vertex exists in the graph
    auto loc = adj.find(src);
    if (loc == adj.end()) {
        return vector<pair<Vertex, double>>();
    }
    // Converts unordered map and edges into vector of Vertex, weight pairs
    vector<pair<Vertex, double>> vertex_list;
    unordered_map<Vertex, Edge<Vertex>>& source_list = adj[src];
    for (auto& elem : source_list) {
        vertex_list.push_back(make_pair(elem.first, elem.second.getWeight()));
    }
    return vertex_list;
}

template <class Vertex> vector<Vertex> Graph<Vertex>::getVertices() const {
    // set to keep track of which vertices we have already seen
    vector<Vertex> vertices;
    for (auto elem : adj) {
        vertices.push_back(elem.first);
    }
    return vertices;
}

template <class Vertex> vector<Edge<Vertex>> Graph<Vertex>::getEdges() const {
    // Checks to see if the graph is empty
    if (adj.empty()) {
        return vector<Edge<Vertex>>();
    }
    // iterates through adjacency list and creates the vector of edges
    vector<Edge<Vertex>> edges;
    for (auto& map : adj) {
        Vertex source = map.first;
        for (auto& pair : adj[source]) {
            edges.push_back(pair.second);
        }
    }

    return edges;
}

template <class Vertex>
Edge<Vertex> Graph<Vertex>::getEdge(Vertex source, Vertex destination) const {
    if (!edgeExists(source, destination)) {
        return Edge<Vertex>();
    }
    return adj[source][destination];
}

template <class Vertex> void Graph<Vertex>::insertEdge(const Edge<Vertex> edge) {
    if (adj.find(edge.source) == adj.end()) {
        adj[edge.source].insert({edge.dest, edge});
    } else {
        adj[edge.source][edge.dest] = edge;
    }
    if (adj.find(edge.dest) == adj.end()) {
        adj[edge.dest] = unordered_map<Vertex, Edge<Vertex>>();
    }
}

template <class Vertex> void Graph<Vertex>::insertEdge(Vertex src, Vertex dest, double weight) {
    if (adj.find(src) == adj.end()) {
        adj[src].insert({dest, Edge<Vertex>(src, dest, weight)});
    } else {
        adj[src][dest] = Edge<Vertex>(src, dest, weight);
    }
    if (adj.find(dest) == adj.end()) {
        adj[dest] = unordered_map<Vertex, Edge<Vertex>>();
    }
}

template <class Vertex> double Graph<Vertex>::getEdgeWeight(Vertex src, Vertex dest) const {
    if (edgeExists(src, dest)) {
        return adj[src][dest].getWeight();
    }
    return -1;
}

template <class Vertex> Edge<Vertex> Graph<Vertex>::removeEdge(Vertex src, Vertex dest) {
    if (!edgeExists(src, dest)) {
        return Edge<Vertex>();
    }
    auto edge = adj[src].find(dest);
    adj[src].erase(edge);
    if (adj[src].empty()) {
        auto vertex = adj.find(src);
        adj.erase(vertex);
    }
}

template <class Vertex> bool Graph<Vertex>::edgeExists(Vertex v1, Vertex v2) const {
    return adj.find(v1) != adj.end() && adj[v1].find(v2) != adj[v1].end();
}

template <class Vertex> bool Graph<Vertex>::vertexExists(Vertex v1) const {
    return adj.find(v1) != adj.end();
}
