#include <vector>
#include "HasPtr.h"
#include <string>
#include <algorithm>

int main() {
    std::vector<HasPtr> hpvect;
    for (auto i = 10; i-- != 0;) { hpvect.emplace_back(std::to_string(i)); }
    std::sort(hpvect.begin(), hpvect.end());

    return 0;
}
