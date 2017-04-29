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




enum TypeDeGraph {
    GENERAL, BIPARTI
};



int main(int argc, char** argv) {
    // - - - - - Argument parsing
    if (argc < 4 || argc > 8) {
        std::cerr << "Le nombre de paramètre est incorrect" << std::endl
                << "Utilisation : " << argv[0] << " Type_de_graph Nombre_de_noeud pas [minimum maximum nb_repetition -p]" << std::endl;
        return 0;
    }

    TypeDeGraph type_de_graph;
    if ((std::strcmp(argv[1], "g") == 0) || (std::strcmp(argv[1], "general") == 0)) {
        type_de_graph = TypeDeGraph::GENERAL;
    } else if ((std::strcmp(argv[1], "b") == 0) || (std::strcmp(argv[1], "biparti") == 0)) {
        type_de_graph = TypeDeGraph::BIPARTI;
    } else {
        std::cerr << "Type de graph inconnu: " << argv[1] << ". Soit  g pour un graph general, soit b pour un graph biparti." << std::endl;
        return 1;
    }

    unsigned int nombre_de_noeuds = std::atoi(argv[2]);
    if (nombre_de_noeuds <= 0) {
        std::cerr << "le nombre de noeud ne peut pas etre négatif: " << nombre_de_noeuds << std::endl;
        return 1;
    }

    float pas = std::atof(argv[3]);
    if (pas <= 0 || pas > 1) {
        std::cerr << "Valeur invalide pour le nombre d'étapes : " << pas << ". doit etre comprise entre 0 et 1." << std::endl;
        return 1;
    }

    float min = 0;
    if (argc > 4) {
        min = std::atof(argv[4]);
        if (min < 0 || min >= 1) {
            std::cerr << "valeur du minimum incorrecte: " << min << ". doit etre comprise entre 0 et 1." << std::endl;
            return 1;
        }
    }

    float max = 1;
    if (argc > 5) {
        max = std::atof(argv[5]);
        if (max <= 0 || max > 1) {
            std::cerr << "valeur du maximum incorrecte: " << max << ". doit etre comprise entre 0 et 1." << std::endl;
            return 1;
        }
    }

    unsigned int repetition = 100;
    if (argc > 6) {
        repetition = std::atoi(argv[6]);
        if (repetition < 0) {
            std::cerr << "Inombre de repetition incorrect: " << repetition
                    << ". doit etre positif." << std::endl;
            return 1;
        }
    }



    // - - - - - Actual work
    std::vector<std::pair<float, unsigned int>> results ( (max - min) / pas, std::pair<float, unsigned int>(0, 0));

    for (unsigned int i = 0; (i + 1) * pas + min <= max; i++) {
        results[i].first = (i + 1) * pas + min;
  
        float proba = results[i].first;
        std::random_device rand;
    	unsigned int& result = std::ref(results[i].second);
    	result= 0;
	    for (unsigned int i = 0; i < repetition; i++) {
	        if (type_de_graph == BIPARTI) {
	            UnDiGraph graph = RandomGraphBuilder::RandomBipartiteGraph(nombre_de_noeuds, nombre_de_noeuds,proba, rand);
	            if (GraphMatching::CouplageParfait(graph, GraphMatching::CouplageMaximumBiparti(graph, nombre_de_noeuds))) {
	                result++;
	            }
	        } else {
	            UnDiGraph graph = RandomGraphBuilder::RandomGraph(nombre_de_noeuds,proba, rand);
	            if (GraphMatching::CouplageParfait(graph, GraphMatching::CouplageMaximumGeneral(graph))) {
	                result++;
	            }
	        }
	       
	    }
	    
	
    }


    std::cout << " ################ Résultats ###############" << std::endl;
    std::cout <<"Nombre de nodes : " << nombre_de_noeuds << std::endl;
    std::cout << "Nombre de répétitions : "<< repetition << ", Pas :" << pas << ", min : " << min << ", max :" << max << std::endl;

    for (std::pair<float, unsigned int> i : results) {
        std::cout << i.first << "," << i.second << "," << ((float) i.second / repetition) << std::endl;
    }

    return 0;
}
