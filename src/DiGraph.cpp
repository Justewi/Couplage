#include "DiGraph.h"
#include "Edge.h"

DiGraph::DiGraph(unsigned int nbVertex)
: adjacency(nbVertex, std::vector<int>(nbVertex)), _nbEdges(0){
}

DiGraph::DiGraph(const DiGraph& orig){
}

DiGraph::~DiGraph(){
}

unsigned int DiGraph::nbVertices() const{
    return adjacency.size();
}

unsigned int DiGraph::nbEdges() const{
    return _nbEdges;
}

void DiGraph::addEdge(Edge e){
    addEdge(e.origin(), e.destination());
}

void DiGraph::removeEdge(Edge e){
    removeEdge(e.origin(), e.destination());
}

void DiGraph::addEdge(unsigned int orig, unsigned int dest){
    adjacency[orig][dest] = 1;
}

void DiGraph::removeEdge(unsigned int orig, unsigned int dest){
    adjacency[orig][dest] = 0;
}

unsigned int DiGraph::addVertex(){
    adjacency.push_back(std::vector<int>(adjacency.size() - 1));
    for (auto it : adjacency){
        it.push_back(0);
    }
}