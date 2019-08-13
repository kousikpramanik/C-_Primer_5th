#include <iostream>

int main()
{
        int i = 0, &r = i;
        auto a = r;
        const int ci = i, &cr = ci;
        auto b = ci;
        auto c = cr;
        auto d = &i;
        auto e = &ci;
        const auto f = ci;
        auto &g = ci;

        std::cout << "a = 42;" << std::endl;
        a = 42;
        std::cout << "a is " << a << std::endl;

        std::cout << "b = 42;" << std::endl;
        b = 42;
        std::cout << "b is " << b << std::endl;

        std::cout << "c = 42;" << std::endl;
        c = 42;
        std::cout << "c is " << c << std::endl;

        std::cout << "d = 42; tries to assign an int to a pointer" << std::endl;
        std::cout << "*d is " << *d << std::endl;

        std::cout << "e = 42; tries to assign an int to a pointer" << std::endl;
        std::cout << "*e is " << *e << std::endl;

        std::cout << "f = 42; tries to assign to a const int" << std::endl;
        std::cout << "f is " << f << std::endl;

        std::cout << "g = 42; tries to assign to a const int&" << std::endl;
        std::cout << "g is " << g << std::endl;

        return 0;
}
