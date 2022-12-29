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

unordered_map<string, Node*> FlightGraph::get_nodes() const {
    return nodes_;
}

vector<vector<Node*>> FlightGraph::BfsShortestPaths(string source_name, string target_name) {
    queue<pair<Node*, vector<Node*>>> q;
    Node* source = nodes_[source_name];
    Node* target = nodes_[target_name];
    vector<Node*> path;
    path.push_back(source);
    q.push({source, path});

    vector<vector<Node*>> paths;
    int shortest_path_length = -1;

    while (!q.empty()) {
        Node* current = q.front().first;
        path = q.front().second;
        q.pop();

        // Verify if target as been reached
        if (current == target) {
            if (shortest_path_length == -1 || path.size() == shortest_path_length) {
                paths.push_back(path);
                if (shortest_path_length == -1) {
                    shortest_path_length = path.size();
                }
            } else if (path.size() < shortest_path_length) {
                paths.clear();
                paths.push_back(path);
                shortest_path_length = path.size();
            }
        } else {
            // Default BFS search marking as visited
            for (const auto& neighbor: current->neighbors) {
                if (!nodes_[neighbor.node]->visited) {
                    nodes_[neighbor.node]->visited = true;
                    vector<Node*> new_path = path;
                    new_path.push_back(nodes_[neighbor.node]);
                    q.push({nodes_[neighbor.node], new_path});
                }
            }
        }
    }

    return paths;
}






