#include <iostream>
#include <cstdlib>
#include <random>
#include <condition_variable>
#include <cstring>

#include "GraphMatching.h"

enum TypeDeGraph {
    GENERAL, BIPARTI
};


UnDiGraph GenerateGrapheBiparti(int n1, int n2, float p){

    std::mt19937 rng;
    std::bernoulli_distribution dist(p);


    std::random_device rand;
    rng.seed(rand());


    UnDiGraph graphe(n1 + n2);

    //On ne met un lien qu'entre deux noeuds de parties opposés
    for (int gauche = 0; gauche < n1; gauche++){
        for (int droite = n1; droite < n1 + n2; droite++){
            if (dist(rng)){
                graphe.addEdge(gauche, droite);
            }
        }
    }
    return graphe;
}

UnDiGraph GenerateGeneralGraphe(int n, float p){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    UnDiGraph graphe(n);

    std::bernoulli_distribution dist(p);
    for (int e1 = 0; e1 < n; e1++){
        for (int e2 = e1; e2 < n; e2++){
            if (dist(rng)){
                graphe.addEdge(e1, e2);
            }
        }
    }
    return graphe;
}


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

    int nombre_de_noeuds = std::atoi(argv[2]);
    if (nombre_de_noeuds <= 0) {
        std::cerr << "le nombre de noeud ne peut pas etre négatif: " << nombre_de_noeuds << std::endl;
        return 1;
    }

    float pas = std::atof(argv[3]);
    if (pas <= 0 || pas > 1) {
        std::cerr << "Valeur invalide pour le pas : " << pas << ". doit etre comprise entre 0 et 1." << std::endl;
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

    int repetition = 100;
    if (argc > 6) {
        repetition = std::atoi(argv[6]);
        if (repetition < 0) {
            std::cerr << "Inombre de repetition incorrect: " << repetition
                    << ". doit etre positif." << std::endl;
            return 1;
        }
    }



    // - - - - - Actual work
    std::vector<std::pair<float, int>> results ( (max - min) / pas, std::pair<float, int>(0, 0));

    for (int i = 0; (i + 1) * pas + min <= max; i++) {
        results[i].first = (i + 1) * pas + min;

      float proba = results[i].first;
    	int& result = std::ref(results[i].second);
    	result= 0;
	    for (int i = 0; i < repetition; i++) {
	        if (type_de_graph == BIPARTI) {
	            UnDiGraph graph = GenerateGrapheBiparti(nombre_de_noeuds, nombre_de_noeuds,proba);
	            if (GraphMatching::CouplageParfait(graph, GraphMatching::CouplageMaximumBiparti(graph, nombre_de_noeuds))) {
	                result++;
	            }
	        } else {
	            UnDiGraph graph = GenerateGeneralGraphe(nombre_de_noeuds,proba);
	           /* if (GraphMatching::CouplageParfait(graph, GraphMatching::CouplageMaximumGeneral(graph))) {
	                result++;
	            }*/
	        }

	    }


    }


    std::cout << " ################ Résultats ###############" << std::endl;
    std::cout <<"Nombre de nodes : " << nombre_de_noeuds << std::endl;
    std::cout << "Nombre de répétitions : "<< repetition << ", Pas :" << pas << ", min : " << min << ", max :" << max << std::endl;

    for (std::pair<float, int> i : results) {
        std::cout << i.first << "," << i.second << "," << ((float) i.second / repetition) << std::endl;
    }

    return 0;
}
