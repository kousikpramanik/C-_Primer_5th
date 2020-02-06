#include <list>
#include <string>
#include <iterator>
#include <iostream>
#include "elimDups_list.h"

int main() {
    std::list<std::string> slst((std::istream_iterator<std::string>) std::cin, std::istream_iterator<std::string>());
    elimDups_list(slst);
    return 0;
}
