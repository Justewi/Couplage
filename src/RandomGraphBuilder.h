#ifndef RANDOMGRAPHBUILDER_H
#define RANDOMGRAPHBUILDER_H

#include <random>

#include "UnDiGraph.h"

namespace RandomGraphBuilder {

    /**
     * Build an undirected random bipartite graph
     * @param n1 The amount of vertices in the first group
     * @param n2 The amout of vertices in the second group
     * @param p The probability at which the edge exist between two vertices
     * @param rand A random device
     * @return A random bipartite graph
     */
    UnDiGraph RandomBipartiteGraph(unsigned int n1, unsigned int n2, float p, std::random_device& rand);

    /**
     * Build an undirected random graph
     * @param n The amount of vertices
     * @param p The probability at which the edge exist between two vertices
     * @param rand A random device
     * @return A random graph
     */
    UnDiGraph RandomGraph(unsigned int n, float p, std::random_device& rand);
}

#endif /* RANDOMGRAPHBUILDER_H */

