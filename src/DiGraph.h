#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "Graph.h"

#include <vector>

/**
 * Represent a weighted directed graph
 */
class DiGraph : public Graph {
    std::vector<std::vector<int>> adjacency;
    unsigned int _nbEdges;
public:
    DiGraph(unsigned int nbVertex);
    DiGraph(const DiGraph& orig);
    virtual ~DiGraph();

    unsigned int nbVertices() const;
    unsigned int nbEdges() const;

    void addEdge(Edge e);
    void removeEdge(Edge e);

    void addEdge(unsigned int u, unsigned int v);
    void removeEdge(unsigned int u, unsigned int v);

    unsigned int addVertex();
};

#endif /* DIGRAPH_H */

