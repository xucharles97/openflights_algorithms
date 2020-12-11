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
    /*!
     * Builds graph out of list of edges
     * @param edges vector of edges with type Vertex
     */
    Graph<Vertex>(vector<Edge<Vertex>>& edges);
    /*!
     * Gets all adjacent vertices to src
     * @param src vertex to find adjacent edges with
     * @return returns vector of Vertices that are adjacent to src
     */
    vector<Vertex> getAdjacent(Vertex src) const;
    /*!
     * Gets all adjacent vertices to src along with the edge weights
     * @param src vertex to find adjacent vertices to
     * @return returns vector of pairs containing the adjacent vertex and
     *                  the distance between src and the vertex
     */
    vector<pair<Vertex, double>> getAdjacentWeighted(Vertex src) const;
    /*!
     * Gets all of the vertices in vector form. O(|E|) runtime.
     * @return vector of vertices contained within the graph
     */
    vector<Vertex> getVertices() const;
    /*!
     * Gets all of the edges in vector form. O(|E|) runtime.
     * @return vector of edges contained within the graph
     */
    vector<Edge<Vertex>> getEdges() const;
    /*!
     * Gets edge object between source and destination.  O(|V| + |E|) runtime
     * @param source vertex
     * @param destination vertex
     * @return Edge object containing src, dest, and the weight between the two vertices.
     */
    Edge<Vertex> getEdge(Vertex source, Vertex destination) const;
    /*!
     * Inserts an edge into the graph.  Runs in Amortized O(1) time
     * @param edge to insert
     */
    void insertEdge(const Edge<Vertex> edge);
    /*!
     * Inserts an edge into the graph.  Runs in Amortized O(1) time
     * @param src vertex
     * @param dest vertex
     * @param weight between the two vertices
     */
    void insertEdge(Vertex src, Vertex dest, double weight = 1);
    /*!
     * Gets weight between two vertices
     * @param src vertex
     * @param dest vertex
     * @return weight
     */
    double getEdgeWeight(Vertex src, Vertex dest) const;
    /*!
     * Removes edge between src and dest
     * @param src vertex
     * @param dest vertex
     * @return edge removed
     */
    Edge<Vertex> removeEdge(Vertex src, Vertex dest);
    /*!
     * Checks if an edge exists within the graph.  Runs in amortized O(1)
     * @param v1 vertex
     * @param v2 vertex
     * @return if edge exists
     */
    bool edgeExists(Vertex v1, Vertex v2) const;
    /*!
     * Checks to see if the vertex exists within the graph.
     * @param v1 vertex
     * @return if v1 is contained within the graph.
     */
    bool vertexExists(Vertex v1) const;

  private:
    // adjacency list of vertices represented as an unordered map of unordered maps
    // a bit slower in runtime, but it achieves the same asymptotic runtime
    // and allows for general object containment rather only indices with vectors
    mutable unordered_map<Vertex, unordered_map<Vertex, Edge<Vertex>>> adj;
};

#include "Graph.hpp"