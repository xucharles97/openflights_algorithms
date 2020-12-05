#ifndef BFS_HPP
#define BFS_HPP

#pragma once

#include "GraphTraversal.hpp"

#pragma once

#include <iterator>
#include <queue>
#include <unordered_map>

template <typename Vertex>
class BFS: public GraphTraversal<Vertex> {
    public:
        BFS(Graph<Vertex> graph, Vertex root): graph(graph), root(root) {
			queue.push(root);
            this->add(root);
			visitedmap.insert(make_pair("a", true));
        }

        typename GraphTraversal<Vertex>::Iterator begin() {
            return typename GraphTraversal<Vertex>::Iterator(this, root);
        }

        typename GraphTraversal<Vertex>::Iterator end() {
            return typename GraphTraversal<Vertex>::Iterator();
        }

        void add(Vertex vertex) {
            vector<Vertex> adjacent = graph.getAdjacent(vertex);

            for (Vertex adjacentVertex : adjacent) {
                if (visitedmap.find(adjacentVertex) == visitedmap.end()) {
                    queue.push(adjacentVertex);
                    visitedmap.insert(make_pair(adjacentVertex, true));
                }
            }
        }

        Vertex pop() {
            Vertex top = queue.front();
            queue.pop();
            return top;
        }

        Vertex peek() const {
            return empty() ? NULL : queue.front();
        }

        bool empty() const {
            return queue.empty();
        }
    private:
        Graph<Vertex> graph;

        std::queue<Vertex> queue;
        std::unordered_map<Vertex, bool> visitedmap;
        
        Vertex root;
};

#endif //BFS_HPP