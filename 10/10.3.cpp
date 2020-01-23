#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "Sum of ivec is: " << std::accumulate(ivec.cbegin(), ivec.cend(), 0) << '\n';

    return 0;
}
