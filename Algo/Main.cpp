#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "GraphBipartie.h"
#include <vector>

using namespace std;
int main(void){
	srand(time(NULL));
	GraphBipartie g;
	g.initializeVector(250);
	cout << "salut" << endl;
	g.createGraph(0.1);

	Node n = Node("lol");
	cout << n.id ;
	return 0;
}
