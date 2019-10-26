#include <iostream>
#include <string>

int main() {
    std::cout << "Enter marks: ";
    unsigned grade;
    while (std::cin >> grade && grade <= 100) {
        std::string finalgrade;
        if (grade > 90)
            finalgrade = "high pass";
        else if (grade > 75)
            finalgrade = "pass";
        else if (grade >= 60)
            finalgrade = "low pass";
        else
            finalgrade = "fail";
        std::cout << "Your grade is " << finalgrade << std::endl;
        std::cout << "Enter next marks: ";
    }
    std::cout << "Done" << std::endl;

    return 0;
}
