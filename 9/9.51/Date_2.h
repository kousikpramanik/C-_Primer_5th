#ifndef C_PRIMER_5TH_DATE_2_H
#define C_PRIMER_5TH_DATE_2_H

#include <iostream>
#include <string>

class Date {
    friend std::istream &read(std::istream &is, Date &dt);

    friend std::ostream &print(std::ostream &os, const Date &dt);

public: // constructors
    Date() = default;

    Date(unsigned a, unsigned b, unsigned c, unsigned style = 0);

    // using string where date is required is fine, don't make explicit
    Date(std::string str); // create copy because we will modify this

    explicit Date(std::istream &is) { read(is, *this); }

public: // member functions
    // year % 400 if century, year % 4 if not
    bool leap_year() { return !(yyyy % (yyyy % 100 ? 4 : 400)); }

private: // member functions
    bool valid();

private: // data members
    unsigned yyyy = 0;
    unsigned mm = 1;
    unsigned dd = 1;
};

inline std::istream &read(std::istream &is, Date &dt) {
    std::string input;
    std::getline(is, input);
    dt = input; // let Date(std::string str) handle this
    return is;
}

inline std::ostream &print(std::ostream &os, const Date &dt) { return os << dt.yyyy << '/' << dt.mm << '/' << dt.dd; }

#endif // C_PRIMER_5TH_DATE_2_H
