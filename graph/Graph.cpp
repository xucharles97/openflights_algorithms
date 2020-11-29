//
// Created by elia on 11/29/20.
//

#include "Graph.h"
#include "Edge.h"
#include <unordered_map>
#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::make_pair;

template<Vertex>
Graph<Vertex>::Graph(vector<Vertex> vertices, vector<Edge<Vertex>> edges) {
    adj.insert(vertices.begin(), vertices.end());
    for (auto &e : edges) {
        this.insertEdge(e.source, e.destination, e.weight);
    }
}

template<Vertex>
vector<Vertex> Graph<Vertex>::getAdjacent(Vertex src) const {
    auto loc = adj.find(src);
    if (loc == adj.end()) {
        return vector<Vertex>();
    }
    vector<Vertex> vertex_list;
    unordered_map<Vertex, Edge<Vertex>> &source_list = adj[source];
    for (auto &elem : source_list) {
        vertex_list.push_back(elem.first);
    }
    return vertex_list;
}

template<Vertex>
vector<pair<Vertex, double>> Graph<Vertex>::getAdjacentWeighted(Vertex src) const {
    auto loc = adj.find(src);
    if (loc == adj.end()) {
        return vector<pair<Vertex, double>>();
    }
    vector<pair<Vertex, double>> vertex_list;
    unordered_map<Vertex, Edge<Vertex>> &source_list = adj[source];
    for (auto &elem : source_list) {
        vertex_list.push_back(make_pair(elem.first, elem.second.getWeight()));
    }
    return vertex_list;
}

template<Vertex>
vector<Vertex> Graph<Vertex>::getVertices() const {
    vector<Vertex> vertices;
    for (auto &pair : adj) {
        vertices.push_back(pair.first);
    }
    return vertices;
}

template<Vertex>
vector<Edge<Vertex>> Graph<Vertex>::getEdges() const {
    if (adj.empty()) {
        return vector<Edge<Vertex>>();
    }
    vector<Edge<Vertex>> edges;
    for (auto &map : adj) {
        Vertex source = map.first;
        for (auto &pair : adj[source]) {
            edges.push_back(pair->second);
        }
    }

    return edges;
}

template<Vertex>
Edge<Vertex> Graph<Vertex>::getEdge(Vertex source, Vertex destination) const {
    if (edgeExists(source, destination)) {
        return Edge<Vertex>();
    }
    return adj[source][destination].second;
}

template<Vertex>
void Graph<Vertex>::insertEdge(Vertex src, Vertex dest, double weight=1) {
    if (adj.find(src) == adj.end()) {
        adj.insert(src, {dest, Edge<Vertex>(src, dest, weight)});
    }
    else {
        adj[src][dest] = Edge<Vertex>(src, dest, weight);
    }
}

template<Vertex>
double Graph<Vertex>::getEdgeWeight(Vertex src, Vertex dest) const {
    if (edgeExists(src, dest)) {
        return adj[src][dest].getWeight();
    }
    return -1;
}

template<Vertex>
Edge<Vertex> Graph<Vertex>::removeEdge(Vertex src, Vertex dest) const {
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

template<Vertex>
bool Graph<Vertex>::edgeExists(Vertex v1, Vertex v2) const {
    return adj.find(v1) != adj.end() && adj[v1].find(v2) != adj[v1].end();
}