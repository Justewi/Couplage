#include <stdio.h>
#include <string>
#include "Node.h"
#include <vector>

using namespace std;

class GraphBipartie{
public :
	vector<Node> partie1;
	vector<Node> partie2;
	void createGraph(double probabilite);
	void initializeVector(int nombre_noeuds_par_partie);




};
