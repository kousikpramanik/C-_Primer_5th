#include <iostream>
#include <vector>

int main() {
    std::vector<int> vectA{0, 1, 1, 2};
    std::vector<int> vectB{0, 1, 1, 2, 3, 5, 8};

    if (vectA.size() > vectB.size()) {
        auto iterA = vectA.cbegin(), iterB = vectB.cbegin();
        while (iterB != vectB.cend()) {
            if (*iterA != *iterB)
                break;
            ++iterA;
            ++iterB;
        }
        std::cout << "vectB is " << (iterB == vectB.cend() ? "" : "not ") << "a prefix of vectA" << std::endl;
    } else if (vectA.size() < vectB.size()) {
        auto iterA = vectA.cbegin(), iterB = vectB.cbegin();
        while (iterA != vectA.cend()) {
            if (*iterA != *iterB)
                break;
            ++iterA;
            ++iterB;
        }
        std::cout << "vectA is " << (iterA == vectA.cend() ? "" : "not ") << "a prefix of vectB" << std::endl;
    } else if (vectA == vectB)
        std::cout << "vectA and vectB are prefixes of each other." << std::endl;

    return 0;
}
