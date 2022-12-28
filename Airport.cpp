#include "Airport.h"

Airport::Airport() {
    code = ""; name = ""; city = ""; country = ""; latitude = 0; longitude = 0;
}
Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

const string& Airport::getCode() const {return this->code;}
void Airport::setCode(const string &code) {this->code = code;}

const string& Airport::getName() const {return name;}
void Airport::setName(const string &name) {this->name = name;}

const string& Airport::getCity() const {return city;}
void Airport::setCity(const string &city) {this->city = city;}

const string& Airport::getCountry() const {return country;}
void Airport::setCountry(const string &country) {this->country = country;}

double Airport::getLatitude() const {return latitude;}
void Airport::setLatitude(double latitude) {this->latitude = latitude;}

double Airport::getLongitude() const {return longitude;}
void Airport::setLongitude(double longitude) {this->longitude = longitude;}

