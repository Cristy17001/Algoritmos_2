#include <iostream>
#include "Manager.h"

using namespace std;

void airportInfoMenu(){
    string choice;
    cout
            << '\n'
            << "###############################################################################\n"
            << "#                           Airport Information Menu                          #\n"
            << "###############################################################################\n"
            << "# Please choose an option:                                                    #\n"
            << "# 1. Number of departures                                                     #\n"
            << "# 2. How many different companies did the airport serve as a source for       #\n"
            << "# 3. How many different destinations                                          #\n"
            << "# 4. How many different countries                                             #\n"
            << "# 5. How many locations are reachable using a maximum of Y flights            #\n"
            << "# Q. Back                                                                     #\n"
            << "###############################################################################\n"
            << "#> ";

    cin >> choice;
    if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
    choice = (char)toupper(choice[0]);

    switch (choice[0]) {
        case '1': break;
        case '2': break;
        case '3': break;
        case '4': break;
        case '5': break;
        case 'Q': break;
        case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
        default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
    }
}

void flightOptionsMenu(){
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
        << "# Q. Back                                                                     #\n"
        << "###############################################################################\n"
        << "#> ";

    cin >> choice;
    if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
    choice = (char)toupper(choice[0]);

    switch (choice[0]) {
        case '1': break;
        case '2': break;
        case '3': break;
        case 'Q': break;
        case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
        default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
    }
}

int main() {
    Manager manager = Manager();
    string choice;

    do {
        cout
        <<'\n'
        << "###############################################################################\n"
        << "#                              Flight Manager                                 #\n"
        << "###############################################################################\n"
        << "# Please choose an option:                                                    #\n"
        << "# 1. Find shortest path between two locations                                 #\n"
        << "# 2. Get information about an airport                                         #\n"
        << "# Q. Quit                                                                     #\n"
        << "###############################################################################\n"
        << "#> ";
        cin >> choice;
        if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
        choice = (char)toupper(choice[0]);

        switch (choice[0]) {
            case '1':
                flightOptionsMenu();
                break;

            case '2':
                airportInfoMenu();
                break;

            case 'Q': break;
            case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
            default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
        }

    } while (choice[0] != 'Q');

    return 0;
}