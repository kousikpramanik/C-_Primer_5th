#include "8.10.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "8.4.h"

std::ifstream &fileToVecWord(std::ifstream &ifs, std::vector<std::string> &ftvw) {
    std::vector<std::string> lnVec;
    fileToVec(ifs, lnVec);

    for (const auto &s : lnVec) {
        std::istringstream vecifs(s);
        std::string word;
        while (vecifs >> word) { ftvw.push_back(word); }
    }

    return ifs;
}
