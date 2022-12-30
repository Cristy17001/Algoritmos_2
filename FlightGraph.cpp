#include <algorithm>
#include "FlightGraph.h"
#include <iostream>

FlightGraph::FlightGraph() = default;

void FlightGraph::AddNode(string code) {
    if (nodes_[code] == nullptr) {
        Node *node = new Node{code};
        nodes_[code] = node;
    }
}

void FlightGraph::AddEdge(string source, string target, string airline) {
    Node* source_node = nodes_[source];
    if (!source_node->neighbors[target].empty()) {
        source_node->neighbors[target].push_back(airline);
    }
    else {
        source_node->neighbors[target] = {airline};
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
    int shortest_length = INT_MAX;
    vector<vector<Node*>> paths;

    while (!q.empty()) {
        // Current node
        Node* current = q.front().first;
        // Current path
        path = q.front().second;
        q.pop();

        if (current->code == target_name) {
            if (shortest_length == INT_MAX) {
                shortest_length = path.size();
            }
            if (shortest_length == INT_MAX || path.size() == shortest_length) {
                paths.push_back(path);
            }
            else if (path.size() < shortest_length) {
                paths.clear();
                paths.push_back(path);
                shortest_length = path.size();
            }
        }
        for (auto &neighbor: current->neighbors) {
            // Destination node
            string node = neighbor.first;
            Node *node_ptr = nodes_[node];
            if (node_ptr->n_visited == 0 || current->n_visited + 1 <= node_ptr->n_visited) {
                node_ptr->n_visited = current->n_visited + 1;
                vector<Node *> new_path = path;
                new_path.push_back(nodes_[node]);
                q.push({nodes_[node], new_path});
            }
        }
    }
    auto test = transformer(paths);
    return paths;
}

vector<vector<string>> FlightGraph::transformer(vector<vector<Node*>> paths) {
    vector<vector<string>> res;
    for (auto path: paths) {
        for (int i = 0; i < path.size() - 1; i++) {
            vector<string> airlines = path[i]->neighbors[path[i + 1]->code];
            if (res.empty()) {
                for (auto a: airlines) {
                    vector<string> aux;
                    aux.push_back(path[i]->code);
                    aux.push_back(a);
                    aux.push_back(path[i+1]->code);
                    res.push_back(aux);
                }
            }
            else {
                for (auto& s: res) {
                    auto& copy = s;
                    //std::remove(res.begin(), res.end(), s);
                    //res.pop_back();
                    for (auto a: airlines) {
                        vector<string> aux = copy;
                        aux.push_back(a);
                        aux.push_back(path[i+1]->code);
                        res.push_back(aux);
                    }
                }
            }
        }

    }
    return res;
}