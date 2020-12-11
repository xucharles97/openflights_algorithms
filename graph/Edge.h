//
// Created by elia on 11/29/20.
//

#pragma once

template <class Vertex> class Edge {
  public:
    Vertex source;
    Vertex dest;
    /*!
     * Default edge constructor
     * Sets edge weight to 1 as if it were an unweighted graph
     */
    Edge() : source(Vertex()), dest(Vertex()), weight(1) {}
    /*!
     * Edge constructor for unweighted edge
     * @param u vertex
     * @param v vertex
     */
    Edge(Vertex u, Vertex v) : source(u), dest(v), weight(1) {}
    /*!
     * Edge constructor for weighted edge
     * @param u vertex
     * @param v vertex
     * @param w weight
     */
    Edge(Vertex u, Vertex v, double w) : source(u), dest(v), weight(w) {}
    /*!
     * Copy constructor
     * @param other Edge
     */
    Edge(const Edge<Vertex>& other)
        : source(other.source), dest(other.dest), weight(other.weight) {}
    /*!
     * Equals operator
     * @param other edge to copy
     * @return Edge reference
     */
    Edge& operator=(const Edge& other) {
        weight = other.weight;
        source = other.source;
        dest = other.dest;
        return *this;
    }
    /*!
     * Edge Destructor (included for rule of three purposes, no heap allocated objects in this struct
     */
    ~Edge() {}
    /*!
     * Gets weight contained within the edge
     * @return weight
     */
    double getWeight() const { return this->weight; }
    /*!
     * Compares edges based on which edge has the larger weight
     * @param other edge to compare to
     * @return if this edge is smaller than the other
     */
    bool operator<(const Edge<Vertex>& other) const { return weight < other.weight; }

    /*!
     * Compares two edges based on vertices
     * @param other edge
     * @return if the two edges have the same endpoints
     */
    bool operator==(const Edge<Vertex>& other) const {
        return this->source == other.source && this->dest == other.dest;
    }
    /*!
     * Compares two edges based on vertices
     * @param other edge
     * @return if the two edges have different endpoints
     */
    bool operator!=(Edge<Vertex>& other) const { return !(*this == other); }

  private:
    double weight;
};
