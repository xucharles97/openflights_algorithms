#ifndef DFS_HPP
#define DFS_HPP

#include "GraphTraversal.hpp"

#include <iterator>
#include <stack>
#include <unordered_map>

template <typename Vertex> class DFS : public GraphTraversal<Vertex> {
  public:
    DFS(Graph<Vertex> graph, Vertex root) : graph(graph), root(root) {
        this->add(root);
        stack.push(root);
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
                stack.push(adjacentVertex);
                visitedmap.insert(make_pair(adjacentVertex, true));
            }
        }
    }

    Vertex pop() {
        Vertex top = stack.top();
        stack.pop();
        return top;
    }

    Vertex peek() const { return empty() ? NULL : stack.top(); }

    bool empty() const { return stack.empty(); }

  private:
    Graph<Vertex> graph;

    std::stack<Vertex> stack;
    std::unordered_map<Vertex, bool> visitedmap;

    Vertex root;
};

#endif // DFS_HPP