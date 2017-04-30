#ifndef GRAPH_H
#define GRAPH_H


/*
 * Graph.h
 * Classe réutilisée du cours d'ADS en SI3
 * Alexandre BAR, Cyprien LEVY
 */
#include "Edge.h"

class Graph {
public:
    Graph();
    Graph(const Graph& orig);
    virtual ~Graph();

    // returns the number of vertices
    virtual int nbVertices() const = 0;
    // returns the number of edges
    virtual int nbEdges() const = 0;

    // adds the edge e to the graph
    virtual void addEdge(Edge e) = 0;
    // removes the edge e from the graph
    virtual void removeEdge(Edge e) = 0;

    // adds the edge (u,v) to the graph
    virtual void addEdge(int u, int v) = 0;
    // removes the edge (u,v) from the graph
    virtual void removeEdge(int u, int v) = 0;

    /**
     * Add a new vertex to the graph
     * @return The id of the new vertex
     */
    virtual int addVertex() = 0;
};

#endif /* GRAPH_H */
