#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::cout << "Enter some integers: ";
    std::istream_iterator<int> cin_iterator(std::cin), eof;
    std::vector<int> ivec(cin_iterator, eof);
    std::cout << "Your integers in reverse order: ";
    for (auto curr = ivec.cend(), first = ivec.cbegin(); curr != first;) { std::cout << *--curr << ' '; }
    std::cout << '\n';

    return 0;
}
