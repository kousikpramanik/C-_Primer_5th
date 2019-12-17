#include "8.5.h"

#include <vector>
#include <string>
#include <fstream>

std::ifstream &fileToVecWord(std::ifstream &ifs, std::vector<std::string> &ftvw) {
    std::string str;
    while (ifs >> str) { ftvw.push_back(str); }

    return ifs;
}
