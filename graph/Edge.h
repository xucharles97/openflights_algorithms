//
// Created by elia on 11/29/20.
//

#pragma once

template <class Vertex>
class Edge
{
public:
    Vertex source;
    Vertex dest;

    Edge(Vertex u, Vertex v) : source(u), dest(v), weight(1) {}
    Edge(Vertex u, Vertex v, double w) : source(u), dest(v), weight(w) {}

    double getWeight() const
    {
        return this->weight;
    }

    bool operator==(Edge &other) const
    {
        return this->source == other.source && this->dest == other->dest;
    }

private:
    double weight;
};
