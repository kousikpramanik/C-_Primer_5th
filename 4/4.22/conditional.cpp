#include <iostream>
#include <string>

int main()
{
        std::cout << "Enter marks: ";
        unsigned grade;
        while (std::cin >> grade && grade <= 100) {
                std::string finalgrade = (grade > 90) ? "high pass" :
                                         (grade > 75) ? "pass" :
                                         (grade >= 60) ? "low pass" :
                                         "fail";
                std::cout << "Your grade is " << finalgrade << std::endl;
                std::cout << "Enter next marks: ";
        }
        std::cout << "Done" << std::endl;

        return 0;
}
