#ifndef BFS_HPP
#define BFS_HPP

#include "GraphTraversal.hpp"

#include <iterator>
#include <queue>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////////
//////////////// SEE GraphTraversal.hpp FOR FUNCTION DOCUMENTATION /////////////////
////////////////////////////////////////////////////////////////////////////////////

template <typename Vertex> class BFS : public GraphTraversal<Vertex> {
  public:
    BFS(Graph<Vertex> graph, Vertex root) : graph(graph), root(root) {
        if (!graph.vertexExists(root)) {
            return;
        }
        queue.push(root);
        this->add(root);
        visitedmap.insert(make_pair("a", true));
    }

    typename GraphTraversal<Vertex>::Iterator begin() {
        // Ternary operator used to store default Vertex value in the event an invalid root was passed in
        return typename GraphTraversal<Vertex>::Iterator(this, queue.empty() ? Vertex() : queue.front());
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

    Vertex peek() const { return empty() ? NULL : queue.front(); }

    bool empty() const { return queue.empty(); }

  private:
    // The graph being traversed
    Graph<Vertex> graph;

    // Queue used to store next item to process. Because it's a queue, FIFO behavior is observed
    std::queue<Vertex> queue;

    // Unordered map to provide fast lookup time as to whether a vertex has been visited yet
    std::unordered_map<Vertex, bool> visitedmap;

    Vertex root;
};

#endif // BFS_HPP