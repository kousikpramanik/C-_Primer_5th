#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>

int main() {
    std::cout << "Enter some integers: ";
    std::istream_iterator<int> cin_iter(std::cin), eof;
    std::list<int> ilst(cin_iter, eof);
    auto found = std::count_if(ilst.cbegin(), std::find(ilst.crbegin(), ilst.crend(), 0).base(),
                               [](int n) { return true; });
    if (found != 0) {
        std::cout << "Last 0 entry found at position: " << found - 1 // reverse_iterator.base() is one position ahead
                  << '\n';
    }

    return 0;
}
