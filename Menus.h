#ifndef TRABALHO_ALGORITMOS_2_MENUS_H
#define TRABALHO_ALGORITMOS_2_MENUS_H

#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <locale>
#include <codecvt>
#include "Manager.h"


using namespace std;

void flightOptionsMenuOrigin(Manager& m, bool combination);
void flightOptionsMenuDestination(Manager& m, const string& origin_type,bool combination);
void flightOptionsProcess(Manager& m, vector<string> orig_dest,bool combination);
Manager::InputType getInputType(const string& inputTypeString);
vector<string> airlinesOptionsMenu(Manager& m);
/**
 * The time complexity of this function is O(1).
 * \param m - Manager is passed to access data
 * Asks the user what kind of information about an airport he want to have
 * \see general_information, y_flights
 */
void airportInfoMenu(Manager& m);
/**
 * The time complexity of this function is O(1).
 * The function asks for input from the user and display the amount of flights, different airlines, different destinations and
 * different countries that can be reach from a given airport
 * \param m - Manager is passed to access data
 * \see n_flights, diff_airline, n_diff_dest, diff_countrys
 */
void general_information(Manager& m);
/**
 * The time complexity of this function is O(1).
 * \param m - Manager is passed to access data
 * The function asks for input from the user and display the amount of airports, cities and country that is possible to reach
 * with y flights. It call a function that performs this task called n_flights_bfs and display the result.
 * \see n_flights_bfs
 */
void y_flights(Manager& m);
/**
 * The time complexity of this function is O(p*n), where p is the number of paths in the input list and n is the maximum length of the paths
 * Prints the paths in a table format
 * \param paths - paths to print
 */
void tablePrint(const vector<vector<string>>& paths);
/**
 * The time complexity of this function is O(1)
 * Performs the addition of spaces to a wstring in order to center it in a table format
 * \param s - wstring to pad
 * \param width - the size the wstring as to have in the end
 *
 * \return wstring formatted for centering
 */
wstring centerString(const wstring& s, int width);

#endif //TRABALHO_ALGORITMOS_2_MENUS_H
