#include "Menus.h"

void flightOptionsMenuOrigin(Manager& m,bool combination) {
    string choice;
    cout
            << '\n'
            << "###############################################################################\n"
            << "#                           Flight Options Menu                               #\n"
            << "###############################################################################\n"
            << "# Specify the type of location you of your origin:                            #\n"
            << "# 1. Airport                                                                  #\n"
            << "# 2. City and Country                                                         #\n"
            << "# 3. Latitude and Longitude                                                   #\n"
            << "# B. Back                                                                     #\n"
            << "###############################################################################\n"
            << "#> ";

    cin >> choice;
    if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
    choice = (char)toupper(choice[0]);

    switch (choice[0]) {
        case '1': {
            flightOptionsMenuDestination(m, "Airports",combination);
            break;
        }
        case '2': {
            flightOptionsMenuDestination(m, "Cities",combination);
            break;
        }
        case '3': {
            flightOptionsMenuDestination(m, "Coordinates",combination);
            break;
        }
        case 'B': break;
        case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
        default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
    }
}

void flightOptionsMenuDestination(Manager& m, const string& origin_type, bool combination) {
    string choice;
    cout
            << '\n'
            << "###############################################################################\n"
            << "#                           Flight Options Menu                               #\n"
            << "###############################################################################\n"
            << "# Specify the type of location you of your destination:                       #\n"
            << "# 1. Airport                                                                  #\n"
            << "# 2. City and Country                                                         #\n"
            << "# B. Back                                                                     #\n"
            << "###############################################################################\n"
            << "#> ";

    cin >> choice;
    if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
    choice = (char)toupper(choice[0]);


    switch (choice[0]) {
        case '1': {
            vector<string> dest_type;
            dest_type.push_back(origin_type);
            dest_type.emplace_back("Airports");
            flightOptionsProcess(m, dest_type,combination);

            break;
        }
        case '2': {
            vector<string> dest_type;
            dest_type.push_back(origin_type);
            dest_type.emplace_back("Cities");
            flightOptionsProcess(m, dest_type,combination);
            break;
        }
        case 'B': break;
        case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
        default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
    }
}

void flightOptionsProcess(Manager& m, vector<string> orig_dest, bool combination) {
    string origin = orig_dest[0];
    string dest = orig_dest[1];
    string o_airport, o_country, o_city;
    string d_airport, d_country, d_city;
    double latitude, longitude, distance;
    vector<vector<string>> res;

    // Origin inputs
    if (origin == "Airports") {
        cout << '\n'<<'\n';
        cout << "Origin Airport: ";
        cin >> o_airport;
    }
    else if (origin == "Cities") {
        cout << '\n'<<'\n';
        cout << "Origin Country: ";
        cin >> o_country;
        cout << endl << "Origin City: ";
        cin >> o_city;
    }
    else if (origin == "Coordinates") {
        cout << '\n'<<'\n';
        cout << "Origin latitude: ";
        cin >> latitude;
        cout << endl << "Origin longitude: ";
        cin >> longitude;
        cout << endl << "Distance from Origin: ";
        cin >> distance;
    }

    // Destination inputs
    if (dest == "Airports") {
        cout << '\n';
        cout << "Destination Airport: ";
        cin >> d_airport;
    }
    else if (dest == "Cities") {
        cout << '\n';
        cout << "Destination Country: ";
        cin >> d_country;
        cout << endl << "Destination City: ";
        cin >> d_city;
    }
    vector<string> airlines = airlinesOptionsMenu();
    Manager::InputType o_input = getInputType(origin);
    Manager::InputType d_input = getInputType(dest);

    if (origin == "Airports") {
        if (dest == "Airports") {
            res = m.findShortestPathConditions(o_input,d_input,"",o_airport,"",d_airport,0,0,0,airlines,combination);
        }
        else if (dest == "Cities") {
            res = m.findShortestPathConditions(o_input,d_input,"",o_airport,d_country,d_city,0,0,0,airlines,combination);
        }
    }
    else if (origin == "Cities") {
        if (dest == "Airports") {
            res = m.findShortestPathConditions(o_input,d_input,o_country,o_city,"",d_airport,0,0,0,airlines,combination);
        }
        else if (dest == "Cities") {
            res = m.findShortestPathConditions(o_input,d_input,o_country,o_city,d_country,d_city,0,0,0,airlines,combination);
        }
    }
    else if (origin == "Coordinates") {
        if (dest == "Airports") {
            res = m.findShortestPathConditions(o_input,d_input,"","","",d_airport,latitude,longitude,distance,airlines,combination);
        }
        else if (dest == "Cities") {
            res = m.findShortestPathConditions(o_input,d_input,"","",d_country,d_city,latitude,longitude,distance,airlines,combination);
        }
    }

    for (const auto& r : res) {
        cout<<endl;
        for (int i = 0; i<r.size();i++){
            if(i % 2 != 0 && i != r.size()-1 && i !=0 && i != r.size()-2 ) {
                cout << "~[" << r[i] << "]~";
            }
            else if (i == r.size()-1){
                cout<<endl<<"Distance: "<<r[i]<<" Km";
            }
            else{
                cout << r[i];}
        }
        cout << endl;
        cout<<endl;
    }
}

