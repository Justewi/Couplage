
#include <vector>
#include <algorithm>

#include "../src/GraphMatching.h"

void bipartite_matching_multiple_iterations() {
    UnDiGraph graph(6);
    graph.addEdge(0, 3);
    graph.addEdge(0, 4);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);
    graph.addEdge(2, 4);

    std::vector<Edge> result = GraphMatching::MaximumBipartite(graph, 3);
    if (result.size() != 3 ||
            std::find(result.begin(), result.end(), Edge(0, 3)) == result.end() ||
            std::find(result.begin(), result.end(), Edge(1, 5)) == result.end() ||
            std::find(result.begin(), result.end(), Edge(2, 4)) == result.end()) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

void bipartite_matching_two_left_options() {
    UnDiGraph graph(4);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    std::vector<Edge> result = GraphMatching::MaximumBipartite(graph, 2);
    if (result.size() != 1 ||
            std::find(result.begin(), result.end(), Edge(0, 2)) == result.end()) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

void bipartite_matching_all_on_one_right() {
    UnDiGraph graph(4);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    std::vector<Edge> result = GraphMatching::MaximumBipartite(graph, 2);
    if (result.size() != 1 ||
            std::find(result.begin(), result.end(), Edge(0, 2)) == result.end()) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

void bipartite_matching_disjoint() {
    UnDiGraph graph(4);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    std::vector<Edge> result = GraphMatching::MaximumBipartite(graph, 2);
    if (result.size() != 2 ||
            std::find(result.begin(), result.end(), Edge(0, 2)) == result.end() ||
            std::find(result.begin(), result.end(), Edge(1, 3)) == result.end()) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

void is_perfect_match_true() {
    UnDiGraph g(4);
    std::vector<Edge> result;
    result.push_back(Edge(0, 2));
    result.push_back(Edge(1, 3));
    if (!GraphMatching::IsPerfectMatch(g, result)) {
        std::cout << __func__ << " failed." << std::endl;
    }
}


// IsPerfectMatch

void is_perfect_match_false() {
    UnDiGraph g(4);
    std::vector<Edge> result;
    result.push_back(Edge(0, 2));
    if (GraphMatching::IsPerfectMatch(g, result)) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

void is_perfect_match_not_even_a_match() {
    UnDiGraph g(4);
    std::vector<Edge> result;
    result.push_back(Edge(0, 2));
    result.push_back(Edge(1, 2));
    if (GraphMatching::IsPerfectMatch(g, result)) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

//GraphMatching::MaximumMatching

void maximum_matching() {
    UnDiGraph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    std::vector<Edge> result = GraphMatching::MaximumMatching(g);
    if (result.size() != 2) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

void maximum_matching_not_fully_connected() {
    UnDiGraph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    std::vector<Edge> result = GraphMatching::MaximumMatching(g);
    if (result.size() != 2) {
        std::cout << __func__ << " failed." << std::endl;
    }
}

void maximum_matching_star() {
    UnDiGraph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    std::vector<Edge> result = GraphMatching::MaximumMatching(g);
    if (result.size() != 1) {
        std::cout << __func__ << " failed." << std::endl;
    }
}