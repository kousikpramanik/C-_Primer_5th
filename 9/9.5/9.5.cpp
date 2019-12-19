#include "9.5.h"

#include <vector>

std::vector<int>::iterator search(std::vector<int>::iterator begin, std::vector<int>::iterator end, int toSearch) {
    while (begin != end) {
        if (*begin == toSearch)
            return begin;
        ++begin;
    }

    return end;
}

std::vector<int>::const_iterator
search(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end, int toSearch) {
    while (begin != end) {
        if (*begin == toSearch)
            return begin;
        ++begin;
    }
    return end;
}
