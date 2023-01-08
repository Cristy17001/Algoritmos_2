#include <iostream>
#include "Manager.h"
#include "Menus.h"

using namespace std;

int main() {
    Manager manager = Manager();
    string choice;

    do {
        _setmode(_fileno(stdout), _O_WTEXT);
        wcout <<'\n'
        << L"╔═════════════════════════════════════════════════════════════════════════════╗\n"
        << L"║                               Flight Manager                                ║\n"
        << L"╠═════════════════════════════════════════════════════════════════════════════╣\n"
        << L"║ Please choose an option:                                                    ║\n"
        << L"║ 1. Find shortest path between two locations                                 ║\n"
        << L"║ 2. Find all the possible paths between two locations                        ║\n"
        << L"║ 3. Get information about an airport                                         ║\n"
        << L"║ Q. Quit                                                                     ║\n"
        << L"╚═════════════════════════════════════════════════════════════════════════════╝\n"
        << L"#> ";

        _setmode(_fileno(stdout), _O_TEXT);

        cin >> choice;
        if (choice.size() > 1) {choice.clear(); choice[0] = '?';}
        choice = (char)toupper(choice[0]);

        switch (choice[0]) {
            case '1': {
                flightOptionsMenuOrigin(manager,false);
                break;}
            case '2': {
                flightOptionsMenuOrigin(manager, true);
                break;}
            case '3': {airportInfoMenu(manager); break;}
            case 'Q': break;
            case '?': {cout << "\nError: Invalid input. Please enter one character.\n\n"; break;}
            default : {cout << "\nError: Invalid input. Please enter a valid choice.\n\n"; break;}
        }

    } while (choice[0] != 'Q');

    return 0;
}