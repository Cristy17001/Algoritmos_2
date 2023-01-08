#ifndef TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H
#define TRABALHO_ALGORITMOS_2_FLIGHTGRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>

using namespace std;

/**
 * \struct Node
 * \brief Nodes of the FlightGraph.
 *
 * Designed for the capability of storing data of every flight, including
 * \param code - the airport of origin
 * \param neighbors - unordered_map capable of storing the destination airport and the possible airlines to achieve it, and insertion of them in O(1) time complexity
 * \param n_visited - auxiliary counter for the design of the BFS
 *
 * \see FlightGraph
 */
struct Node {
    string code;
    // First field is the destination and the vector are the airlines from which it can travel
    unordered_map<string, vector<string>> neighbors;
    int n_visited = 0;
};


/**
 * \class FlightGraph
 * \brief Graph storing every flight possibility.
 *
 * Designed for node access in O(1) time complexity, by using unordered_map<string, Node*> for node access.
 * Simple directed graph with implementations of BFS to find shortest path between two airports.
 *
 * \note This class was designed to be used by the manager class.
 * \see Manager
 */
class FlightGraph {

private:
    unordered_map<string, Node*> nodes_;

public:
    FlightGraph();
    /**
     * \brief Adds a new node.
     *
     * Creates a new node* if the airport isn't yet in the map ignores otherwise
     * \param code - airport code
     *
     */
    void AddNode(const string& code);

    /**
      * \brief Adds a link from source node to target node.
      *
      * Adds a new destination node to source neighbors. If the link already existed then adds the airline, otherwise creates a new link by adding to neighbors map the target node with the airline
      *
      * \param source source airport.
      * \param target target airport.
      * \param airline airline from source to target
      *
      *
      */
    void AddEdge(const string& source, const string& target, const string& airline);
    unordered_map<string, Node*> get_nodes() const;

    /**
      * \brief Performs BFS search for the shortest paths.
      *
      * Performs a breadth-first search (BFS) on a graph and keeps track of the path taken through the graph during the search.
      * The function also checks if the target node is found during the search, and if it is found, the path taken to reach the target node is added to a return vector of paths.
      * This search as a time complexity of O(n + e) where n is the number of nodes and e is the number of edges
      *
      * \param source_name source airport.
      * \param target_name target airport.
      *
      * \return Shortest paths from the source airport to the target airport stored in a vector<vector<Node*>>
      */
    vector<vector<Node*>> BfsShortestPaths(const string& source_name, const string& target_name);

    /**
      * \brief Transforms the paths in to a readable format.
      *
      * Transforms the vector<vector<Node*>> receive from the BFS into to vector<vector<string>> while also adding every possible airline combination for the specific path.
      * Therefore having a time complexity of O(n*m) being n the number of paths and m the number of nodes in each path
      *
      * \param paths all possible path received from the BfsShortestPaths.
      *
      * \return Shortest paths in format [Origin, airline1, stopage1, airline2, Destination] as a vector<vector<string>>.
      */
    static vector<vector<string>> transformer(const vector<vector<Node*>>& paths);

    /**
      * \brief Performs BFS search with n_flights
      *
      * Performs a breadth-first search (BFS) on a graph to find all nodes that can be reached from a given starting node in a maximum of n_flights.
      * The time complexity of this function is O(n + m), where n is the number of nodes in the graph and m is the number of edges.
      * \param airport source airport
      * \param n_flights number of flights
      *
      * \return set of airport codes reachable from one airport with n_flights
      */
    unordered_set<string> BfsNflights(const string& airport, int n_flights);

    /**
      * The time complexity of this function is O(1)
      * \param airport - source airport
      * \return number of neighbors for a given airport
      */
    int n_flights(const string& airport);
    /**
      * The time complexity of this function is O(n), where n is the number of neighbors of the input node
      * \param airport - source airport
      * \return number of different airlines that can be used with one flight
      */
    int diff_airline(const string& airport);

    /**
      * The time complexity of this function is O(1)
      * \param airport - source airport
      * \return number of different destinations from one airport
      */
    int n_diff_dest(const string& airport);

    /**
      * The time complexity of this function is O(n), where n is the number of neighbors of the input node
      * \param airport - source airport
      * \return vector of different destinations from one airport
      */
    vector<string> diff_dest(const string& airport);
};

#endif
