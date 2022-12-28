#ifndef TRABALHO_ALGORITMOS_2_AIRPORT_H
#define TRABALHO_ALGORITMOS_2_AIRPORT_H

#include <string>
#include <utility>

using namespace std;

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
