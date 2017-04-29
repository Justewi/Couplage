#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <unordered_set>
#include <stack>
#include <unordered_map>
#include "GraphMatching.h"
#include "UnDiGraph.h"

static int lca(std::vector<int>& match, std::vector<int>& base, std::vector<int>& p, int a, int b) {
    //std::cout << "in lca" << '\n';
    std::vector<bool> used(match.size());
    while (true) {
        //std::cout << "firts while" << '\n';
        a = base[a];
        used[a] = true;
        if (match[a] == -1) {
            break;
        }
        a = p[match[a]];
    }
    while (true) {
        //std::cout << "second while" << '\n';
        b = base[b];
        if (used[b]) {
            return b;
        }
        b = p[match[b]];
    }
}

static void markPath(std::vector<int>& match, std::vector<int>& base, std::vector<bool>& blossom, std::vector<int>& p, int v, int b, int children) {
    //std::cout << "in markPath" << '\n';
    while (base[v] != b) {
        //for (; base[v] != b; v = p[match[v]]) {
        blossom[base[v]] = blossom[base[match[v]]] = true;
        p[v] = children;
        children = match[v];
        v = p[match[v]];
    }
}

static int findPath(const UnDiGraph& graph, std::vector<int>& match, std::vector<int>& p, int root) {
    //std::cout << "in find path" << '\n';
    int n = graph.nbVertices();
    std::vector<bool> used(n);
    std::vector<int> base(n);
    //std::vector<int> p(n, -1);
    for (int i = 0; i < n; ++i) {
        base[i] = i;
    }
    for (int i = 0; i < n; i++) {
        p[i] = -1;
    }

    used[root] = true;
    int qh = 0;
    int qt = 0;
    std::vector<int> q(n);
    q[qt++] = root;
    while (qh < qt) {
        int v = q[qh++];

        for (int to : graph.adjacents(v)) {
            if (base[v] == base[to] || match[v] == to) continue;
            if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                int curbase = lca(match, base, p, v, to);
                std::vector<bool> blossom(n);
                markPath(match, base, blossom, p, v, curbase, to);
                markPath(match, base, blossom, p, to, curbase, v);
                for (int i = 0; i < n; i++) {
                    if (blossom[base[i]]) {
                        base[i] = curbase;
                        if (!used[i]) {
                            used[i] = true;
                            q[qt++] = i;
                        }
                    }
                }
            } else if (p[to] == -1) {
                p[to] = v;
                if (match[to] == -1) {
                    return to;
                }
                to = match[to];
                used[to] = true;
                q[qt++] = to;
            }
        }
    }
    return -1;
}

std::vector<Edge> GraphMatching::MaximumMatching(const UnDiGraph& g) {
    //std::cout << "in max matching" << '\n';
    int n = g.nbVertices();
    std::vector<int> match(n, -1);
    std::unordered_set<Edge, Edge::Hash> matchedEdges;
    //std::vector<int> p(n, -1);
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        if (match[i] == -1) {
            int v = findPath(g, match, p, i);
            while (v != -1) {
                int pv = p[v];
                int ppv = match[pv];
                if (match[v] != -1) {
                    if (v < match[v])
                        matchedEdges.erase(Edge(v, match[v]));
                    else
                        matchedEdges.erase(Edge(match[v], v));
                }
                if (match[pv] != -1) {
                    if (pv < match[pv])
                        matchedEdges.erase(Edge(pv, match[pv]));
                    else
                        matchedEdges.erase(Edge(match[pv], pv));
                }
                match[v] = pv;
                match[pv] = v;
                matchedEdges.insert(Edge(pv, v));
                v = ppv;
            }
        }
    }

    return std::vector<Edge>(matchedEdges.begin(), matchedEdges.end());
}

/**
 * Does a Breadth First Search in the given graph, adapted for the Hopcroft-Karp
 * algorithm. This function ensure that the returned nodes are all from the same
 * level, and that the path found to reach them alternate between matched and
 * unmatched edges.
 * @param g The bipartite graph
 * @param matched The list of all the nodes, filled with true if the node is already matched
 * @param median The amount of nodes in the left side of the graph
 * @param matchedEdges The set of already matched edges
 * @return A set of nodes, all at the same distance of the starting vertexes
 */
