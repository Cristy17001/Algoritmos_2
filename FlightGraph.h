#ifndef TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H
#define TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct Node {
    string code;
    bool visited = false;
    vector<Node*> neighbors;
    int n_flights = 0;
};

class FlightGraph {

private:
    unordered_map<string, Node*> nodes_;

public:
    FlightGraph();
    void AddNode(string code);
    void AddEdge(string source, string target);
    vector<Node*> BfsNFlights(Node* source, Node* target);
};

#endif
