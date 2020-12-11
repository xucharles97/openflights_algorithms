#ifndef DFS_HPP
#define DFS_HPP

#include "GraphTraversal.hpp"

#include <iterator>
#include <stack>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////////
//////////////// SEE GraphTraversal.hpp FOR FUNCTION DOCUMENTATION /////////////////
////////////////////////////////////////////////////////////////////////////////////

template <typename Vertex> class DFS : public GraphTraversal<Vertex> {
  public:
    DFS(Graph<Vertex> graph, Vertex root) : graph(graph), root(root) {
        if (!graph.vertexExists(root)) {
            return;
        }
        this->add(root);
        stack.push(root);
        visitedmap.insert(make_pair("a", true));
    }

    typename GraphTraversal<Vertex>::Iterator begin() {
        // Ternary operator used to store default Vertex value in the event an invalid root was passed in
        return typename GraphTraversal<Vertex>::Iterator(this, stack.empty() ? Vertex() : stack.top());
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
    // The graph being traversed
    Graph<Vertex> graph;

    // Stack used to store next item to process. Because it's a queue, FILO behavior is observed
    std::stack<Vertex> stack;

    // Unordered map to provide fast lookup time as to whether a vertex has been visited yet
    std::unordered_map<Vertex, bool> visitedmap;

    Vertex root;
};

#endif // DFS_HPP