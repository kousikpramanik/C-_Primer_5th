#include "8.4.h"

#include <vector>
#include <string>
#include <fstream>

std::ifstream &fileToVec(std::ifstream &ifs, std::vector<std::string> &ftv) {
    std::string str;
    while (getline(ifs, str)) { ftv.push_back(str); }

    return ifs;
}
