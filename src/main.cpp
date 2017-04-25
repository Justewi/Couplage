#include <iostream>
#include <cstdlib>
#include <random>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <cstring>

#include "RandomGraphBuilder.h"
#include "GraphMatching.h"

static unsigned int threadCount = 0;
static std::mutex threadCountMutex;
static std::condition_variable cv;

enum TypeGraph {GENERAL, BIPARTI};

void compute(TypeGraph type, unsigned int repeat, float p, unsigned int nbNodes, unsigned int& result) {
	// We need to start this one only once, since windows has no entropy
	std::random_device rand;
	result = 0;
	std::cout << "in compute function" << '\n';
	std::cout << "type: " << type << '\n';
	for (unsigned int i = 0; i < repeat; i++) {
		if(type == BIPARTI){
			//std::cout << "in if biparti" << '\n';
			UnDiGraph graph = RandomGraphBuilder::RandomBipartiteGraph(nbNodes, nbNodes, p, rand);
			if (GraphMatching::IsPerfectMatch(graph, GraphMatching::MaximumBipartite(graph, nbNodes))) {
				//std::cout << "in is perfect match" << '\n';
				result++;
			}
		} else {
			UnDiGraph graph = RandomGraphBuilder::RandomGraph(nbNodes, p, rand);
			if (GraphMatching::IsPerfectMatch(graph, GraphMatching::MaximumMatching(graph))) {
				result++;
			}
		}

		//std::cout << '\r' << p << ':' << i << " - " << ((float) result / (i + 1)) << std::endl;
	}
	{ // Critical section
		std::unique_lock<std::mutex> lk(threadCountMutex);
		threadCount--;
		cv.notify_one();
	}
}

int main(int argc, char** argv) {
	// - - - - - Argument parsing
	if (argc < 4 || argc > 8) {
		std::cerr << "Invalid amount of parameters." << std::endl
				<< "Usage: " << argv[0] << "Type_of_graph Number_of_nodes step [min_p max_p max_thread nb_repeat]" << std::endl;
		return 0;
	}

	TypeGraph type;
	std::cout << "type graphe arg1: " << argv[1] << '\n';
	if((std::strcmp(argv[1], "g") == 0) || (std::strcmp(argv[1], "general") == 0)){
		std::cout << "this is general graphe" << '\n';
		type = TypeGraph::GENERAL;
	}
	else if ((std::strcmp(argv[1], "b") == 0) || (std::strcmp(argv[1], "biparti") == 0)){
		std::cout << "this is bipartie graphe" << '\n';
		type = TypeGraph::BIPARTI;
	}
	else{
		std::cerr << "Invalid value for Type_of_graph: " << argv[1] << ". Expected (g | general) for general graph or (b | biparti) for bipartite graph." << std::endl;
		return 1;
	}

	unsigned int nbNodes = std::atoi(argv[2]);
	if (nbNodes <= 0) {
		std::cerr << "Invalid value for Number_of_nodes: " << nbNodes << ". Expected a positive integer." << std::endl;
		return 1;
	}
	float step = std::atof(argv[3]);
	if (step <= 0 || step > 1) {
		std::cerr << "Invalid value for step: " << step << ". Expected a floating point value in (0;1]." << std::endl;
		return 1;
	}
	float minP = 0;
	if (argc > 4) {
		minP = std::atof(argv[4]);
		if (minP < 0 || minP >= 1) {
			std::cerr << "Invalid value for min_p: " << minP << ". Expected a decimal value in [0;1)." << std::endl;
			return 1;
		}
	}
	float maxP = 1;
	if (argc > 5) {
		maxP = std::atof(argv[5]);
		if (maxP <= 0 || maxP > 1) {
			std::cerr << "Invalid value for max_p: " << maxP << ". Expected a decimal value in (0;1]." << std::endl;
			return 1;
		}
	}

	// Try to determine the amount of avaiable threads, or default to 4
	unsigned int nbThreads = std::thread::hardware_concurrency();
	if (argc > 6) {
		nbThreads = std::atoi(argv[6]);
		if (nbThreads < 0) {
			std::cerr << "Invalid value for max_thread: " << nbThreads
					<< ". Expected a positive value." << std::endl;
			return 1;
		}
	}
	if (nbThreads == 0) nbThreads = 4;

	unsigned int repeat = 100;
	if (argc > 7) {
		repeat = std::atoi(argv[7]);
		if (repeat < 0) {
			std::cerr << "Invalid value for nb_repeat: " << repeat
					<< ". Expected a positive value." << std::endl;
			return 1;
		}
	}

	// - - - - - Actual work
	std::vector<std::pair<float, unsigned int>> results((maxP - minP) / step, std::pair<float, unsigned int>(0, 0));
	std::cout << "in main after parsing" << '\n';

	for (unsigned int i = 1; i * step + minP < maxP; i++) {
		std::cout << "in for after parsing" << '\n';
		results[i].first = i * step + minP;
		{ // Critical section
			std::unique_lock<std::mutex> lk(threadCountMutex);
			cv.wait(lk, [nbThreads]() {
				return threadCount<nbThreads;
			});
			threadCount++;
		}
		std::cout << "in for: before thread" << '\n';
		std::thread(compute, type, repeat, results[i].first, nbNodes, std::ref(results[i].second)).detach();
	}
	{ // Critical section
		std::unique_lock<std::mutex> lk(threadCountMutex);
		cv.wait(lk, []() {
			return threadCount == 0;
		});
	}
	std::cout << " - - - - - Results:" << std::endl;
	std::cout << nbNodes << "," << repeat << "," << step << "," << minP << "," << maxP << std::endl;

	for (std::pair<float, unsigned int> i : results) {
		std::cout << i.first << "," << i.second << "," << ((float) i.second / repeat) << std::endl;
	}

	return 0;
}
