#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <unordered_set>
#include "GraphMatching.h"
#include "UnDiGraph.h"

static std::vector<int> ParcoursEnProfondeur(const UnDiGraph& graphe, const std::vector<bool>& matched, int moitie, const std::unordered_set<Edge, Edge::Hash>& arretesCouplees, int source, std::vector<bool>& visited);
static std::set<int> ParcoursEnLargeur(const UnDiGraph& graphe, const std::vector<bool>& matched,  int moitie, const std::unordered_set<Edge, Edge::Hash>& arretesCouplees);

std::vector<Edge> CouplageMaximumGeneral(const UnDiGraph& graphe){

}

/**
*
* Algo de Hopcroft-Karp
* suis l'algo à cette adresse :
* https://en.wikipedia.org/wiki/Hopcroft-Karp_algorithm
* Complexité : O(nombre de noeuds)
**/
std::vector<Edge> GraphMatching::CouplageMaximumBiparti(const UnDiGraph& graphe, int moitie) {
    std::unordered_set<Edge, Edge::Hash> arretesCouplees;
    std::vector<bool> matched(graphe.nbVertices(), false);
    //Parcours en largeur
    std::set<int> bfsResultSet = ParcoursEnLargeur(graphe, matched, moitie, arretesCouplees);
    while (!bfsResultSet.empty()) {
        for (int i : bfsResultSet) {
            // Trouve un chemin en utilisant l'algorithme de parcours en profondeur

            std::vector<bool> visited(graphe.nbVertices(), false);

            std::vector<int> chemin = ParcoursEnProfondeur(graphe, matched, moitie, arretesCouplees, i, visited);

            if (!chemin.empty()){
                chemin.push_back(i);
            }


            bool step = false;
            if (!chemin.empty()){
                for (int j = 0; j < chemin.size() - 1; j++) {

                    int droite = chemin.at(j + 1);
                    int gauche = chemin.at(j);
                    if (gauche > droite){
                      std::swap(gauche, droite);
                    }
                    if (step){
                      arretesCouplees.erase(Edge(gauche, droite));
                    }
                    else{
                      arretesCouplees.insert(Edge(gauche, droite));
                    }
                    step = !step;
                    matched.at(gauche) = true;
                    matched.at(droite) = true;

                }
              }
        }
        bfsResultSet = ParcoursEnLargeur(graphe, matched, moitie, arretesCouplees);
    }
    return std::vector<Edge>(arretesCouplees.begin(), arretesCouplees.end());
}

/**
 * Test si le couplage est parfait .
 */
bool GraphMatching::CouplageParfait(const UnDiGraph& graphe, const std::vector<Edge>& couplages) {
    //Si on a plus de couplage que le nombre de noeuds/2 : false
    if (couplages.size() != graphe.nbVertices() / 2)
        return false;
    std::set<int> noeuds;
    for (Edge e : couplages) {
       // Si un des noeuds est déjà couplé : false
        if (noeuds.find(e.origin()) != noeuds.end() || noeuds.find(e.destination()) != noeuds.end()){
            return false;
        }
        noeuds.insert(e.origin());
        noeuds.insert(e.destination());
    }
    //Le graphe est parfait si on arrive ici
    return true;
}

/**
 * Parcours en largeur
 * pour l'algo de Hopcroft-Karp
 * https://en.wikipedia.org/wiki/Hopcroft-Karp_algorithm
 */
static std::set<int> ParcoursEnLargeur(const UnDiGraph& graphe, const std::vector<bool>& matched,  int moitie, const std::unordered_set<Edge, Edge::Hash>& arretesCouplees) {
    std::set<int>  defaut =  std::set<int>();

    std::vector<bool> visited(graphe.nbVertices(), false);

    std::queue<int> queue;
    for (int i = 0; i < moitie; i++) {
        if (!matched[i]) {
            queue.push(i);
            visited[i] = true;
        }
    }
    int restant = queue.size();
    bool soloFound = false;
    while (!queue.empty()) {
        int noeudActuel = queue.front();
        queue.pop();
        for (int i : graphe.adjacents(noeudActuel)) {
            if (!visited[i] && ((noeudActuel < moitie && arretesCouplees.find(Edge(noeudActuel, i)) == arretesCouplees.end()) || (noeudActuel >= moitie && arretesCouplees.find(Edge(i, noeudActuel)) != arretesCouplees.end()))) {
                queue.push(i);
                if (!matched[i]){
                    soloFound = true;
                }
            }
        }
        visited[noeudActuel] = true;
        
        if (--restant == 0) {
            if (soloFound) {
                std::set<int> vertex;
                while (!queue.empty()) {
                    vertex.insert(queue.front());
                    queue.pop();
                }
                return vertex;
            }
            restant = queue.size();
            soloFound = false;
        }
    }
    return defaut;
}

/**
 * Parcours en profondeur du graphe
 * pour l'algo de Hopcroft-Karp
 *
 */

static std::vector<int> ParcoursEnProfondeur(const UnDiGraph& graphe, const std::vector<bool>& matched, int moitie, const std::unordered_set<Edge, Edge::Hash>& arretesCouplees, int source, std::vector<bool>& visited) {
        std::vector<int> vide = std::vector<int>();
        visited[source] = true;
        for (int i : graphe.adjacents(source)) {
            if (!visited[i] && ((source >= moitie && arretesCouplees.find(Edge(i, source)) == arretesCouplees.end()) || (source < moitie && arretesCouplees.find(Edge(source, i)) != arretesCouplees.end()))) {
                if (i < moitie && !matched[i]){
                    return std::vector<int>(1, i);
                }
                std::vector<int> rec = ParcoursEnProfondeur(graphe, matched, moitie, arretesCouplees, i, visited);
                if (!rec.empty()) {
                    rec.push_back(i);
                    return rec;
                }
            }
        }

    return vide;
}
