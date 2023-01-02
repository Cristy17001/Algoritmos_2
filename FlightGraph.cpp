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
    // Clear the n_visited flag
    for (auto& e: nodes_) {e.second->n_visited = 0;}
    return paths;
}

vector<vector<string>> FlightGraph::transformer(vector<vector<Node*>> paths) {
    vector<vector<string>> res;
    for (auto path: paths) {
        vector<vector<string>> new_paths;
        new_paths.push_back({path[0]->code});
        for (int i = 0; i < path.size() - 1; i++) {
            string source = path[i]->code;
            string target = path[i + 1]->code;
            vector<string> airlines = path[i]->neighbors[target];
            vector<vector<string>> updated_paths;
            for (auto p: new_paths) {
                for (auto a: airlines) {
                    vector<string> current_path = p;
                    current_path.push_back(a);
                    current_path.push_back(target);
                    updated_paths.push_back(current_path);
                }
            }
            new_paths = updated_paths;
        }
        res.insert(res.end(), new_paths.begin(), new_paths.end());
    }
    return res;
}

unordered_set<string> FlightGraph::BfsNflights(string airport, int n_flights) {
    Node* node = nodes_[airport];
    queue<Node*> q;
    unordered_set<string> res;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front(); q.pop();
        if (current->n_visited <= n_flights && current->n_visited != 0) {
            res.insert(current->code);
        }

        for (auto& neighbor: current->neighbors) {
            Node* neighbor_ptr = nodes_[neighbor.first];
            if (neighbor_ptr->n_visited <= n_flights && neighbor_ptr->n_visited == 0 && neighbor_ptr != node) {
                neighbor_ptr->n_visited = current->n_visited + 1;
                q.push(neighbor_ptr);
            }
        }
    }
    // Clear the n_visited flag
    for (auto& e: nodes_) {e.second->n_visited = 0;}
    return res;
}


int FlightGraph::n_flights(string airport) {
    auto airport_ptr = nodes_[airport];
    return airport_ptr->neighbors.size();
}

int FlightGraph::diff_airline(std::string airport) {
    Node* airport_ptr = nodes_[airport];
    auto neighbors = airport_ptr->neighbors;
    // Unordered set for insertion and searching with O(1) complexity
    unordered_set<string> aux;
    for (auto n: neighbors) {
        for (string str: n.second) {
            aux.insert(str);
        }
    }
    return aux.size();
}

int FlightGraph::n_diff_dest(string airport) {
    Node* airport_ptr = nodes_[airport];
    return nodes_[airport]->neighbors.size();
}

vector<string> FlightGraph::diff_dest(string airport) {
    Node* airport_ptr = nodes_[airport];
    vector<string> diff_airports;
    for (auto [airport, airlines]: nodes_[airport]->neighbors) {
        diff_airports.push_back(airport);
    }
    return diff_airports;
}