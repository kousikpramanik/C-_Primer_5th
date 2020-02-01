#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> ivec(10); // don't use reserve, we want the elements to actually exist
    std::fill_n(ivec.begin(), ivec.size(), 0);

    for (auto i : ivec) { std::cout << i << '\t'; }
    std::cout << '\n';

    return 0;
}
