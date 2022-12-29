#ifndef TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H
#define TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

struct Edge {
    string node;
    string airline;
};

struct EdgeHash {
    size_t operator()(const Edge& e) const {
        size_t h1 = std::hash<string>()(e.node);
        size_t h2 = std::hash<string>()(e.airline);
        return h1 ^ h2;
    }
};

struct EdgeEqual {
    bool operator()(const Edge& e1, const Edge& e2) const {
        return e1.node == e2.node && e1.airline == e2.airline;
    }
};

struct Node {
    string code;
    bool visited = false;
    unordered_set<Edge, EdgeHash, EdgeEqual> neighbors;
    int n_flights = 0;
};


class FlightGraph {

private:
    unordered_map<string, Node*> nodes_;

public:
    FlightGraph();
    void AddNode(string code);
    void AddEdge(string source, string target, string airline);
    unordered_map<string, Node*> get_nodes() const;
    vector<vector<Node*>> BfsShortestPaths(string source_name, string target_name);
};

#endif
