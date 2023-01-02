#include <iostream>
#include <algorithm>
#include "Manager.h"
#include "Menus.h"

using namespace std;

int main() {
    Manager manager = Manager();
    string choice;
    // Testes

    /*auto shortest_paths = graph.BfsShortestPaths(source, target);
    auto res = graph.transformer(shortest_paths);
    for (auto r : res) {
        int count = 0;
        for (auto s : r){
            count++;
            if(count%2==0) {
                cout << "~" << s << "~ ";
            }
            else{
                cout << s << " ";}
        }
        cout << endl;
    }*/

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
            case '1': {
                cout << "Teste 1:" << endl;
                auto graph = manager.get_Flights();
                string source = "YVM";
                string target = "MPN";
                auto random = manager.findShortestPathConditions(Manager::InputType::Airports,Manager::InputType::Airports,"France","YVM","Italy","MPN",41.248055,-8.681389,300 );
                for (auto r : random) {
                    int count = 0;
                    for (auto s : r){
                        count++;
                        if(count%2==0) {
                            cout << "~" << s << "~ ";
                        }
                        else{
                            cout << s << " ";}
                    }
                    cout << endl;
                    cout<<endl;
                }
                flightOptionsMenu(manager);
                break;}
            case '2': {airportInfoMenu(manager); break;}
            case 'Q': break;
            case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
            default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
        }

    } while (choice[0] != 'Q');

    return 0;
}