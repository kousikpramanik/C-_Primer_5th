#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <sstream>

int compare(const std::list<int> &lst, const std::vector<int> &vec) {
    auto lcurr = lst.cbegin();
    auto lend = lst.cend();
    auto vcurr = vec.cbegin();
    auto vend = vec.cend();

    for (;; ++vcurr, ++lcurr) {
        // test sizes of the containers, because the value was equal upto the last element tested
        if (lcurr == lend) {
            if (vcurr == vend)
                return 0;
            else
                return -1;
        }
        if (vcurr == vend)
            return 1;

        // test values
        if (*lcurr < *vcurr)
            return -1;
        else if (*lcurr == *vcurr)
            continue; // executes iteration_expression
        else
            return 1;
    }
}

int main() {
    std::string input;
    std::istringstream inpstrm;

    std::cout << "Enter a set of integers and press enter.\n";
    if (!std::getline(std::cin, input)) {
        std::cerr << "Error on cin!\n";
        return -1;
    }
    std::list<int> lst;
    inpstrm.str(input);
    while (inpstrm) {
        int temp;
        inpstrm >> temp;
        lst.push_back(temp);
    }

    std::cout << "Enter a second set of integers and press enter.\n";
    if (!std::getline(std::cin, input)) {
        std::cerr << "Error on cin!\n";
        return -1;
    }
    std::vector<int> vec;
    inpstrm.str(input);
    inpstrm.clear();
    while (inpstrm) {
        int temp;
        inpstrm >> temp;
        vec.push_back(temp);
    }

    int result = compare(lst, vec);
    if (result == -1)
        std::cout << "The list is smaller than the vector.\n";
    else if (result == 0)
        std::cout << "The list and the vector are equal.\n";
    else
        std::cout << "The list is greater than the vector.\n";

    return 0;
}

