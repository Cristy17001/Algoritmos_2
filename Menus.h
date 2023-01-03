#ifndef TRABALHO_ALGORITMOS_2_MENUS_H
#define TRABALHO_ALGORITMOS_2_MENUS_H

#include <iostream>
#include <string>
#include "Manager.h"

using namespace std;

void flightOptionsMenuOrigin(Manager& m);
void flightOptionsMenuDestination(Manager& m, string origin_type);
void flightOptionsProcess(Manager& m, vector<string> orig_dest);
Manager::InputType getInputType(const string& inputTypeString);
vector<string> airlinesOptionsMenu(Manager& m);
void airportInfoMenu(Manager& m);
void general_information(Manager& m);
void y_flights(Manager& m);

#endif //TRABALHO_ALGORITMOS_2_MENUS_H
