#include <iostream>
#include <initializer_list>

int varSum(std::initializer_list<int> lst) {
    int ret = 0;

    for (auto n : lst)
        ret += n;

    return ret;
}

int main() {
    std::cout << "Sum of 2, 3, and 4: " << varSum({2, 3, 4}) << '\n';
    std::cout << "Sum of 5 and 9: " << varSum({5, 9}) << '\n';
    std::cout << "Sum of 1, 7, 3, and 9: " << varSum({1, 7, 3, 9}) << '\n';

    return 0;
}
