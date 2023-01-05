#ifndef TRABALHO_ALGORITMOS_2_MANAGER_H
#define TRABALHO_ALGORITMOS_2_MANAGER_H


#include "FlightGraph.h"
#include "Airport.h"
#include "Airlines.h"
#include <fstream>
#include <cmath>
#include <float.h>
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

class Manager {
private:
    // Graph representing the flights
    FlightGraph flights;

    // Airport code defined as key to an Airport
    unordered_map<string, Airport> airport;

    unordered_map<string, Airlines> airlines;

    // Country and City defined as key to vector of airport codes
    CityToAirportsMap cities_to_airports;

public:
    Manager();

    enum InputType {
        Airports,
        Cities,
        Coordinates
    };

    //void set_Flights() const;
    const FlightGraph get_Flights() const;

    const unordered_map<string, Airport> get_airport() const;

    const unordered_map<string, Airlines> get_airlines() const;

    const CityToAirportsMap get_cities_to_airports() const;

    vector<string> getAirportsByCity (const string& coutry, const string& city) const;

    vector<string> getMinDistancePath (const vector<string>& sourceAirports, const vector<string>& targetAirports, vector<string> valid_airlines);

    vector<vector<string>> getMinPathCombinations (const vector<string>& sourceAirports, const vector<string>& targetAirports, vector<string> valid_airlines);

    vector<vector<string>> findShortestPathConditions(InputType inputType, InputType destinationType,const string &country, const string &input,const string &countryD, const string &target, double inputLat, double inputLong, double inputDist,vector<string> valid_airlines, bool combination);

    void load_Flights(const std::string& filename);
    void load_Airports(const std::string& filename);
    void load_Airlines(const std::string& filename);

    double haversine(double lat1, double lon1, double lat2, double lon2);
    int diff_countrys(string airport);
    vector<int> n_flights_bfs(string airp, int n_flights);
};

#endif