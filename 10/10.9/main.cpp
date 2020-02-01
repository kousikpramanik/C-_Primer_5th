#include <iostream>
#include <vector>
#include <string>
#include "elimDups.h"

int main() {
    std::vector<std::string> svec;
    for (std::string s; std::cin >> s;) { svec.push_back(s); }
    elimDups(svec);
    return 0;
}
