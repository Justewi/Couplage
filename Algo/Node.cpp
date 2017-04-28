#include <stdio.h>
#include <string>
#include "Node.h"
#include <vector>

using namespace std;

void Node::addvoisin(Node n){
	voisins.push_back(n);
	n.voisins.push_back(*this);
};
