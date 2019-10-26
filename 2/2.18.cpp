#include <iostream>

int main() {
    int a = 40, b = 50;
    int *p = &a;

    std::cout << *p << std::endl;
    // code to change the value of a pointer
    p = &b;
    std::cout << *p << std::endl;

    // code to change the value to which the pointer points
    *p = 1;
    std::cout << *p << std::endl;

    return 0;
}
