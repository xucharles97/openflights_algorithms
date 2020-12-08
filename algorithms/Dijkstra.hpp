//Created by Charles Xu on December 7, 2020

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include <vector>
#include <unordered_map>
#include <utility>

namespace Dijkstra {
    
    /**
     * Uses Dijkstra's algorithm to get the distance of the shortest path between two points
     * @return shortest distance between two points as a double. Returns -1.0 if one of the inputs is invalid
     */
    template <class Vertex>    
    double getDistanceBetweenPoints(Graph<Vertex>& g_, Vertex source, Vertex sink) {
        std::unordered_map<Vertex, std::pair<double, Vertex>> distances = getDistanceDataForVertex(g_, source);
        std::pair<double, Vertex> data = distances.find(sink);
        if (data == distances.end()) {
            return -1.0;
        }
        return data.first;
    }

    /**
     * Uses Dijkstra's algorithm to get the shortest path between two points
     * @return shortest path between two points as a vector of Vertex objects. Returns empty vector if one of the inputs is invalid
     */
    template <class Vertex>    
    std::vector<Edge> getPathBetweenPoints(Graph<Vertex>& g_, Vertex source, Vertex sink) {
        std::unordered_map<Vertex, std::pair<double, Vertex>> distances = getDistanceDataForVertex(g_, source);
        std::pair<double, Vertex> data = distances.find(sink);
        if (data == distances.end()) {
            return std::vector<Edge>();
        }
        std::vector<Edge> path;
        Vertex current = sink;
        while (current != source) {
            data = distances.find(current);
            path.push_back(g_.getEdge(data.second, current));
            current = data.second;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    /**
     * Uses Dijkstra's algorithm to get the distances of ALL vertices from the given point 
     * @return unordered_map where the key is the Vertex and the value is a pair of the corresponding distance from the source and the previous vertex
     * If source vertex isn't in the graph, returns an empty map
     */
    template <class Vertex>    
    std::unordered_map<Vertex, std::pair<double, Vertex>> getDistanceDataForVertex(Graph<Vertex>& g_, Vertex source) {
        std::unordered_map<Vertex, std::pair<double, Vertex>> distances;
        if (std::find(g_.getVertices().begin(), g_.getVertices().end(), source) == g_.getVertices().end()) {
            //if the source isn't in the graph, return empty map
            return distances;
        }
        std::vector<Vertex> vertices = g_.getVertices();
        std::unordered_map<Vertex, double> not_visited; //key is Vertex, value is current distance to source (to make it easier to check for next node to visit)
        for (Vertex v : vertices) {
            //set up distances
            not_visited.insert(std::pair<v, -1.0>);
            distances.insert(std::pair<v, std::pair<-1.0, source>>);
        }
        Vertex current = source;
        auto iter = distances.find(current);
        iter->first = 0.0;
        while (not_visited.size() != 0) {
            //Update weights for nodes adjacent to current
            //Find unvisited node with next smallest distance, set to current

            iter = distances.find(current);
            std::vector<std::pair<Vertex, double>> adjacent = g_.getAdjacentWeighted(current);
            for (std::pair<Vertex, double> adj : adjacent) {
                Edge<Vertex> currentEdge = g_.getEdge(current, adj.first);
                if ((adj.second == -1.0 || adj.second > iter.second + currentEdge.getWeight()) && not_visited.find(adj.first) != not_visited.end()) {
                    //if current distance is -1 (hasn't been visited yet) or is longer than the path from current vector, update the distance
                    not_visited[adj.first] = iter.second + currentEdge.getWeight();
                    distances[adj.first].first = iter.second + currentEdge.getWeight();
                    distances[adj.first].second = current;
                }
            }

            double nextShortest;
            Vertex nextVertex = current;

            for (std::pair<Vertex, double> v : not_visited) {
                if (nextVertex == current || v.second < nextShortest) {
                    nextVertex = v.first;
                    nextShortest = v.second;
                }
            }

            not_visited.erase(current);
            current = nextVertex;

        }
        return distances;
    }
}