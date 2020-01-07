#include <iostream>
#include <string>
#include <stdexcept>

void replace_all(std::string &s, const std::string &oldVal, const std::string &newVal) {
    if (oldVal.empty())
        throw std::invalid_argument("string to be replaced is empty.");

    for (auto iterSfirst = s.begin(); iterSfirst != s.end(); ++iterSfirst) {
        auto iterSlast = iterSfirst; // we will be replacing the range [iterSfirst, iterSlast)

        auto iterOldBegin = oldVal.cbegin();
        auto iterOldEnd = oldVal.cend();
        for (; iterOldBegin != iterOldEnd; ++iterSlast, ++iterOldBegin) {
            // if s has no more elements and we are in the loop
            // body, oldVal has more elements that cannot be matched
            if (iterSlast == s.end() || *iterOldBegin != *iterSlast)
                break;
        }

        if (iterOldBegin == iterOldEnd) { // oldVal found in s
            iterSfirst = s.erase(iterSfirst, iterSlast);
            iterSfirst = s.insert(iterSfirst, newVal.cbegin(), newVal.cend()) + newVal.length() - 1;
        }
    }
}

int main() {
    std::string s("Though I cannot write a proper sentence, this tho is not a test tho my redacted tho");
    replace_all(s, "tho", "though");
    std::cout << s << '\n';

    return 0;
}
