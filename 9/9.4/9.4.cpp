#include "9.4.h"

#include <vector>

bool search(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end, int toSearch) {
    while (begin != end) {
        if (*begin == toSearch)
            return true;
        ++begin;
    }
    return false;
}
