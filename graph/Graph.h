//
// Created by elia on 11/29/20.
//

#pragma once

#include "Edge.h"
#include <unordered_map>
#include <utility>
#include <vector>

using std::pair;
using std::unordered_map;
using std::vector;

template <class Vertex> class Graph {
  public:
    Graph<Vertex>(){};
    Graph<Vertex>(vector<Edge<Vertex>>& edges);

    vector<Vertex> getAdjacent(Vertex src) const;
    vector<pair<Vertex, double>> getAdjacentWeighted(Vertex src) const;
    vector<Vertex> getVertices() const;
    vector<Edge<Vertex>> getEdges() const;
    Edge<Vertex> getEdge(Vertex source, Vertex destination) const;
    void insertEdge(const Edge<Vertex> edge);
    void insertEdge(Vertex src, Vertex dest, double weight = 1);
    double getEdgeWeight(Vertex src, Vertex dest) const;
    Edge<Vertex> removeEdge(Vertex src, Vertex dest);
    bool edgeExists(Vertex v1, Vertex v2) const;
    bool vertexExists(Vertex v1) const;

  private:
    mutable unordered_map<Vertex, unordered_map<Vertex, Edge<Vertex>>> adj;
};

#include "Graph.hpp"