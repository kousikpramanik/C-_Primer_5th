#include <string>
#include <iostream>

int main() {
    const std::string test("ab2c3d7R4E6");
    const std::string alphabet("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
    const std::string digits("1234567890");

    std::cout << "Alphabetic:\n";
    for (decltype(test.size()) i = 0; (i = test.find_first_of(alphabet, i)) != std::string::npos; ++i) {
        std::cout << "test[" << i << "] = " << test[i] << '\n';
    }
    std::cout << '\n';
    std::cout << "Numeric:\n";
    for (decltype(test.size()) i = 0; (i = test.find_first_of(digits, i)) != std::string::npos; ++i) {
        std::cout << "test[" << i << "] = " << test[i] << '\n';
    }
    std::cout << '\n';

    std::cout << "Not numeric:\n";
    for (decltype(test.size()) i = 0; (i = test.find_first_not_of(digits, i)) != std::string::npos; ++i) {
        std::cout << "test[" << i << "] = " << test[i] << '\n';
    }
    std::cout << '\n';
    std::cout << "Not alphabetic:\n";
    for (decltype(test.size()) i = 0; (i = test.find_first_not_of(alphabet, i)) != std::string::npos; ++i) {
        std::cout << "test[" << i << "] = " << test[i] << '\n';
    }
    std::cout << '\n';

    return 0;
}
