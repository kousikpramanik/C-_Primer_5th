#include <iostream>

void f() {
    std::cout << "Called f() without any arguments.\n";
}

void f(int a) {
    std::cout << "Called f() with one int argument: " << a << ".\n";
}

void f(int a, int b) {
    std::cout << "Called f() with two int arguments: " << a << ", " << b << ".\n";
}

void f(double a, double b = 3.14) {
    std::cout << "Called f() with two double arguments: " << a << ", " << b << ".\n";
    std::cout << "\tThe argument of the second parameter was" << (b == 3.14 ? " " : " not ")
              << "the same as its default argument.";
}

int main() {
    // f(2.56, 42); error: ambiguous, candidates are void f(int, int) and void f(double, double)
    f(42);
    f(42, 0);
    f(2.56, 3.14);

    return 0;
}