static std::set<unsigned int> BFS(const UnDiGraph& g,
        const std::vector<bool>& matched,
        unsigned int median,
        const std::unordered_set<Edge, Edge::Hash>& matchedEdges) {
    std::queue<unsigned int> queue;
    std::vector<bool> visited(g.nbVertices(), false);

    // Put the source nodes in the queue and mark them as visited
    for (unsigned int i = 0; i < median; i++) {
        if (!matched[i]) {
            queue.push(i);
            visited[i] = true;
        }
    }
    unsigned int left = queue.size();
    bool hasFoundUnmatched = false;
    while (!queue.empty()) {
        unsigned int current = queue.front();
        queue.pop();

        for (unsigned int i : g.adjacents(current)) {
            if (!visited[i]
                    && ((current < median && matchedEdges.find(Edge(current, i)) == matchedEdges.end())
                    || (current >= median && matchedEdges.find(Edge(i, current)) != matchedEdges.end()))) {
                queue.push(i);
                if (!matched[i])
                    hasFoundUnmatched = true;
            }
        }
        visited[current] = true;

        // Early stop when finding a stage where there is an unmatched vertex
        if (--left == 0) {
            if (hasFoundUnmatched) {
                std::set<unsigned int> v;
                while (!queue.empty()) {
                    v.insert(queue.front());
                    queue.pop();
                }
                return v;
            }
            left = queue.size();
            hasFoundUnmatched = false;
        }
    }
    return std::set<unsigned int>();
}

/**
 * Does the actual work of the Depth First Search, adapted for Hopcroft-Karp
 * algorithm. See DFS().
 */
static std::vector<unsigned int> DFS_(const UnDiGraph& g,
        const std::vector<bool>& matched, unsigned int median,
        const std::unordered_set<Edge, Edge::Hash>& matchedEdges,
        unsigned int from, std::vector<bool>& visited) {
    visited[from] = true;

    for (unsigned int i : g.adjacents(from)) {
        if (!visited[i]
                && ((from < median && matchedEdges.find(Edge(from, i)) != matchedEdges.end())
                || (from >= median && matchedEdges.find(Edge(i, from)) == matchedEdges.end()))) {
            if (!matched[i] && i < median)
                return std::vector<unsigned int>(1, i);
            std::vector<unsigned int> tmp = DFS_(g, matched, median, matchedEdges, i, visited);
            if (!tmp.empty()) {
                tmp.push_back(i);
                return tmp;
            }
        }
    }
    return std::vector<unsigned int>();
}

/**
 * Does a Depth First Search in the given graph, adapted for Hopcroft-Karp
 * algorithm. This function ensure that the returned path will alternate between
 * a matched edge and a non-matched one.
 * @param g The bipartite graph
 * @param matched A list of size corresponding to the amount of vertex in g,
 *  with true for the already matched vertexes
 * @param median The amount of nodes in the left side of the graph
 * @param matchedEdges The list of already matched edges
 * @param from The node to start the search from
 * @return The path from the node to a free one (on the other side), or an empty set.
 */
static std::vector<unsigned int> DFS(const UnDiGraph& g, const std::vector<bool>& matched, unsigned int median, const std::unordered_set<Edge, Edge::Hash>& matchedEdges, unsigned int from) {
    std::vector<bool> visited(g.nbVertices(), false);
    std::vector<unsigned int> path = DFS_(g, matched, median, matchedEdges, from, visited);
    if (!path.empty())
        path.push_back(from);
    return path;
}

std::vector<Edge> GraphMatching::MaximumBipartite(const UnDiGraph& g, unsigned int median) {
    std::vector<bool> matched(g.nbVertices(), false);
    std::unordered_set<Edge, Edge::Hash> matchedEdges;
    std::set<unsigned int> bfsResult = BFS(g, matched, median, matchedEdges);
    while (!bfsResult.empty()) {
        // We can match those nodes, so do it
        for (unsigned int i : bfsResult) {
            // Find a path from i to a left node
            std::vector<unsigned int> path = DFS(g, matched, median, matchedEdges, i);
            // Reverse the matched edges in the path
            bool step = false;
            if (!path.empty())// Otherwise, with unsigned int, 0-1 is too big
                for (unsigned int j = 0; j < path.size() - 1; j++) {
                    unsigned int left = path[j];
                    unsigned int right = path[j + 1];
                    if (left > right) std::swap(left, right);

                    if (step) matchedEdges.erase(Edge(left, right));
                    else matchedEdges.insert(Edge(left, right));
                    matched[left] = true;
                    matched[right] = true;
                    step = !step;
                }
        }
        bfsResult = BFS(g, matched, median, matchedEdges);
    }
    return std::vector<Edge>(matchedEdges.begin(), matchedEdges.end());
}

/**
 * Since a vertex can't be connected to two matched edges, there should be all
 * vertices exactly once, this means half as much edges.
 */
bool GraphMatching::IsPerfectMatch(const UnDiGraph& g, const std::vector<Edge>& match) {
    if (match.size() != g.nbVertices() / 2)
        return false;
    std::set<unsigned int> nodes;
    for (Edge e : match) {
        if (nodes.find(e.origin()) != nodes.end()
                || nodes.find(e.destination()) != nodes.end())
            return false;
        nodes.insert(e.origin());
        nodes.insert(e.destination());
    }
    return true;
}
