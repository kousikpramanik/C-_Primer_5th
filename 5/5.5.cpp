#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> scores{"F", "D", "C", "B", "A", "A++"};

    std::cout << "Enter marks: ";
    unsigned grade;
    while (std::cin >> grade && grade <= 100) {
        std::string lettergrade;
        if (grade < 60)
            lettergrade = scores[0];
        else {
            lettergrade = scores[(grade - 50) / 10]; // fetch the letter grade
            if (grade != 100) // add plus or minus only if not already on A++
                if (grade % 10 > 7)
                    lettergrade += '+'; // grades ending in 8 or 9 get a +
                else if (grade % 10 < 3)
                    lettergrade += '-'; // grades ending in 0, 1, or 2 get a -
        }
        std::cout << "Grade is: " << lettergrade << std::endl;
        std::cout << "Enter next marks: ";
    }

    return 0;
}
