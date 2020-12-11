#ifndef GRAPH_TRAVERSAL_HPP
#define GRAPH_TRAVERSAL_HPP

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
        Iterator() : traversal(NULL), root(Vertex()) {}

        /**
         * @param traversal The graph traversal to iterate over
         * @param root The vertex to start the traversal from
         */
        Iterator(GraphTraversal<Vertex>* traversal, Vertex root)
            : traversal(traversal), root(root) {
            if (!traversal->empty()) {
                current = traversal->peek();
            } else {
                current = root;
            }
        }

        /**
         * Increment the iterator by one unless there are no other elements to traverse
         * @returns the iterator incremented by one
         */
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

        /**
         * Dereference operator
         * @returns the current value of the iterator
         */
        Vertex operator*() { return current; }

        /**
         * Not equal to operator
         * @returns if two iterators are the same. Typically used to determine if the iterator is empty
         */
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
        // The traversal to iterate over
        GraphTraversal* traversal;
        
        // The first vertex in the traversal
        Vertex root;

        // The current value in the traversal
        Vertex current;
    };

    /**
     * @returns an iterator starting at the root
     */
    virtual Iterator begin() = 0;

    /**
     * @returns an iterator that is empty. While iterator != iterator.end(), iterator still has values in it
     */
    virtual Iterator end() = 0;

    /**
     * Process adjacent vertices to the parameter
     * @param vertex the vertex to process adjacent vertices of
     */
    virtual void add(Vertex vertex) = 0;

    /**
     * Removes the current item in the iterator
     * @returns the current item in the iterator
     */
    virtual Vertex pop() = 0;

    /**
     * @returns the current item in the iterator
     */
    virtual Vertex peek() const = 0;

    /**
     * @returns whether the iterator has any remaining items
     */
    virtual bool empty() const = 0;
};

#endif // GRAPH_TRAVERSAL_HPP
