#ifndef GRAPH_TRAVERSAL_HPP
#define GRAPH_TRAVERSAL_HPP

#pragma once

#include "../graph/Graph.h"

#include <iostream>
#include <iterator>
using std::cout;
using std::endl;

// Code here
template <typename Vertex> class GraphTraversal {
  public:
    class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
      public:
        Iterator() : traversal(NULL) {}

        Iterator(GraphTraversal<Vertex>* traversal, Vertex root)
            : traversal(traversal), root(root) {
            current = traversal->peek();
        }

        Iterator& operator++() {
            if (!traversal->empty()) {
                current = traversal->pop();

                traversal->add(current);

                if (!traversal->empty()) {
                    current = traversal->peek();
                }
            }

            return *this;
        }

        Vertex operator*() { return current; }

        bool operator!=(const Iterator& other) {
            bool thisEmpty = false;
            bool otherEmpty = false;

            if (traversal == NULL) {
                thisEmpty = true;
            }
            if (other.traversal == NULL) {
                otherEmpty = true;
            }

            if (!thisEmpty) {
                thisEmpty = traversal->empty();
            }
            if (!otherEmpty) {
                otherEmpty = other.traversal->empty();
            }

            if (thisEmpty && otherEmpty)
                return false; // both empty then the traversals are equal, return true
            else if ((!thisEmpty) && (!otherEmpty))
                return (traversal != other.traversal); // both not empty then compare the traversals
            else
                return true; // one is empty while the other is not, return true
        }

      private:
        GraphTraversal* traversal;
        Vertex root;
        Vertex current;
    };

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
    virtual void add(Vertex vertex) = 0;
    virtual Vertex pop() = 0;
    virtual Vertex peek() const = 0;
    virtual bool empty() const = 0;
};

#endif // GRAPH_TRAVERSAL_HPP
