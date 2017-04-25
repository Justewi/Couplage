/*
 * UnDiGraph.cpp
 *
 *  Created on: 5 mars 2017
 *      Authors: Alexis Metge, Liavona Zheltanosava, Gaspard lacroix
 */

#include <algorithm>

#include "UnDiGraph.h"

UnDiGraph::UnDiGraph(unsigned int n)
: _nbEdges(0), adjacencyList(n){
}

UnDiGraph::UnDiGraph(const UnDiGraph& orig)
: _nbEdges(orig._nbEdges), adjacencyList(orig.nbVertices()){
    for (unsigned int i = 0; i < orig.nbVertices(); i++){
        for (unsigned int j : orig.adjacents(i))
            adjacencyList[i].push_back(j);
    }
}

UnDiGraph::UnDiGraph(UnDiGraph&& orig)
: _nbEdges(orig._nbEdges), adjacencyList(std::move(orig.adjacencyList)){
};

UnDiGraph::~UnDiGraph(){
};

unsigned int UnDiGraph::nbVertices() const{
    return adjacencyList.size();
}

unsigned int UnDiGraph::nbEdges() const{
    return _nbEdges;
}

vector<unsigned int> UnDiGraph::adjacents(unsigned int u) const{
    return adjacencyList.at(u);
}

void UnDiGraph::addEdge(Edge e){
    addEdge(e.origin(), e.destination());
}

void UnDiGraph::removeEdge(Edge e){
    removeEdge(e.origin(), e.destination());
}

void UnDiGraph::addEdge(unsigned int u, unsigned int v){
    vector<unsigned int>& vector = adjacencyList.at(u);

    if (!(std::find(vector.begin(), vector.end(), v) != vector.end())){
        adjacencyList.at(u).push_back(v);
        adjacencyList.at(v).push_back(u);
        _nbEdges++;
    }
}

void UnDiGraph::removeEdge(unsigned int u, unsigned int v){
    vector<unsigned int>& uvector = adjacencyList.at(u);
    uvector.erase(std::remove(uvector.begin(), uvector.end(), v), uvector.end());

    vector<unsigned int>& vvector = adjacencyList.at(v);
    vvector.erase(std::remove(vvector.begin(), vvector.end(), u), vvector.end());
    _nbEdges--;
}

unsigned int UnDiGraph::degree(unsigned int u) const{
    return adjacencyList.at(u).size();
}

unsigned int UnDiGraph::addVertex(){
    adjacencyList.push_back(std::vector<unsigned int>());
    return adjacencyList.size() - 1;
}

UnDiGraph& UnDiGraph::operator=(const UnDiGraph& right){
    // Check for self-assignment!
    if (this == &right) // Same object?
        return *this; // Yes, so skip assignment, and just return *this.
    // Deallocate, allocate new space, copy values...
    _nbEdges = right._nbEdges;
    adjacencyList = vector<vector<unsigned int>>(right.nbVertices());
    for (unsigned int i = 0; i < right.nbVertices(); i++){
        for (unsigned int j : right.adjacents(i))
            adjacencyList[i].push_back(j);
    }
    return *this;
}
