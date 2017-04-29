#include "RandomGraphBuilder.h"

#include <random>

UnDiGraph RandomGraphBuilder::RandomBipartiteGraph(unsigned int n1, unsigned int n2, float p, std::random_device& rand){
    UnDiGraph graph(n1 + n2);
    std::mt19937 rng;
    rng.seed(rand());
    std::bernoulli_distribution dist(p);

    for (unsigned int left = 0; left < n1; left++){
        for (unsigned int right = n1; right < n1 + n2; right++){
            if (dist(rng)){
                graph.addEdge(left, right);
            }
        }
    }
    return graph;
}

UnDiGraph RandomGraphBuilder::RandomGraph(unsigned int n, float p, std::random_device& rand){
    UnDiGraph graph(n);
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::bernoulli_distribution dist(p);

    for (unsigned int e1 = 0; e1 < n; e1++){
        for (unsigned int e2 = e1; e2 < n; e2++){
            if (dist(rng)){
                graph.addEdge(e1, e2);
            }
        }
    }
    return graph;
}