/*
 * UnDiGraph.cpp
 * Classe réutilisée du cours d'ADS en SI3
 * Alexandre BAR, Cyprien LEVY
 *
 */

#include <algorithm>

#include "UnDiGraph.h"

UnDiGraph::UnDiGraph(int n)
: _nbEdges(0), adjacencyList(n){
}

UnDiGraph::UnDiGraph(const UnDiGraph& orig)
: _nbEdges(orig._nbEdges), adjacencyList(orig.nbVertices()){
    for (int i = 0; i < orig.nbVertices(); i++){
        for (int j : orig.adjacents(i))
            adjacencyList[i].push_back(j);
    }
}

UnDiGraph::UnDiGraph(UnDiGraph&& orig)
: _nbEdges(orig._nbEdges), adjacencyList(std::move(orig.adjacencyList)){
};

UnDiGraph::~UnDiGraph(){
};

int UnDiGraph::nbVertices() const{
    return adjacencyList.size();
}

int UnDiGraph::nbEdges() const{
    return _nbEdges;
}

vector<int> UnDiGraph::adjacents(int u) const{
    return adjacencyList.at(u);
}

void UnDiGraph::addEdge(Edge e){
    addEdge(e.origin(), e.destination());
}

void UnDiGraph::removeEdge(Edge e){
    removeEdge(e.origin(), e.destination());
}

void UnDiGraph::addEdge(int u, int v){
    vector<int>& vector = adjacencyList.at(u);

    if (!(std::find(vector.begin(), vector.end(), v) != vector.end())){
        adjacencyList.at(u).push_back(v);
        adjacencyList.at(v).push_back(u);
        _nbEdges++;
    }
}

void UnDiGraph::removeEdge(int u, int v){
    vector<int>& uvector = adjacencyList.at(u);
    uvector.erase(std::remove(uvector.begin(), uvector.end(), v), uvector.end());

    vector<int>& vvector = adjacencyList.at(v);
    vvector.erase(std::remove(vvector.begin(), vvector.end(), u), vvector.end());
    _nbEdges--;
}

int UnDiGraph::degree(int u) const{
    return adjacencyList.at(u).size();
}

int UnDiGraph::addVertex(){
    adjacencyList.push_back(std::vector<int>());
    return adjacencyList.size() - 1;
}

UnDiGraph& UnDiGraph::operator=(const UnDiGraph& right){
    // Check for self-assignment!
    if (this == &right) // Same object?
        return *this; // Yes, so skip assignment, and just return *this.
    // Deallocate, allocate new space, copy values...
    _nbEdges = right._nbEdges;
    adjacencyList = vector<vector<int>>(right.nbVertices());
    for (int i = 0; i < right.nbVertices(); i++){
        for (int j : right.adjacents(i))
            adjacencyList[i].push_back(j);
    }
    return *this;
}
