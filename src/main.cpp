#include <iostream>
#include <cstdlib>
#include <random>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <iomanip>

#include "RandomGraphBuilder.h"
#include "GraphMatching.h"

static unsigned int threadCount = 0;
static std::mutex threadCountMutex;
static std::condition_variable cv;
static std::atomic<unsigned int> progress;

enum TypeGraph {
    GENERAL, BIPARTI
};

void compute(TypeGraph type, unsigned int repeat, float p, unsigned int nbNodes, unsigned int& result) {
    // We need to start this one only once, since windows has no entropy
    std::random_device rand;
    result = 0;
    for (unsigned int i = 0; i < repeat; i++) {
        if (type == BIPARTI) {
            UnDiGraph graph = RandomGraphBuilder::RandomBipartiteGraph(nbNodes, nbNodes, p, rand);
            if (GraphMatching::IsPerfectMatch(graph, GraphMatching::MaximumBipartite(graph, nbNodes))) {
                result++;
            }
        } else {
            UnDiGraph graph = RandomGraphBuilder::RandomGraph(nbNodes, p, rand);
            if (GraphMatching::IsPerfectMatch(graph, GraphMatching::MaximumMatching(graph))) {
                result++;
            }
        }
        progress++;
    }
    { // Critical section
        std::unique_lock<std::mutex> lk(threadCountMutex);
        threadCount--;
        cv.notify_one();
    }
}

static bool done;


int main(int argc, char** argv) {
    // - - - - - Argument parsing
    if (argc < 4 || argc > 9) {
        std::cerr << "Invalid amount of parameters." << std::endl
                << "Usage: " << argv[0] << " Type_of_graph Number_of_nodes step [min max max_thread nb_repeat -p]" << std::endl;
        return 0;
    }

    TypeGraph type;
    if ((std::strcmp(argv[1], "g") == 0) || (std::strcmp(argv[1], "general") == 0)) {
        type = TypeGraph::GENERAL;
    } else if ((std::strcmp(argv[1], "b") == 0) || (std::strcmp(argv[1], "biparti") == 0)) {
        type = TypeGraph::BIPARTI;
    } else {
        std::cerr << "Invalid value for Type_of_graph: " << argv[1] << ". Expected (g | general) for general graph or (b | biparti) for bipartite graph." << std::endl;
        return 1;
    }

    unsigned int nbNodes = std::atoi(argv[2]);
    if (nbNodes <= 0) {
        std::cerr << "Invalid value for Number_of_nodes: " << nbNodes << ". Expected a positive integer." << std::endl;
        return 1;
    }
    float step = std::atof(argv[3]);
    if (step <= 0 || step > 1) {
        std::cerr << "Valeur invalide pour le nombre d'étapes : " << step << ". Valeur attendue entre 0 et 1." << std::endl;
        return 1;
    }
    float min = 0;
    if (argc > 4) {
        min = std::atof(argv[4]);
        if (min < 0 || min >= 1) {
            std::cerr << "Invalid value for min: " << min << ". Expected a decimal value in [0;1)." << std::endl;
            return 1;
        }
    }
    float max = 1;
    if (argc > 5) {
        max = std::atof(argv[5]);
        if (max <= 0 || max > 1) {
            std::cerr << "Invalid value for max: " << max << ". Expected a decimal value in (0;1]." << std::endl;
            return 1;
        }
    }


    // Try to determine the amount of avaiable threads, or default to 4
    unsigned int nbThreads = std::thread::hardware_concurrency();
    if (argc > 6) {
        nbThreads = std::atoi(argv[6]);
        if (nbThreads < 0) {
            std::cerr << "Invalid value for max_thread: " << nbThreads
                    << ". Expected a positive value." << std::endl;
            return 1;
        }
    }
    if (nbThreads == 0) nbThreads = 4;

    unsigned int repeat = 100;
    if (argc > 7) {
        repeat = std::atoi(argv[7]);
        if (repeat < 0) {
            std::cerr << "Invalid value for nb_repeat: " << repeat
                    << ". Expected a positive value." << std::endl;
            return 1;
        }
    }



    // - - - - - Actual work
    std::vector<std::pair<float, unsigned int>> results ( (max - min) / step, std::pair<float, unsigned int>(0, 0));

    for (unsigned int i = 0; (i + 1) * step + min <= max; i++) {
        results[i].first = (i + 1) * step + min;
        compute(type, repeat, results[i].first, nbNodes, std::ref(results[i].second));
    }


    std::cout << " ################ Résultats ###############" << std::endl;
    std::cout <<"Nombre de nodes : " << nbNodes << std::endl;
    std::cout << "Nombre de répétitions : "<< repeat << ", Pas :" << step << ", min : " << min << ", max :" << max << std::endl;

    for (std::pair<float, unsigned int> i : results) {
        std::cout << i.first << "," << i.second << "," << ((float) i.second / repeat) << std::endl;
    }

    return 0;
}
