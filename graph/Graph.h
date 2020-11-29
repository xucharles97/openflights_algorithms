//
// Created by elia on 11/29/20.
//

#ifndef MADHAV2_MGEIMER2_ECHUDOV2_CYX2_GRAPH_H
#define MADHAV2_MGEIMER2_ECHUDOV2_CYX2_GRAPH_H
#include <vector>
#include <unordered_map>
#include "Edge.h"

template<Vertex>
class Graph {
public:
    Graph();
    Graph(vector<Vertex> vertices, vector<Edge> edges);
    Graph(unsigned int numVertices);

    vector<Vertex> getAdjacent(Vertex src) const;
    vector<Vertex> getVertices() const;
    vector<Edge> getEdges() const;
    Edge getEdge(Vertex source, Vertex destination) const;
    void insertEdge(Vertex src, Vertex dest);
    double getEdgeWeight(Vertex src, Vertex dest) const;
    Edge removeEdge(Vertex src, Vertex dest);
    bool edgeExists(Vertex v1, Vertex v2);
    vector<Edge> getEdges(Vertex v);
private:
    mutable unordered_map<Vertex, unordered_map<Vertex, Edge>> adj;
};


#endif //MADHAV2_MGEIMER2_ECHUDOV2_CYX2_GRAPH_H