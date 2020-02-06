#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    std::cout << "Enter some integers.\n";
    std::istream_iterator<int> cin_iter(std::cin), eof;
    std::vector<int> ivec(cin_iter, eof);
    std::sort(ivec.begin(), ivec.end());
    std::ostream_iterator<int> cout_iter(std::cout, " ");
    std::unique_copy(ivec.cbegin(), ivec.cend(), cout_iter);
    std::cout << '\n';

    return 0;
}
