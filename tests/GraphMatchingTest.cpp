
#include <vector>
#include <algorithm>

#include "../src/GraphMatching.h"

bool sanityCheck(UnDiGraph g, std::vector<Edge> result) {
    std::vector<bool> matched(g.nbVertices(), false);
    for (Edge e : result) {
        if (e.origin() < 0 || e.origin() >= g.nbVertices() ||
                e.destination() < 0 || e.destination() >= g.nbVertices()) {
            std::cout << "Got a weird edge:" << e << std::endl;
            return false;
        }
        if (matched[e.origin()] || matched[e.destination()]) {
            std::cout << "A vertice is in two matches." << std::endl;
            return false;
        }
        matched[e.origin()] = true;
        matched[e.destination()] = true;
    }
    return true;
}

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
    } else {
        std::cout << "bipartite_matching_multiple_iterations OK" << '\n';
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
    } else {
        std::cout << "bipartite_matching_two_left_options OK" << '\n';
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
    } else {
        std::cout << "bipartite_matching_all_on_one_right OK" << '\n';
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
    } else {
        std::cout << "bipartite_matching_disjoint OK" << '\n';
    }
}

void is_perfect_match_true() {
    UnDiGraph g(4);
    std::vector<Edge> result;
    result.push_back(Edge(0, 2));
    result.push_back(Edge(1, 3));
    if (!GraphMatching::IsPerfectMatch(g, result)) {
        std::cout << __func__ << " failed." << std::endl;
    } else {
        std::cout << "is_perfect_match_true OK" << '\n';
    }
}


// IsPerfectMatch

void is_perfect_match_false() {
    UnDiGraph g(4);
    std::vector<Edge> result;
    result.push_back(Edge(0, 2));
    if (GraphMatching::IsPerfectMatch(g, result)) {
        std::cout << __func__ << " failed." << std::endl;
    } else {
        std::cout << "is_perfect_match_false OK" << '\n';
    }
}

void is_perfect_match_not_even_a_match() {
    UnDiGraph g(4);
    std::vector<Edge> result;
    result.push_back(Edge(0, 2));
    result.push_back(Edge(1, 2));
    if (GraphMatching::IsPerfectMatch(g, result)) {
        std::cout << __func__ << " failed." << std::endl;
    } else {
        std::cout << "is_perfect_match_not_even_a_match OK" << '\n';
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
    if (result.size() != 2 || !sanityCheck(g, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "maximum_matching OK" << '\n';
    }
}

void maximum_matching_not_fully_connected() {
    UnDiGraph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    std::vector<Edge> result = GraphMatching::MaximumMatching(g);
    if (result.size() != 2 || !sanityCheck(g, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "maximum_matching_not_fully_connected OK" << '\n';
    }
}

void maximum_matching_star() {
    UnDiGraph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    std::vector<Edge> result = GraphMatching::MaximumMatching(g);
    if (result.size() != 1 || !sanityCheck(g, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "maximum_matching_star OK" << '\n';
    }
}

void maximum_matching_blossom() {
    UnDiGraph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);
    g.addEdge(3, 4);
    std::vector<Edge> result = GraphMatching::MaximumMatching(g);
    if (result.size() != 2 ||
            !sanityCheck(g, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "maximum_matching_blossom OK" << '\n';
    }
}

void bipartite_matching_multiple_iterations_g() {
    UnDiGraph graph(6);
    graph.addEdge(0, 3);
    graph.addEdge(0, 4);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);
    graph.addEdge(2, 4);

    std::vector<Edge> result = GraphMatching::MaximumMatching(graph);
    if (result.size() != 3 ||
            std::find(result.begin(), result.end(), Edge(0, 3)) == result.end() ||
            std::find(result.begin(), result.end(), Edge(1, 5)) == result.end() ||
            std::find(result.begin(), result.end(), Edge(2, 4)) == result.end() ||
            !sanityCheck(graph, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "bipartite_matching_multiple_iterations OK" << '\n';
    }
}

void bipartite_matching_two_left_options_g() {
    UnDiGraph graph(4);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    std::vector<Edge> result = GraphMatching::MaximumMatching(graph);
    if (result.size() != 1 ||
            std::find(result.begin(), result.end(), Edge(0, 2)) == result.end() ||
            !sanityCheck(graph, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "bipartite_matching_two_left_options OK" << '\n';
    }
}

void bipartite_matching_all_on_one_right_g() {
    UnDiGraph graph(4);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    std::vector<Edge> result = GraphMatching::MaximumMatching(graph);
    if (result.size() != 1 ||
            std::find(result.begin(), result.end(), Edge(0, 2)) == result.end() ||
            !sanityCheck(graph, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "bipartite_matching_all_on_one_right OK" << '\n';
    }
}

void bipartite_matching_disjoint_g() {
    UnDiGraph graph(4);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    std::vector<Edge> result = GraphMatching::MaximumMatching(graph);
    if (result.size() != 2 ||
            std::find(result.begin(), result.end(), Edge(0, 2)) == result.end() ||
            std::find(result.begin(), result.end(), Edge(1, 3)) == result.end() ||
            !sanityCheck(graph, result)) {
        std::cout << __func__ << " failed:" << std::endl;
        for (Edge e : result)
            std::cout << e << std::endl;
    } else {
        std::cout << "bipartite_matching_disjoint OK" << '\n';
    }
}