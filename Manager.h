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
    * \note This class was designed to store data about flights, airports and airlines.
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

    /**
    * @brief Constructs a Manager object
    *
    * This is the default constructor for the Manager class. It initializes the internal data structures to their default state.
    */
    Manager();

    /**
    * @enum InputType
    * @brief Enumeration for specifying the type of input
    *
    * The InputType enum is used to specify the type of input when calling the findShortestPathConditions() method.
    *
    * @var Airports
    * Indicates that the input is an airport code
    * @var Cities
    * Indicates that the input is a city name
    * @var Coordinates
    * Indicates that the input is a pair of latitude and longitude coordinates
    */
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

    /**
    * @brief Finds the shortest path(s) between two input locations
    *
    * This method finds the shortest path(s) between the specified source and target locations, subject to the given constraints. The source and target locations can be specified as airport codes, city names, or latitude and longitude coordinates.
    *
    * The complexity of this function is O(n), where n is the number of airports in the graph.
    *
    * @param inputType The type of the source location (airport code, city name, or coordinates)
    * @param destinationType The type of the target location (airport code, city name, or coordinates)
    * @param country The country in which the source location is located (if inputType is City or Airport)
    * @param input The source location (airport code, city name, or coordinates)
    * @param countryD The country in which the target location is located (if destinationType is City or Airport)
    * @param target The target location (airport code, city name, or coordinates)
    * @param inputLat The latitude of the source location (if inputType is Coordinates)
    * @param inputLong The longitude of the source location (if inputType is Coordinates)
    * @param inputDist The maximum distance from the source location (if inputType is Coordinates)
    * @param valid_airlines A list of valid airline names
    * @param combination A flag indicating whether to return all combinations or just the shortest path(s)
    * @return A list of combinations of flights between the source and target locations
    */
    vector<vector<string>> findShortestPathConditions(InputType inputType, InputType destinationType,const string &country, const string &input,const string &countryD, const string &target, double inputLat, double inputLong, double inputDist,const vector<string>& valid_airlines, bool combination) const;

    /**
    * @brief Loads flight data from a CSV file
    *
    * This method loads flight data from a CSV file and stores it in the internal FlightGraph object.
    * The file must be in a specific format as described in the project documentation.
    * @see FlightGraph
    * @param filename The path to the CSV file
    */
    void load_Flights(const std::string& filename);

    /**
    * @brief Loads airport data from a CSV file
    *
    * This method loads airport data from a CSV file and stores it in the internal map of Airport objects.
    * @see Airport
    * @param filename The path to the CSV file
    */
    void load_Airports(const std::string& filename);

    /**
    * @brief Loads airline data from a CSV file
    *
    * This method loads airline data from a CSV file and stores it in the internal map of Airlines objects.
    * @see Airlines
    * @param filename The path to the CSV file
    */
    void load_Airlines(const std::string& filename);

    /**
    * @brief Calculates the distance between two pairs of latitude and longitude coordinates
    *
    * This method calculates the distance between two pairs of latitude and longitude coordinates using the Haversine formula.
    *
    * @param lat1 The latitude of the first coordinate
    * @param lon1 The longitude of the first coordinate
    * @param lat2 The latitude of the second coordinate
    * @param lon2 The longitude of the second coordinate
    * @return The distance between the two coordinates in kilometers
    */
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
    * @brief Counts the number of different countries that are reachable from a given airport
    *
    * This method returns the number of different countries that can be reached from the specified airport, within a certain number of flights.
    *
    * @param airp The airport code of the starting airport
    * @return The number of different countries that can be reached from the starting airport
    */
    int diff_countrys(const string& airp);


    /**
    * @brief Counts the number of airports, cities, and countries that are reachable from a given airport
    *
    * This method returns the number of airports, cities, and countries that can be reached from the specified airport, within a certain number of flights. The results are returned in a vector with the following format: [num_airports, num_cities, num_countries]
    *
    * @param airp The airport code of the starting airport
    * @param n_flights The maximum number of flights
    * @return A vector containing the number of airports, cities, and countries that can be reached from the starting airport
    */
    vector<int> n_flights_bfs(const string& airp, int n_flights);

};

#endif