#include <iostream>
#include <list>
#include <deque>
#include <string>
#include <sstream>

int main() {
    std::list<int> lstint;

    std::cout << "Enter a set of integers and press enter.\n";
    std::string input;
    if (!getline(std::cin, input)) {
        std::cerr << "Error with cin.\n";
        return -1;
    }
    std::istringstream inpstrm(input);
    for (int temp; inpstrm >> temp;) { lstint.push_back(temp); }

    std::deque<int> even;
    std::deque<int> odd;
    for (auto n : lstint) {
        if (n % 2)
            even.push_back(n);
        else
            odd.push_back(n);
    }

    std::cout << "Here are the even elements: ";
    for (auto n : even) { std::cout << n << ' '; }
    std::cout << '\n';

    std::cout << "Here are the odd elements: ";
    for (auto n : odd) { std::cout << n << ' '; }
    std::cout << '\n';

    return 0;
}
