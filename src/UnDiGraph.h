/*
 * UnDiGraph.h
 *
 * This class is the traduction in C++ of the Java Graph classes studied in ADS2 course (Polytech SI3)
 *
 *  Created on: 5 mars 2017
 *      Authors: Alexis Metge, Liavona Zheltanosava, Gaspard lacroix
 */

#ifndef SRC_UNDIGRAPH_H_
#define SRC_UNDIGRAPH_H_

#include <iostream>
#include <vector>
using std::vector;

#include "Edge.h"
#include "Graph.h"

/**
 * A class for undirected graph
 */
class UnDiGraph : public Graph {
private:
    // the total number of edges
    unsigned int _nbEdges;
    // the adjacency list
    vector<vector<unsigned int>> adjacencyList;

public:

    // builds an undirected graph with n vertices
    UnDiGraph(unsigned int n);
    UnDiGraph(const UnDiGraph& orig);
    UnDiGraph(UnDiGraph&& orig);

    virtual ~UnDiGraph();

    UnDiGraph& operator=(const UnDiGraph& right);


    // returns the number of vertices
    unsigned int nbVertices() const;
    // returns the number of edges
    unsigned int nbEdges() const;

    //returns the list of the vertices adjacent to u
    vector<unsigned int> adjacents(unsigned int u) const;

    // adds the edge e to the graph
    void addEdge(Edge e);
    // removes the edge e from the graph
    void removeEdge(Edge e);

    // adds the edge (u,v) to the graph
    void addEdge(unsigned int u, unsigned int v);
    // removes the edge (u,v) from the graph
    void removeEdge(unsigned int u, unsigned int v);

    //returns the total degree of u
    unsigned int degree(unsigned int u) const;

    /**
     * Add a new vertex to the graph
     * @return The id of the new vertex
     */
    unsigned int addVertex();

};

#endif /* SRC_UNDIGRAPH_H_ */
