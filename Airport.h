#ifndef TRABALHO_ALGORITMOS_2_AIRPORT_H
#define TRABALHO_ALGORITMOS_2_AIRPORT_H

#include <string>
#include <utility>

using namespace std;


/**
 * @class Airport
 * @brief Stores information about an airport.
 *
 * This class was designed to store every information about an airport including
 * @param code - the identification code of the airport
 * @param name - full name of the airport
 * @param city - city in which the airport is located
 * @param country - country in which the airport is located
 * @param latitude - latitude coordinates of the airport
 * @param longitude - longitude coordinates of the airport
 *
 * @note This class was designed to be used by the manager class.
 * @see Manager
 */
class Airport {

private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;

public:
    // Constructor
    Airport();
    Airport(string code, string name, string city, string country, double latitude, double longitude);

    //Getters and Setters
    const string &getCode() const;
    void setCode(const string &code);

    const string &getName() const;
    void setName(const string &name);

    const string &getCity() const;
    void setCity(const string &city);

    const string &getCountry() const;
    void setCountry(const string &country);

    double getLatitude() const;
    void setLatitude(double latitude);

    double getLongitude() const;
    void setLongitude(double longitude);

};


#endif
