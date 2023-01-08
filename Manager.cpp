#include "Manager.h"


Manager::Manager() {
    //load the airports from the "airports.csv"
    load_Airports("airports.csv");

    //load the airlines from the "airlines.csv"
    load_Airlines("airlines.csv");

    //load the flights from the "airlines.csv"
    load_Flights("flights.csv");
}


FlightGraph Manager::get_Flights() const {
    return this->flights;
}


unordered_map<string, Airport> Manager::get_airport() const {
    return this->airport;
}

unordered_map<string, Airlines> Manager::get_airlines() const{
    return this->airlines;
}


CityToAirportsMap Manager::get_cities_to_airports() const {
    return cities_to_airports;
}

vector<string> Manager::getAirportsByCity(const string& country, const string& city) const {
    vector<string> e;
    auto cityAirports = this->get_cities_to_airports();
    auto it = cityAirports.find({country,city});
    if (it != cityAirports.end()){
        e = it->second;
    }
    return e;
}

vector<vector<string>> Manager::getMinPathCombinations (const vector<string>& sourceAirports, const vector<string>& targetAirports, vector<string> valid_airlines, bool combination) const {
    auto graph = this->get_Flights();
    auto aux = this->get_airport();
    vector<vector<string>> path_combination;
    for (const auto& sourceAirport : sourceAirports) {
        for (const auto& targetAirport : targetAirports) {
            if (targetAirport != sourceAirport) {
                auto shortest_path = graph.BfsShortestPaths(sourceAirport, targetAirport);
                auto path = FlightGraph::transformer(shortest_path);
                for (auto& paths : path) {

                    // Check if the user has specified that they want to use any airline
                    bool any_airline = (valid_airlines[0] == "any");

                    // Check that all the airlines in the path are in the valid_airlines vector
                    bool valid_path = any_airline;

                    for (int i = 1; i < paths.size()-1; i+=2) {
                        if (!any_airline && find(valid_airlines.begin(), valid_airlines.end(), paths[i]) != valid_airlines.end()) {
                            valid_path = true;
                        }
                        else if (any_airline) {
                            valid_path = true;
                            break;
                        }
                        else {
                            valid_path = false;
                            break;
                        }
                    }
                    if (valid_path) {
                        double distance = 0;
                        for (int i = 0; i < paths.size()-2; i+=2){
                            distance += haversine(
                                    aux.at(paths[i]).getLatitude(),
                                    aux.at(paths[i]).getLongitude(),
                                    aux.at(paths[i+2]).getLatitude(),
                                    aux.at(paths[i+2]).getLongitude());
                        }
                        if (!combination) {
                            int size_zero = 1;
                            int dist_verification;
                            if (!path_combination.empty()) {
                                size_zero = (int)path_combination[0].size();
                                dist_verification = stoi(path_combination[0][size_zero - 1]);
                            }
                            if (path_combination.empty() or dist_verification > distance) {
                                path_combination.clear();
                                paths.push_back(to_string((int) floor(distance)));
                                path_combination.push_back(paths);
                            }
                        }
                        else {
                            paths.push_back(to_string((int) floor(distance)));
                            path_combination.push_back(paths);
                        }
                    }
                }
            }
        }
    }
    return path_combination;
}


vector<vector<string>> Manager::findShortestPathConditions(InputType inputType, InputType destinationType,const string &country, const string &input,const string &countryD, const string &target, double inputLat, double inputLong, double inputDist, const vector<string>& validAirlines, bool combination) const {
    auto graph = this->get_Flights();

    // Handle different input/destination types
    switch (inputType) {
        case Airports: {
            if (destinationType == Airports) {
                vector<string> source;
                vector<string> tAirport;
                source.push_back(input);
                tAirport.push_back(target);
                return {getMinPathCombinations(source,tAirport,validAirlines, combination)};
            } else {
                // Shortest path from airport to city
                auto sourceAirports = {input};
                auto targetAirports = getAirportsByCity(countryD,target);
                return {getMinPathCombinations(sourceAirports,targetAirports,validAirlines, combination)};

            }
        }
        case Cities: {
            if (destinationType == Airports) {
                // Shortest path from city to airport
                auto sourceAirports = getAirportsByCity(country,input);
                auto targetAirports = {target};
                return {getMinPathCombinations(sourceAirports,targetAirports,validAirlines, combination)};
            } else {
                // Shortest path between two cities
                auto sourceAirports = getAirportsByCity(country,input);
                auto targetAirports = getAirportsByCity(countryD, target);
                return {getMinPathCombinations(sourceAirports,targetAirports,validAirlines, combination)};
            }
        }
        case Coordinates: {
            vector<string> originAirports;
            for (const auto& airport_pair : this->get_airport()) {
                const auto& code = airport_pair.first;
                const auto& airp = airport_pair.second;
                if (haversine(airp.getLatitude(), airp.getLongitude(), inputLat, inputLong) < inputDist){
                    originAirports.push_back(code);
                }
            }
            if (destinationType == Airports){
                auto targetAirports = {target};
                return {getMinPathCombinations(originAirports,targetAirports,validAirlines, combination)};
            } else {
                auto targetAirports = getAirportsByCity(countryD, target);
                return {getMinPathCombinations(originAirports, targetAirports, validAirlines, combination)};
            }
        }
    }
    return {{}};
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
    // convert to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // distance between latitudes
    // and longitudes
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    // apply formula
    const double earthRadius = 6371; // radius of the Earth in kilometers
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));
    return earthRadius * c;
}


int Manager::diff_countrys(const string& airp) {
    vector<string> diff_dest = flights.diff_dest(airp);
    unordered_set<string> counter;
    for (const string& str: diff_dest) {
        Airport a = airport[str];
        counter.insert(a.getCountry());
    }
    return (int)counter.size();
}

vector<int> Manager::n_flights_bfs(const string& airp, int n_flights) {
    // elements in this order airports, city's, country's
    vector<int> res;
    unordered_set<string> airports = flights.BfsNflights(airp, n_flights);
    int n_aiports = (int)airports.size();
    res.push_back(n_aiports);
    unordered_set<string> countrys;
    unordered_set<string> citys;

    for (const auto& str: airports) {
        citys.insert(airport[str].getCity());
        countrys.insert(airport[str].getCountry());
    }
    res.push_back((int)citys.size());
    res.push_back((int)countrys.size());

    return res;
}