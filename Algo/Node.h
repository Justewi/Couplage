#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Node{
public :
	string id;
	vector<Node> voisins;

	Node(string ide){
		id = ide;
	};

	void addvoisin(Node n);

	friend ostream& operator <<(ostream& Stream, const Node& Obj){
	    Stream << Obj.id ;
	    return Stream; // N'oubliez pas de renvoyer le flux, afin de pouvoir chaîner les appels
	}
};
