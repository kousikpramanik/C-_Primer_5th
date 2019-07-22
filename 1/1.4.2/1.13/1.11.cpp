#include <iostream>

int main()
{
        int val1, val2;

        std::cout << "Enter two integers: ";
        std::cin >> val1 >> val2;
        std::cout << "Integers from " << val1 << " to " << val2
                        << " inclusive are as follows" << std::endl;
        for (; val2 >= val1; ++val1) {
                std::cout << val1 << std::endl;
        }

        return 0;
}
