#include "Airlines.h"
#include <utility>

Airlines::Airlines() {
    code=""; name = ""; callsign = ""; country = "";
}

Airlines::Airlines(string code, string name, string callsign, string country) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->callsign = std::move(callsign);
    this->country = std::move(country);
}

const string &Airlines::getCode() const {return this->code;}
void Airlines::setCode(const string& code) {this->code = code;}

const string &Airlines::getName() const {return this->name;}
void Airlines::setName(const string& name) {this->name = name;}

const string &Airlines::getCallsign() const {return this->callsign;}
void Airlines::setCallsign(const string& callsign) {this->callsign = callsign;}

const string &Airlines::getCountry() const {return this->country;}
void Airlines::setCountry(const string& country) {this->country = country;}
