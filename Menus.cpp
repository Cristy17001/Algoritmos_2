#include "Menus.h"

void flightOptionsMenu(Manager& m) {
    string choice;
    cout
            << '\n'
            << "###############################################################################\n"
            << "#                           Flight Options Menu                               #\n"
            << "###############################################################################\n"
            << "# Specify the type of location you want to input:                             #\n"
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
        case '1': break;
        case '2': break;
        case '3': break;
        case 'B': break;
        case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
        default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
    }
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