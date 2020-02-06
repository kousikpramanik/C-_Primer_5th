#include <iterator>
#include "Sales_item.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    std::istream_iterator<Sales_item> cin_iter(std::cin), eof;
    std::vector<Sales_item> sitem_vec(cin_iter, eof);
    std::sort(sitem_vec.begin(), sitem_vec.end(),
              [](const Sales_item &lhs, const Sales_item &rhs) { return lhs.isbn() < rhs.isbn(); });
    for (auto curr = sitem_vec.cbegin(), curr_end = curr; curr != sitem_vec.cend(); curr = curr_end) {
        curr_end = std::find_if(curr, sitem_vec.cend(),
                                [curr](const Sales_item &s) { return s.isbn() != curr->isbn(); });
        std::cout << std::accumulate(curr, curr_end, Sales_item(curr->isbn())) << '\n';
    }

    return 0;
}
