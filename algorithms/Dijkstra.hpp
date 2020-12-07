//Created by Charles Xu on December 7, 2020

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include <vector>
#include <unordered_map>


namespace Dijkstra {
    
    /**
     * Uses Dijkstra's algorithm to get the distance of the shortest path between two points
     * @return shortest distance between two points as a double
     */
    template <class Vertex>    
    double getDistanceBetweenPoints(Vertex source, Vertex sink) {
        return -1.0;
    }

    /**
     * Uses Dijkstra's algorithm to get the shortest path between two points
     * @return shortest path between two points as a vector of Vertex objects
     */
    template <class Vertex>    
    std::vector<Vertex> getPathBetweenPoints(Vertex source, Vertex sink) {
        return std::vector<Vertex>();
    }

    /**
     * Uses Dijkstra's algorithm to get the distances of ALL vertices from the given point 
     * @return unordered_map where the key is the Vertex and the value is the corresponding distance from the source
     */
    template <class Vertex>    
    std::unordered_map<Vertex, double> getDistanceDataForVertex(Vertex source) {
        return std::unordered_map<Vertex,double>();
    }
}