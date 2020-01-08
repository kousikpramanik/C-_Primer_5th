#include "Date_2.h"

#include <string>
#include <exception>
#include <cctype>
#include <array>

static inline void erase_delim(std::string &str) {
    auto delim = str.at(0);
    if (delim == ' ' || delim == '/') { str.erase(0, 1); }
    else if (delim == ',') { str.erase(0, 2); }
    else { throw std::invalid_argument("Invalid delimiter."); }
}

Date::Date(unsigned a, unsigned b, unsigned c, unsigned style) : yyyy(a), mm(b), dd(c) {
    switch (style) {
        case 1: // dd/mm/yyyy
            dd = a;
            mm = b;
            yyyy = c;
            break;
        case 2: // mm/dd/yyyy
            dd = b;
            mm = a;
            yyyy = c;
            break;
        case 3: // dd/mm/yy
            dd = a;
            mm = b;
            yyyy = 2000 + c;
            break;
        default: // yyyy/mm/dd
            // handled by the constructor initialiser list
            break;
    }

    if (!valid()) { throw std::invalid_argument("Invalid input."); }
}

// allowed formats -
// 1) <month name><delim><day><delim><year>
// 2) <month name><delim><year><delim><day> only when year > 31, otherwise assumes (1)
// 3) <day><delim><month name><delim><year>
// 4) <year><delim><month name><delim><day> only when year > 31, otherwise assumes (3)
// 5) <day><delim><month><delim><year>
// 6) <year><delim><month><delim><day> only when year > 31, otherwise assumes (5)
// delim must be one of " ", ", ", "/"
Date::Date(std::string str) {
    for (auto &c : str) { c = std::tolower(c); }
    static const std::array<std::string, 12> monName{"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep",
                                                     "oct", "nov", "dec"};
    static const std::string alphabet{"qwertyuiopasdfghjklzxcvbnm"};
    static const std::string digits{"1234567890"};

    decltype(str.size()) processed;
    if (str.find_first_of(alphabet) == str.npos) { // numeric input
        dd = std::stoul(str, &processed);
        str.erase(0, processed);
        erase_delim(str);

        mm = std::stoul(str, &processed);
        str.erase(0, processed);
        erase_delim(str);
    } else { // alphabetic input.
        mm = 13; // invalid input if month name was not found in the loop
        bool mfirst = false;
        for (decltype(monName.size()) i = 0; i != 12; ++i) {
            decltype(str.size()) pos = str.find(monName[i], 0);
            if (pos != str.npos) {
                if (pos == 0) { mfirst = true; }
                mm = i + 1;
                break;
            }
        }
        if (mm == 13) { throw std::invalid_argument("Invalid month name."); }

        if (mfirst) {
            str.erase(0, str.find_first_not_of(alphabet));
            erase_delim(str);

            dd = std::stoul(str, &processed);
            str.erase(0, processed);
            erase_delim(str);
        } else {
            dd = std::stoul(str, &processed);
            str.erase(0, processed);
            erase_delim(str);

            str.erase(0, str.find_first_not_of(alphabet));
            erase_delim(str);
        }
    }

    yyyy = std::stoul(str, &processed);
    if (dd > 31) {
        auto temp = dd;
        dd = yyyy;
        yyyy = temp;
    }

    if (!valid()) { throw std::invalid_argument("Invalid input."); }
}

bool Date::valid() {
    static constexpr std::array<int, 12> dInM{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mm == 0 || mm > 12) { return false; }
    if (leap_year() && mm == 2 && dd != 0 && dd <= 29) { return true; }

    return (dd != 0 && dd <= dInM[mm - 1]);
}
