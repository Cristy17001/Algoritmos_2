#ifndef TRABALHO_ALGORITMOS_2_AIRLINES_H
#define TRABALHO_ALGORITMOS_2_AIRLINES_H

#include <string>
#include <utility>

using namespace std;

class Airlines {

private:
    string code;
    string name;
    string callsign;
    string country;

public:
    Airlines();
    Airlines(string code, string name, string callsign, string country);

    const string& getCode() const;
    void setCode(const string &code);

    const string& getName() const;
    void setName(const string &name);

    const string& getCallsign() const;
    void setCallsign(const string &callsign);

    const string& getCountry() const;
    void setCountry(const string &country);
};


#endif
