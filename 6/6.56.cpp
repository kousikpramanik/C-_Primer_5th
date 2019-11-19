#include <vector>
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0)
        return a / b;
    else
        return 0;
}

int main(void) {
    std::vector<decltype(add) *> fnvect;
    fnvect.push_back(add);
    fnvect.push_back(subtract);
    fnvect.push_back(multiply);
    fnvect.push_back(divide);

    std::cout << "9 + 5 is: " << fnvect[0](9, 5) << '\n';
    std::cout << "9 - 5 is: " << fnvect[1](9, 5) << '\n';
    std::cout << "9 * 5 is: " << fnvect[2](9, 5) << '\n';
    std::cout << "9 / 5 is: " << fnvect[3](9, 5) << '\n';
}
