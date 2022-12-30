#ifndef TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H
#define TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>

using namespace std;

struct Node {
    string code;
    // First field is the destination and the vector are the airlines from which it can travel
    unordered_map<string, vector<string>> neighbors;
    bool visited = false;
    int n_visited = 0;
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
    vector<vector<string>> transformer(vector<vector<Node*>> paths);
};

#endif
