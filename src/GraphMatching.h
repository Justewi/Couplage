/**
 * Edge.h
 *
 * Contains a set of functions made to find the maximum match in a graph.
 *
 * Authors: Alexis Metge, Liavona Zheltanosava, Gaspard lacroix
 */
#ifndef GRAPHMATCHING_H
#define GRAPHMATCHING_H

#include "Edge.h"
#include "UnDiGraph.h"

namespace GraphMatching {

	std::vector<Edge> MaximumMatching(const UnDiGraph& g);

    /**
     * Finds the maximum matching of a bipartite graph using Hopcroft-Karp
     * algorithm.
     * @param g The bipartite graph
     * @param median The amount of vertex in the left-side of the graph
     * @return The list of edges in the maximum match
     */
    std::vector<Edge> MaximumBipartite(const UnDiGraph& g, unsigned int median);

    /**
     * A match is perfect if all the edges are matched with exactly one edge.
     * @param g The graph to which the matching belongs
     * @param match The matched edges
     * @return True if the match is perfect
     */
    bool IsPerfectMatch(const UnDiGraph& g, const std::vector<Edge>& match);
}

#endif /* GRAPHMATCHING_H */

