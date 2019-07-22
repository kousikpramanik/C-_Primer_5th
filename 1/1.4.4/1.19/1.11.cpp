#include <iostream>

int main()
{
        int val1, val2;

        std::cout << "Enter two integers: ";
        std::cin >> val1 >> val2;

        if (val2 >= val1) {
                std::cout << "Integers from " << val1 << " to " << val2
                                << " inclusive are as follows" << std::endl;
                while (val2 >= val1) {
                        std::cout << val1 << std::endl;
                        ++val1;
                }
        } else {
                std::cout << val1 << " is greater than " << val2 << std::endl;
                std::cout << "Please try again with different values"
                                << std::endl;
        }

        return 0;
}
