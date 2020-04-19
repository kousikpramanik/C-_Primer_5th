#include <iostream>
#include <vector>
#include <algorithm>

class equal {
public:
    equal(int n = 0) : state(n) {}

    bool operator()(int other) { return state == other; }

private:
    int state;
};

int main() {
    std::vector<int> ivec{1, 2, 3, 2, 5, 7, 1, 3, 2, 6, 9, 11, 40};
    for (auto n : ivec) { std::cout << n << ' '; }
    std::cout << '\n';
    std::replace_if(ivec.begin(), ivec.end(), equal(5), 999);
    for (auto n : ivec) { std::cout << n << ' '; }
    std::cout << '\n';

    return 0;
}
