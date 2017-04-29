#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <unordered_set>
#include <stack>
#include <unordered_map>
#include "GraphMatching.h"
#include "UnDiGraph.h"

static int lca(std::vector<int>& match, std::vector<int>& base, std::vector<int>& p, int a, int b) {
    //std::cout << "in lca" << '\n';
    std::vector<bool> used(match.size());
    while (true) {
        //std::cout << "firts while" << '\n';
        a = base[a];
        used[a] = true;
        if (match[a] == -1) {
            break;
        }
        a = p[match[a]];
    }
    while (true) {
        //std::cout << "second while" << '\n';
        b = base[b];
        if (used[b]) {
            return b;
        }
        b = p[match[b]];
    }
}

static void markchemin(std::vector<int>& match, std::vector<int>& base, std::vector<bool>& blossom, std::vector<int>& p, int v, int b, int children) {
    //std::cout << "in markchemin" << '\n';
    while (base[v] != b) {
        //for (; base[v] != b; v = p[match[v]]) {
        blossom[base[v]] = blossom[base[match[v]]] = true;
        p[v] = children;
        children = match[v];
        v = p[match[v]];
    }
}

static int findchemin(const UnDiGraph& graph, std::vector<int>& match, std::vector<int>& p, int root) {
    //std::cout << "in find chemin" << '\n';
    int n = graph.nbVertices();
    std::vector<bool> used(n);
    std::vector<int> base(n);
    //std::vector<int> p(n, -1);
    for (int i = 0; i < n; ++i) {
        base[i] = i;
    }
    for (int i = 0; i < n; i++) {
        p[i] = -1;
    }

    used[root] = true;
    int qh = 0;
    int qt = 0;
    std::vector<int> q(n);
    q[qt++] = root;
    while (qh < qt) {
        int v = q[qh++];

        for (int to : graph.adjacents(v)) {
            if (base[v] == base[to] || match[v] == to) continue;
            if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                int curbase = lca(match, base, p, v, to);
                std::vector<bool> blossom(n);
                markchemin(match, base, blossom, p, v, curbase, to);
                markchemin(match, base, blossom, p, to, curbase, v);
                for (int i = 0; i < n; i++) {
                    if (blossom[base[i]]) {
                        base[i] = curbase;
                        if (!used[i]) {
                            used[i] = true;
                            q[qt++] = i;
                        }
                    }
                }
            } else if (p[to] == -1) {
                p[to] = v;
                if (match[to] == -1) {
                    return to;
                }
                to = match[to];
                used[to] = true;
                q[qt++] = to;
            }
        }
    }
    return -1;
}

std::vector<Edge> GraphMatching::CouplageMaximumGeneral(const UnDiGraph& graphe) {
    //std::cout << "in max matching" << '\n';
    int n = graphe.nbVertices();
    std::vector<int> match(n, -1);
    std::unordered_set<Edge, Edge::Hash> arretesCouplees;
    //std::vector<int> p(n, -1);
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        if (match[i] == -1) {
            int v = findchemin(graphe, match, p, i);
            while (v != -1) {
                int pv = p[v];
                int ppv = match[pv];
                if (match[v] != -1) {
                    if (v < match[v])
                        arretesCouplees.erase(Edge(v, match[v]));
                    else
                        arretesCouplees.erase(Edge(match[v], v));
                }
                if (match[pv] != -1) {
                    if (pv < match[pv])
                        arretesCouplees.erase(Edge(pv, match[pv]));
                    else
                        arretesCouplees.erase(Edge(match[pv], pv));
                }
                match[v] = pv;
                match[pv] = v;
                arretesCouplees.insert(Edge(pv, v));
                v = ppv;
            }
        }
    }

    return std::vector<Edge>(arretesCouplees.begin(), arretesCouplees.end());
}

/**
 * Does a Breadth First Search in the given graph, adapted for the Hopcroft-Karp
 * algorithm. This function ensure that the returned nodes are all source the same
 * level, and that the chemin found to reach them alternate between matched and
 * unmatched edges.
 * @param g The bipartite graph
 * @param matched The list of all the nodes, filled with true if the node is already matched
 * @param moitie The amount of nodes in the gauche side of the graph
 * @param arretesCouplees The set of already matched edges
 * @return A set of nodes, all at the same distance of the starting vertexes
 */
