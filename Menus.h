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
void airportInfoMenu(Manager& m);
void general_information(Manager& m);
void y_flights(Manager& m);
void tablePrint(const vector<vector<string>>& paths);
wstring centerString(const wstring& s, int width);

#endif //TRABALHO_ALGORITMOS_2_MENUS_H
