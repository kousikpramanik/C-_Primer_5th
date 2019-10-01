#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> scores{"F", "D", "C", "B", "A", "A++"};

    std::cout << "Enter marks: ";
    unsigned grade;
    while (std::cin >> grade && grade <= 100) {
        std::string lettergrade;
        grade < 60 ? (lettergrade = scores[0]) : (lettergrade = scores[(grade - 50) / 10]);
        grade != 100 && grade >= 60 ? grade % 10 > 7 ? (lettergrade += '+')
                                                     : grade % 10 < 3 ? (lettergrade += '-')
                                                                      : lettergrade
                                    : lettergrade;
        std::cout << "Grade is: " << lettergrade << std::endl;
        std::cout << "Enter next marks: ";
    }

    return 0;
}
