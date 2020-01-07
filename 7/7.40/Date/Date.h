#ifndef DATE_H_
#define DATE_H_

#include <iostream>

class Date {
    friend std::istream &read(std::istream &is, Date &dt);

public: // constructors
    Date() = default;

    Date(unsigned a, unsigned b, unsigned c, unsigned style = 0) : yyyy(a), mm(b), dd(c) {
        switch (style) {
            case 1:
                dd = a;
                mm = b;
                yyyy = c;
                break;
            case 2:
                mm = a;
                dd = b;
                yyyy = c;
                break;
            case 3:
                dd = a;
                mm = b;
                yyyy = 2000 + c;
                break;
            default:
                // handled by the constructor initialiser list
                break;
        }

        if (!valid(*this)) {
            yyyy = 0;
            mm = 1;
            dd = 1;
        }
    }

    Date(std::istream &is) { read(is, *this); }

    bool valid(const Date &dt);

    bool leap_year(const Date &dt);

private: // data members
    unsigned yyyy = 0;
    unsigned mm = 1;
    unsigned dd = 1;
};

std::istream &read(std::istream &is, Date &dt);

#endif
