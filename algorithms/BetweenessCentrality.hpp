//
// Created by Madhav on 12/09/20.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "../graph/Edge.h"
#include "../graph/Graph.h"

#include "FloydWarshall.hpp"

using FloydWarshall::shortestPathBetweenAllVertices;
using std::unordered_map;
using std::vector;

namespace BetweenessCentrality {

template <class Vertex> Vertex mostCentralVertex(Graph<Vertex>& graph) {
    unordered_map<Vertex, unordered_map<Vertex, Vertex>> nextStep =
        shortestPathBetweenAllVertices(graph);

    // Most central vertex is that which passes through the most number of shortest paths
    // Obviously, exclude paths which have the vertex as the source/destination
    unordered_map<Vertex, int> vertexFrequencies;
    for (auto const& u : nextStep) {
        Vertex source = u.first; // For every source...

        for (auto const& v : u.second) { // Go through every dest...
            Vertex dest = v.first;

            Vertex next = v.second; // Vertex which lies on a shortest path
            if (source == next || dest == next)
                continue;

            if (vertexFrequencies.find(next) != vertexFrequencies.end())
                vertexFrequencies[next] += 1;
            else
                vertexFrequencies.emplace(next, 1);
        }
    }

    // Take Vertex with max frequency (if empty graph, return empty)
    if (vertexFrequencies.empty())
        return Vertex();

    auto maxPtr = std::max_element(vertexFrequencies.begin(), vertexFrequencies.end());
    Vertex mostBetweenVertex = maxPtr->first;

    return mostBetweenVertex;
}

} // namespace BetweenessCentrality