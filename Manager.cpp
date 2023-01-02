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
    return this->flights;
}


const unordered_map<string, Airport> Manager::get_airport() const {
    return this->airport;
}

const unordered_map<string, Airlines> Manager::get_airlines() const{
    return this->airlines;
};


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

double Manager::haversine(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 *= lat1 * M_PI / 180.0;
    lat2 *= lat2 * M_PI / 180.0;

    // apply formula
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

int Manager::diff_countrys(string airp) {
    vector<string> diff_dest = flights.diff_dest(airp);
    unordered_set<string> counter;
    for (string str: diff_dest) {
        Airport a = airport[str];
        counter.insert(a.getCountry());
    }
    return counter.size();
}

vector<int> Manager::n_flights_bfs(string airp, int n_flights) {
    // elements in this order airports, city's, country's
    vector<int> res;
    unordered_set<string> airports = flights.BfsNflights(airp, n_flights);
    int n_aiports = airports.size();
    res.push_back(n_aiports);
    unordered_set<string> countrys;
    unordered_set<string> citys;

    for (auto str: airports) {
        citys.insert(airport[str].getCity());
        countrys.insert(airport[str].getCountry());
    }
    res.push_back(citys.size());
    res.push_back(countrys.size());

    return res;
}