#include "8.1.h"

#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::cout << "Enter a line: ";

    std::string str;
    if (std::getline(std::cin, str)) {
        std::istringstream strstream(str);
        printIstream(strstream);
        return 0;
    } else
        return -1;
}
