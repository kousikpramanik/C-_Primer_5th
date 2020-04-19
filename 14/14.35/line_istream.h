#ifndef C_PRIMER_5TH_LINE_ISTREAM_H
#define C_PRIMER_5TH_LINE_ISTREAM_H

#include <iostream>
#include <string>

class line_istream {
public:
    line_istream(std::istream &i = std::cin) : is(i) {}

    std::string operator()();

private:
    std::istream &is;
};

inline std::string line_istream::operator()() {
    std::string ret;
    if (!std::getline(is, ret)) {
        return std::string();
    } else {
        return ret;
    }
}

#endif //C_PRIMER_5TH_LINE_ISTREAM_H