Manager::InputType getInputType(const string& inputTypeString) {
    if (inputTypeString == "Cities") {
        return Manager::InputType::Cities;
    } else if (inputTypeString == "Airports") {
        return Manager::InputType::Airports;
    } else if (inputTypeString == "Coordinates") {
        return Manager::InputType::Coordinates;
    }
    return Manager::Airports;
}

vector<string> airlinesOptionsMenu() {
    vector<string> airlines;

    char choice;
    string airline;
    cout<< endl << "Do you want to specify the airlines (y/n): ";
    cin >> choice;
    if (choice == 'n') {return {"any"};}
    else {
        do {
            cout <<endl<< "Introduce the airline: ";
            cin >> airline;
            airlines.push_back(airline);
            cout <<endl << "Do you want to continue(y/n): ";
            cin >> choice;
        } while (choice != 'n');
    }
    return airlines;
}

void airportInfoMenu(Manager& m) {
    string choice;
    cout
            << '\n'
            << "###############################################################################\n"
            << "#                           Airport Information Menu                          #\n"
            << "###############################################################################\n"
            << "# Please choose an option:                                                    #\n"
            << "# 1. General information's about an airport                                   #\n"
            << "# 2. How many locations are reachable using a maximum of Y flights            #\n"
            << "# B. Back                                                                     #\n"
            << "###############################################################################\n"
            << "#> ";

    cin >> choice;
    if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
    choice = (char)toupper(choice[0]);

    switch (choice[0]) {
        case '1': {
            general_information(m);
            break;
        }
        case '2': {
            y_flights(m);
            break;
        }
        case 'B': break;
        case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
        default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
    }
}

void general_information(Manager& m) {
    string code;
    cout << "\nIntroduce the airport code: " << endl;
    cout << "#> ";
    cin >> code;

    auto flights = m.get_Flights();
    auto airports = m.get_airport();

    auto it = airports.find(code);
    if (it != airports.end()) {
        int n_flights = flights.n_flights(code);
        cout << "\nFrom airport " << code << " there are " << n_flights << " flights!";

        int n_airlines = flights.diff_airline(code);
        cout << "\nIn airport " << code << " there are " << n_airlines << " different airlines!";

        int n_diff = flights.n_diff_dest(code);
        cout << "\nFrom airport " << code << " there are " << n_diff << " possible destinations!";

        int n_diff_countrys = m.diff_countrys(code);
        cout << "\nFrom airport " << code << " it is possible to reach " << n_diff_countrys << " different countries!" << endl;
    }
    else {
        cout << "\nERROR: There is no such airport!" << endl;
    }
}
void y_flights(Manager& m) {
    string code, y;
    int num = 0;
    cout << "\nIntroduce the airport code: " << endl;
    cout << "#> ";
    cin >> code;

    cout << "\nIntroduce the number of flights: " << endl;
    cout << "#> ";
    cin >> y;

    auto flights = m.get_Flights();
    auto airports = m.get_airport();

    auto it = airports.find(code);
    bool verify_int = true;
    try {
        num = stoi(y);
    } catch (const invalid_argument& e) {
        verify_int = false;
    }

    if (it != airports.end() && verify_int) {
        vector<int> res = m.n_flights_bfs(code, num);
        cout << "\nWith " << num << " flights it is possible to reach " << res[0] << " airports!";
        cout << "\nWith " << num << " flights it is possible to reach " << res[1] << " cities!";
        cout << "\nWith " << num << " flights it is possible to reach " << res[2] << " countries!";
    }
    if (it == airports.end()) {
        cout << "\nERROR: There is no such airport!" << endl;
    }
    if (!verify_int) {
        cout << "ERROR: Please introduce a valid integer value!" << endl;
    }
}