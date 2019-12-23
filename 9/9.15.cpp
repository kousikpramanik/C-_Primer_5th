#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main() {
    std::string input;
    std::istringstream inpstrm;

    std::cout << "Enter a set of integers and press enter.\n";
    if (!std::getline(std::cin, input)) {
        std::cerr << "Error on cin!\n";
        return -1;
    }
    std::vector<int> vec1;
    inpstrm.str(input);
    while (inpstrm) {
        int temp;
        inpstrm >> temp;
        vec1.push_back(temp);
    }

    std::cout << "Enter a second set of integers and press enter.\n";
    if (!std::getline(std::cin, input)) {
        std::cerr << "Error on cin!\n";
        return -1;
    }
    std::vector<int> vec2;
    inpstrm.str(input);
    inpstrm.clear();
    while (inpstrm) {
        int temp;
        inpstrm >> temp;
        vec2.push_back(temp);
    }

    if (vec1 < vec2)
        std::cout << "The first vector is smaller than the second vector.\n";
    else if (vec1 == vec2)
        std::cout << "The two vectors are equal.\n";
    else
        std::cout << "The first vector is greater than the second vector.\n";

    return 0;
}
