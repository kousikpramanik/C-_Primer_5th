#include <iostream>
#include <string>
#include <stdexcept>

void replace_all(std::string &s, const std::string &oldVal, const std::string &newVal) {
    if (oldVal.empty())
        throw std::invalid_argument("string to be replaced is empty.");

    for (decltype(s.size()) pos = 0; (pos = s.find(oldVal, pos)) != std::string::npos; pos += newVal.length()) {
        s.replace(pos, oldVal.length(), newVal);
    }

}

int main() {
    std::string s("Though I cannot write a proper sentence, this tho is not a test tho my redacted tho");
    replace_all(s, "tho", "though");
    std::cout << s << '\n';

    return 0;
}
