#include <stdio.h>
#include <string>
#include <iostream>
#include "GraphBipartie.h"
#include <vector>

using namespace std;


void GraphBipartie::initializeVector(int nombre_noeuds_par_partie){
	for ( int i = 0; i<nombre_noeuds_par_partie; i++){
		partie1.push_back(Node("n1-" + to_string((2*i))));
		partie2.push_back(Node("n2-" + to_string((2*i+1))));

	}
	for ( int i = 0; i<nombre_noeuds_par_partie; i++){
		cout << partie1.at(i).id;
		cout << partie2.at(i) << endl;
	}

}
void GraphBipartie::createGraph(double probabilite){

	for (Node n1 : partie1) {
		for (Node n2 : partie2) {
			if (rand()/RAND_MAX < probabilite){
				n1.addvoisin(n2);

			}
		}
	}

}
