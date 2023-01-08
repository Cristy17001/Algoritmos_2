#ifndef TRABALHO_ALGORITMOS_2_AIRLINES_H
#define TRABALHO_ALGORITMOS_2_AIRLINES_H

#include <string>
#include <utility>

using namespace std;



/**
 * \class Airlines
 * \brief Stores information about airline.
 *
 * This class was designed to store every information about an airline including
 * \param code - the identification code of the airline
 * \param name - full name of the airline
 * \param callsign - airline identifier
 * \param country - country in which the airline is headquartered or was founded
 *
 * \note This class was designed to be used by the manager class.
 * \see Manager
 */
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
