#include "8.5.h"

#include <vector>
#include <string>
#include <fstream>

std::ifstream &fileToVecWord(std::ifstream &ifs, std::vector<std::string> &ftv) {
    std::string str;
    while (true) {
        ifs >> str;
        if (!ifs)
            break;
        ftv.push_back(str);
    }

    return ifs;
}
