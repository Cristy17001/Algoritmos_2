#include <iostream>
#include <algorithm>
#include "Manager.h"

using namespace std;

int main() {
    Manager manager = Manager();
    string choice;

    // Testes
    cout << "Teste 1:" << endl;
    auto graph = manager.get_Flights();
    string source = "OPO";
    string target = "GDN";
    auto shortest_paths = graph.BfsShortestPaths(source, target);
    for (const auto& path: shortest_paths) {
        for (auto e: path) {
            cout << e->code << " ";
        }
        cout << endl;
    }

    do {
        cout
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
            case '1': break;
            case '2': break;
            case 'Q': break;
            case '?': {cout << endl << "Error: Invalid input. Please enter one character." << endl << endl; break;}
            default : {cout << endl << "Error: Invalid input. Please enter a valid choice." << endl << endl; break;}
        }

    } while (choice[0] != 'Q');

    return 0;
}