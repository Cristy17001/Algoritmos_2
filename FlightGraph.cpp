#include <algorithm>
#include "FlightGraph.h"

FlightGraph::FlightGraph() = default;

void FlightGraph::AddNode(string code) {
    if (nodes_[code] == nullptr) {
        Node *node = new Node{code};
        nodes_[code] = node;
    }
}

void FlightGraph::AddEdge(string source, string target, string airline) {
    Node* source_node = nodes_[source];
    Edge edge = {target, airline};
    if (source_node->neighbors.find(edge) == source_node->neighbors.end()) {
        source_node->neighbors.insert(edge);
    }
}

vector<Node*> FlightGraph::BfsNFlights(Node* source, Node* target) {
    queue<Node*> q;
    // Stores the parent of a node first
    unordered_map<Node*, Node*> parent;
    q.push(source);
    source->visited = true;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // Verify if target as been reached
        if (current == target) {
            vector<Node*> path;
            while (current) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor: current->neighbors) {
            if (!nodes_[neighbor.node]->visited) {
                nodes_[neighbor.node]->visited = true;
                parent[nodes_[neighbor.node]] = current;
                q.push(nodes_[neighbor.node]);
            }
        }
    }

    return {};
}

unordered_map<string, Node*> FlightGraph::get_nodes() const {
    return nodes_;
}
