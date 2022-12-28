#include "Manager.h"


Manager::Manager() {
    //load the airports from the "airports.csv"
    load_Airports("airports.csv");

    //load the airlines from the "airlines.csv"
    load_Airlines("airlines.csv");

    //load the flights from the "airlines.csv"
    load_Flights("flights.csv");
}


const FlightGraph Manager::get_Flights() const {
    return FlightGraph();
}


const unordered_map<string, Airport> Manager::get_airport() const {
    return unordered_map<string, Airport>();
}

const unordered_map<string, Airlines> Manager::get_airlines() const{
    return unordered_map<string, Airlines>();
};

/*void Manager::city_to_airports() {

}*/

const CityToAirportsMap Manager::get_cities_to_airports() const {
    return cities_to_airports;
}


void Manager::load_Flights(const std::string& filename) {
    ifstream file;
    string file_text;
    string source, target, airline;
    // filename = "flights.csv"
    file.open(filename);

    //Eliminate first line
    getline(file, file_text);

    while(!file.eof()) {

        getline(file, source, ',');
        getline(file, target, ',');
        getline(file, airline);

        flights.AddNode(source);
        flights.AddNode(target);

        flights.AddEdge(source, target, airline);
    }
    file.close();

}

void Manager::load_Airports(const std::string& filename) {
    ifstream file;
    string file_text;
    string code, name, city, country, latitude, longitude;
    // filename = "airports.csv"
    file.open(filename);

    //Eliminate first line
    getline(file, file_text);

    while(!file.eof()) {

        getline(file, code, ',');
        getline(file, name, ',');
        getline(file, city, ',');
        getline(file, country, ',');
        getline(file, latitude, ',');
        getline(file, longitude);
        double latitude_ = stod(latitude);
        double longitude_ = stod(longitude);

        Airport airport1 = Airport(code, name, city, country, latitude_, longitude_);
        airport[code] = airport1;

        pair<string, string> country_city = {country, city};
        vector<string> vector_codes;
        cities_to_airports[country_city].emplace_back(code);
    }
    file.close();
}

void Manager::load_Airlines(const std::string& filename) {
    ifstream file;
    string file_text;
    string code, name, callsign, country;
    // filename = "airports.csv"
    file.open(filename);

    //Eliminate first line
    getline(file, file_text);

    while(!file.eof()) {

        getline(file, code, ',');
        getline(file, name, ',');
        getline(file, callsign, ',');
        getline(file, country);

        Airlines airlines1 = Airlines(code, name, callsign, country);
        airlines[code] = airlines1;
    }
    file.close();
}
