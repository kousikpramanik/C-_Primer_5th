#include <vector>
#include <numeric>
#include <deque>
#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> vec(9);
    std::iota(vec.begin(), vec.end(), 1);

    std::deque<int> que1, que2, que3;
    std::copy(vec.cbegin(), vec.cend(), std::back_inserter(que1));
    std::copy(vec.cbegin(), vec.cend(), std::front_inserter(que2));
    std::copy(vec.cbegin(), vec.cend(), std::inserter(que3, que3.end()));

    // expectation : 1 2 3 4 5 6 7 8 9
    for (auto n : que1) { std::cout << n << ' '; }
    std::cout << '\n';
    // expectation : 9 8 7 6 5 4 3 2 1
    for (auto n : que2) { std::cout << n << ' '; }
    std::cout << '\n';
    // expectation : 1 2 3 4 5 6 7 8 9
    for (auto n : que3) { std::cout << n << ' '; }
    std::cout << '\n';

    return 0;
}
