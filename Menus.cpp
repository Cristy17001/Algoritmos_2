#include "Menus.h"

void flightOptionsMenuOrigin(Manager& m,bool combination) {
    string choice;
    _setmode(_fileno(stdout), _O_WTEXT);
    wcout << '\n'
            << L"╔═════════════════════════════════════════════════════════════════════════════╗\n"
            << L"║                           Flight Options Menu                               ║\n"
            << L"╠═════════════════════════════════════════════════════════════════════════════╣\n"
            << L"║ Specify the type of location you of your origin:                            ║\n"
            << L"║ 1. Airport                                                                  ║\n"
            << L"║ 2. City and Country                                                         ║\n"
            << L"║ 3. Latitude and Longitude                                                   ║\n"
            << L"║ B. Back                                                                     ║\n"
            << L"╚═════════════════════════════════════════════════════════════════════════════╝\n"
            << L"⇒ ";
    _setmode(_fileno(stdout), _O_TEXT);
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
    // Special characters possible to use with Wide text
    _setmode(_fileno(stdout), _O_WTEXT);
    wcout << '\n'
            << L"╔═════════════════════════════════════════════════════════════════════════════╗\n"
            << L"║                           Flight Options Menu                               ║\n"
            << L"╠═════════════════════════════════════════════════════════════════════════════╣\n"
            << L"║ Specify the type of location you of your destination:                       ║\n"
            << L"║ 1. Airport                                                                  ║\n"
            << L"║ 2. City and Country                                                         ║\n"
            << L"║ B. Back                                                                     ║\n"
            << L"╚═════════════════════════════════════════════════════════════════════════════╝\n"
            << L"⇒ ";
    _setmode(_fileno(stdout), _O_TEXT);

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
    auto airportmap = m.get_airport();
    auto country_city_map = m.get_cities_to_airports();


    // Origin inputs
    if (origin == "Airports") {
        do{
        cout << '\n';
        cout << "Origin Airport: ";
        cin >> o_airport;
        for (char& c : o_airport) {
            c = toupper(c);
        }
        if(airportmap.find(o_airport) == airportmap.end()){
            cout <<endl<<"Enter a valid airport"<<endl;
        }
        }
        while (airportmap.find(o_airport) == airportmap.end());

    }
    else if (origin == "Cities") {
        bool found = false;
        do {
            cout << '\n';
            cout << "Origin Country: ";
            cin >> o_country;
            o_country[0] = toupper(o_country[0]);
            for (int i = 1; i < o_country.size(); i++) {
                o_country[i] = tolower(o_country[i]);
            }
            cout << endl << "Origin City: ";
            cin >> o_city;

            o_city[0] = toupper(o_city[0]);
            for (int i = 1; i < o_city.size(); i++) {
                o_city[i] = tolower(o_city[i]);
            }

            pair<string, string> city_pair = {o_country, o_city};
            auto it = country_city_map.find(city_pair);
            if (it != country_city_map.end()) {
                found = true;
            }else{
                cout <<endl<< "Country/city not found" << endl;
                found = false;
            }
        }
        while(!found);
    }

    else if (origin == "Coordinates") {
        cout << '\n';
        cout << "Origin latitude: ";
        cin >> latitude;
        cout << endl << "Origin longitude: ";
        cin >> longitude;
        cout << endl << "Distance from Origin: ";
        cin >> distance;
    }

    // Destination inputs
    if (dest == "Airports") {
        do{
        cout << '\n';
        cout << "Destination Airport: ";
        cin >> d_airport;
        for (char& c : d_airport) {
            c = toupper(c);
        }
        if(airportmap.find(d_airport) == airportmap.end()){
            cout <<endl<<"Enter a valid airport"<<endl;
        }

        }
        while(airportmap.find(d_airport) == airportmap.end());
    }
    else if (dest == "Cities") {
        bool found = false;
        do{
        cout << '\n';
        cout << "Destination Country: ";
        cin >> d_country;
        d_country[0] = toupper(d_country[0]);
        for (int i = 1; i < d_country.size(); i++) {
            d_country[i] = tolower(d_country[i]);
        }
        cout << endl << "Destination City: ";
        cin >> d_city;
        d_city[0] = toupper(d_city[0]);
        for (int i = 1; i < d_city.size(); i++) {
            d_city[i] = tolower(d_city[i]);
        }
        pair<string, string> city_pair = {d_country, d_city};
        auto it = country_city_map.find(city_pair);
        if (it != country_city_map.end()) {
            found = true;
        }
        else{
            cout <<endl<< "Country/city not found" << endl;
            found = false;
        }
        }
        while(!found);
    }
    vector<string> airlines = airlinesOptionsMenu(m);
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
    if (res.empty())  {
        cout << endl << "Couldn't find any path with those airlines!" << endl;
    }
    else tablePrint(res);
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

vector<string> airlinesOptionsMenu(Manager& m) {
    vector<string> airlines;
    auto airlinemap = m.get_airlines();
    string choice;
    cout << endl << "Do you want to specify the airlines (y/n): ";
    cin >> choice;
    if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
    choice = (char)toupper(choice[0]);
    cout << endl;

    string airline;

    switch (choice[0]) {
        case 'N': {
            return {"any"};
        }
        case 'Y': {
            do {
                cout << "Introduce the airline: ";
                cin >> airline;
                for (char &c: airline) {
                    c = (char)toupper(c);
                }
                if (airlinemap.find(airline) == airlinemap.end()) {
                    cout <<endl<< "Error: airline not found" << endl<<endl;
                } else {
                    airlines.push_back(airline);
                    cout << endl << "Do you want to continue(y/n): ";
                    cin >> choice;

                    if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
                    choice = (char)toupper(choice[0]);
                    if (choice[0] != 'Y') {
                        cout<<endl;
                        cout << "Invalid Character! ('No' was considered)" << endl;
                        return airlines;
                    }
                    cout << endl;
                }
            } while (choice[0] != 'N');
            return airlines;
        }
        default:{
            cout << "Invalid Character! ('No' was considered)"<<endl<<endl ;
            return {"any"};
        }

    }
}

void airportInfoMenu(Manager& m) {
    string choice;
    // Special characters possible to use with Wide text
    _setmode(_fileno(stdout), _O_WTEXT);
    wcout << '\n'
            << L"╔═════════════════════════════════════════════════════════════════════════════╗\n"
            << L"║                          Airport Information Menu                           ║\n"
            << L"╠═════════════════════════════════════════════════════════════════════════════╣\n"
            << L"║ Please choose an option:                                                    ║\n"
            << L"║ 1. General information's about an airport                                   ║\n"
            << L"║ 2. How many locations are reachable using a maximum of Y flights            ║\n"
            << L"║ B. Back                                                                     ║\n"
            << L"╚═════════════════════════════════════════════════════════════════════════════╝\n"
            << L"⇒ ";
    _setmode(_fileno(stdout), _O_TEXT);

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
    for (char& c : code) {
        c = toupper(c);
    }
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
        cout << "\nFrom airport " << code << " it is possible to reach " << n_diff_countrys << " different countries!"
             << endl;
    } else {
        cout << "\nERROR: There is no such airport!" << endl;
    }
}
void y_flights(Manager& m) {
    string code, y;
    int num = 0;
    cout << "\nIntroduce the airport code: " << endl;
    cout << "#> ";
    cin >> code;
    for (char& c : code) {
        c = toupper(c);
    }

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
        cout << endl;
    }
    if (it == airports.end()) {
        cout << "\nERROR: There is no such airport!" << endl;
    }
    if (!verify_int) {
        cout << "\nERROR: Please introduce a valid integer value!" << endl;
    }
}

