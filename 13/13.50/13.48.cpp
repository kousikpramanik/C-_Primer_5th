#include <vector>
#include "String.h"

int main() {
    std::vector<String> svec;
    svec.push_back("Test");
    svec.push_back("Another test");
    svec.push_back("Test 3");
    svec.push_back("Let's try something different.");
    String str{'D', 'i', 'f', 'f', 'e', 'r', 'e', 'n', 't'};
    svec.push_back(std::move(str));
    str = "A new beginning";
    svec.push_back(str);
    svec.push_back(std::move(str));

    return 0;
}
