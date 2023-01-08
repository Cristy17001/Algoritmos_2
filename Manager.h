#ifndef TRABALHO_ALGORITMOS_2_MANAGER_H
#define TRABALHO_ALGORITMOS_2_MANAGER_H

#include "FlightGraph.h"
#include "Airport.h"
#include "Airlines.h"
#include <fstream>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <cmath>

// Defining the hash "constructor"
struct PairHash {
    size_t operator()(const pair<string, string>& p) const {
        size_t h1 = std::hash<string>()(p.first);
        size_t h2 = std::hash<string>()(p.second);
        return h1 ^ h2;
    }
};

// Defining an equality verification between pairs
struct PairEqual {
    bool operator()(const pair<string, string>& p1, const pair<string, string>& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

// Specify a type for airports map consisting of a pair Country, City
using CityToAirportsMap = unordered_map<pair<string, string>, vector<string>, PairHash, PairEqual>;

/**
 * @class Manager
 * @brief Stores data about flights, airports and airlines
 *
 * Makes the data accessible everywhere in the program. Makes it possible to access most of data in O(1) complexity.
 * Also responsible for loading of data from .csv files
 *
 * @note This class was designed to store data about flights, airports and airlines.
 * @see FlightGraph, Airport, Airlines
 */
class Manager {
private:

    /**
     * Provides access to the flights graph
     * @see FlightGraph
     */
    FlightGraph flights;

    /**
     * Provides access to every airport in O(1) time complexity
     * @see Airport
     */
    unordered_map<string, Airport> airport;

    /**
     * Provides access to every airline in O(1) time complexity
     * @see Airlines
     */
    unordered_map<string, Airlines> airlines;

    /**
     * Provides access to every airport by the city and country of that airport in O(1) time complexity
     * @see Airport
     */
    CityToAirportsMap cities_to_airports;

public:
    Manager();

    enum InputType {
        Airports,
        Cities,
        Coordinates
    };


    //void set_Flights() const;
    FlightGraph get_Flights() const;

    unordered_map<string, Airport> get_airport() const;

    unordered_map<string, Airlines> get_airlines() const;

    CityToAirportsMap get_cities_to_airports() const;

    vector<string> getAirportsByCity (const string& coutry, const string& city) const;

    vector<vector<string>> getMinPathCombinations (const vector<string>& sourceAirports, const vector<string>& targetAirports, vector<string> valid_airlines, bool combination) const;

    vector<vector<string>> findShortestPathConditions(InputType inputType, InputType destinationType,const string &country, const string &input,const string &countryD, const string &target, double inputLat, double inputLong, double inputDist,const vector<string>& valid_airlines, bool combination) const;

    void load_Flights(const std::string& filename);
    void load_Airports(const std::string& filename);
    void load_Airlines(const std::string& filename);

    static double haversine(double lat1, double lon1, double lat2, double lon2);
    int diff_countrys(const string& airport);
    vector<int> n_flights_bfs(const string& airp, int n_flights);
};

#endif