static std::set<unsigned int> ParcoursEnLargeur(const UnDiGraph& graphe,
        const std::vector<bool>& matched,
        unsigned int moitie,
        const std::unordered_set<Edge, Edge::Hash>& arretesCouplees) {
    std::set<unsigned int>  defaut =  std::set<unsigned int>();
    std::queue<unsigned int> queue;
    std::vector<bool> visited(graphe.nbVertices(), false);

    // Put the source nodes in the queue and mark them as visited
    for (unsigned int i = 0; i < moitie; i++) {
        if (!matched[i]) {
            queue.push(i);
            visited[i] = true;
        }
    }
    unsigned int restant = queue.size();
    bool soloFound = false;
    while (!queue.empty()) {
        unsigned int noeudActuel = queue.front();
        queue.pop();

        for (unsigned int i : graphe.adjacents(noeudActuel)) {
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
                std::set<unsigned int> vertex;
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
 * Does the actual work of the Depth First Search, adapted for Hopcroft-Karp
 * algorithm. See ParcoursEnProfondeur().
 */

static std::vector<unsigned int> ParcoursEnProfondeur_(const UnDiGraph& graphe,
        const std::vector<bool>& matched, unsigned int moitie,
        const std::unordered_set<Edge, Edge::Hash>& arretesCouplees,
        unsigned int source, std::vector<bool>& visited) {
        std::vector<unsigned int> vide = std::vector<unsigned int>();
        visited[source] = true;
        for (unsigned int i : graphe.adjacents(source)) {
            if (!visited[i] && ((source >= moitie && arretesCouplees.find(Edge(i, source)) == arretesCouplees.end()) || (source < moitie && arretesCouplees.find(Edge(source, i)) != arretesCouplees.end()))) {
                if (i < moitie && !matched[i]){
                    return std::vector<unsigned int>(1, i);
                }
                std::vector<unsigned int> test = ParcoursEnProfondeur_(graphe, matched, moitie, arretesCouplees, i, visited);
                if (!test.empty()) {
                    test.push_back(i);
                    return test;
                }
            }
        }

    return vide;
}

/**
 * Does a Depth First Search in the given graph, adapted for Hopcroft-Karp
 * algorithm. This function ensure that the returned chemin will alternate between
 * a matched edge and a non-matched one.
 * @param g The bipartite graph
 * @param matched A list of size corresponding to the amount of vertex in graphe,
 *  with true for the already matched vertexes
 * @param moitie The amount of nodes in the gauche side of the graph
 * @param arretesCouplees The list of already matched edges
 * @param source The node to start the search from
 * @return The chemin source the node to a free one (on the other side), or an empty set.
 */
static std::vector<unsigned int> ParcoursEnProfondeur(const UnDiGraph& graphe, const std::vector<bool>& matched, unsigned int moitie, const std::unordered_set<Edge, Edge::Hash>& arretesCouplees, unsigned int source) {
    std::vector<bool> visited(graphe.nbVertices(), false);

    std::vector<unsigned int> chemin = ParcoursEnProfondeur_(graphe, matched, moitie, arretesCouplees, source, visited); ;
    if (!chemin.empty())
        chemin.push_back(source);

    return chemin;
}

std::vector<Edge> GraphMatching::CouplageMaximumBiparti(const UnDiGraph& graphe, unsigned int moitie) {
    std::unordered_set<Edge, Edge::Hash> arretesCouplees;
    std::vector<bool> matched(graphe.nbVertices(), false);
    std::set<unsigned int> bfsResultSet = ParcoursEnLargeur(graphe, matched, moitie, arretesCouplees);
    while (!bfsResultSet.empty()) {
        for (unsigned int i : bfsResultSet) {
            // Trouve un chemin en utilisant l'algorithme de parcours en profondeur
            std::vector<unsigned int> chemin = ParcoursEnProfondeur(graphe, matched, moitie, arretesCouplees, i);
            // Reverse the matched edges in the chemin
            bool step = false;
            if (!chemin.empty())// Otherwise, with unsigned int, 0-1 is too big
                for (unsigned int j = 0; j < chemin.size() - 1; j++) {
                    unsigned int gauche = chemin[j];
                    unsigned int droite = chemin[j + 1];
                    if (gauche > droite) std::swap(gauche, droite);

                    if (step) arretesCouplees.erase(Edge(gauche, droite));
                    else arretesCouplees.insert(Edge(gauche, droite));
                    step = !step;
                    matched[gauche] = true;
                    matched[droite] = true;

                }
        }
        bfsResultSet = ParcoursEnLargeur(graphe, matched, moitie, arretesCouplees);
    }
    return std::vector<Edge>(arretesCouplees.begin(), arretesCouplees.end());
}

/**
 * Since a vertex can't be connected to two matched edges, there should be all
 * vertices exactly once, this means half as much edges.
 */
bool GraphMatching::CouplageParfait(const UnDiGraph& graphe, const std::vector<Edge>& couplages) {
    if (couplages.size() != graphe.nbVertices() / 2)
        return false;
    std::set<unsigned int> noeuds;
    for (Edge e : couplages) {
        if (noeuds.find(e.origin()) != noeuds.end() || noeuds.find(e.destination()) != noeuds.end()){
            return false;
        }
        noeuds.insert(e.origin());
        noeuds.insert(e.destination());
    }
    return true;
}
