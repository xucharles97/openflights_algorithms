#ifndef DFS_HPP
#define DFS_HPP

#pragma once

#include "GraphTraversal.hpp"

#pragma once

#include <iterator>
#include <queue>
#include <unordered_map>

template <typename Vertex>
class DFS: public GraphTraversal<Vertex> {
    public:
        DFS(Graph<Vertex> graph, Vertex root): graph(graph), root(root) {
            this->add(root);
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
                    stack.push_back(adjacentVertex);
                    visitedmap.insert(make_pair(adjacentVertex, true));
                }
            }
        }

        Vertex pop() {
            Vertex top = stack.top();
            stack.pop();
            return top;
        }

        Vertex peek() const {
            return empty() ? NULL : stack.top();
        }

        bool empty() const {
            return stack.empty();
        }
    private:
        Graph<Vertex> graph;

        std::stack<Vertex> stack;
        std::unordered_map<Vertex, bool> visitedmap;
        
        Vertex root;
};

#endif //DFS_HPP