wstring centerString(const wstring& s, int width) {
    int padding = max(0, (width - (int)s.length()) / 2);
    wstring result = s;
    result = wstring(padding, ' ') + s + wstring(padding+(width-(2*padding+(int)s.length())), ' ');
    return result;
}

void tablePrint(const vector<vector<string>>& paths) {
    _setmode(_fileno(stdout), _O_WTEXT);
    size_t n_cols = paths[0].size();
    size_t n_rows = paths.size();

    // First line
    wstring start_line;
    wstring start_pattern = L"╦═════";
    for (int i = 0; i < n_cols-2; i++) {start_line += start_pattern;}
    wcout << L"╔═════" << start_line << L"╦══════════╗" << endl;

    // Header line
    wstring code = L"Code ║";
    wstring airplane = L" AIR ║";
    wstring header = L"║Start║";
    bool alternate = true;
    for (int i = 0; i < n_cols-3; i++) {
        if (alternate) {header += airplane;}
        else {header += code;}
        alternate = !alternate;
    }
    header += L" End ║ Distance ║";
    wcout << header << endl;

    // Mid lines
    wstring mid_line;
    wstring mid_pattern = L"╋━━━━━";
    for (int i = 0; i < n_cols-2; i++) {mid_line += mid_pattern;}
    mid_line = L"┣━━━━━" + mid_line + L"╋━━━━━━━━━━┫";
    wcout << mid_line << endl;

    // Final line
    wstring final_line;
    wstring final_pattern = L"┻━━━━━";
    for (int i = 0; i < n_cols-2; i++) {final_line += final_pattern;}

    for (int i = 0; i < n_rows; i++) {
        wcout << L"┃";
        for (int j = 0; j < n_cols; j++) {
            wstring_convert<codecvt_utf8<wchar_t>> converter;
            wstring wstr = converter.from_bytes(paths[i][j]);
            if (n_cols-1 == j) {
                wstr = centerString(wstr, 8);
            }
            wcout << L" " + wstr + L" ┃";
        }

        wcout << endl;
        if (i != n_rows-1) {
            wcout << mid_line << endl;
        }
    }

    // Final line
    wcout << L"┗━━━━━" << final_line << L"┻━━━━━━━━━━┛" << endl;

    // std::cout working again
    _setmode(_fileno(stdout), _O_TEXT);
}