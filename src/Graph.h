#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"

class Graph {
public:
    Graph();
    Graph(const Graph& orig);
    virtual ~Graph();

    // returns the number of vertices
    virtual unsigned int nbVertices() const = 0;
    // returns the number of edges
    virtual unsigned int nbEdges() const = 0;

    // adds the edge e to the graph
    virtual void addEdge(Edge e) = 0;
    // removes the edge e from the graph
    virtual void removeEdge(Edge e) = 0;

    // adds the edge (u,v) to the graph
    virtual void addEdge(unsigned int u, unsigned int v) = 0;
    // removes the edge (u,v) from the graph
    virtual void removeEdge(unsigned int u, unsigned int v) = 0;

    /**
     * Add a new vertex to the graph
     * @return The id of the new vertex
     */
    virtual unsigned int addVertex() = 0;
};

#endif /* GRAPH_H */

