#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

inline std::vector<int> *alloc_vec() { return (new std::vector<int>); }

std::istream &read(std::istream &is, std::vector<int> &ivec) {
    std::istream_iterator<int> is_iter(is), eof;
    while (is_iter != eof) { ivec.push_back(*is_iter++); }

    return is;
}

std::ostream &print(std::ostream &os, const std::vector<int> &ivec) {
    if (!ivec.empty()) {
        auto iter = ivec.cbegin();
        os << *iter;
        std::for_each(++iter, ivec.cend(), [&os](int n) { os << ' ' << n; });
    }

    return os;
}

int main() {
    auto ivec_ptr = alloc_vec();
    read(std::cin, *ivec_ptr);
    print(std::cout, *ivec_ptr) << '\n';
    delete ivec_ptr;

    return 0;
}
