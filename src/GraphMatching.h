/**
 * GraphMatching.h
 *
 * Authors: Alexandre BAR , Cyprien LEVY

 */
#ifndef GRAPHMATCHING_H
#define GRAPHMATCHING_H

#include "Edge.h"
#include "UnDiGraph.h"

namespace GraphMatching {

		/**
	 	 *  Trouve le couplage maximum dans le cas général
	 	 */
		std::vector<Edge> CouplageMaximumGeneral(const UnDiGraph& graphe);

    /**
     * Trouve le couplage maximum dans le cas d'un graphe biparti
     */
    std::vector<Edge> CouplageMaximumBiparti(const UnDiGraph& graphe, int moitie);

    /**
     * Fonction permettant de dire si un couplage est parfait ou non.
		 * (1 noeud relié a 1 et 1 seul autre noeud)
     */
    bool CouplageParfait(const UnDiGraph& g, const std::vector<Edge>& match);
}

#endif /* GRAPHMATCHING_H */
