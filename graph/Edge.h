//
// Created by elia on 11/29/20.
//

#pragma once

template <class Vertex> class Edge {
  public:
    Vertex source;
    Vertex dest;

    Edge() : source(Vertex()), dest(Vertex()), weight(1) {}
    Edge(Vertex u, Vertex v) : source(u), dest(v), weight(1) {}
    Edge(Vertex u, Vertex v, double w) : source(u), dest(v), weight(w) {}
    Edge(const Edge<Vertex>& other)
        : source(other.source), dest(other.dest), weight(other.weight) {}
    Edge& operator=(const Edge& other) {
        weight = other.weight;
        source = other.source;
        dest = other.dest;
        return *this;
    }
    ~Edge() {}
    double getWeight() const { return this->weight; }

    bool operator<(const Edge<Vertex>& other) const { return weight < other.weight; }

    bool operator==(const Edge<Vertex>& other) const {
        return this->source == other.source && this->dest == other.dest;
    }

    bool operator!=(Edge<Vertex>& other) const { return !(*this == other); }

  private:
    double weight;
};
