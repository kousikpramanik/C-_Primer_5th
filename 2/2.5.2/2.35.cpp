// i is const int
// j is int
// k is const int& associated to i
// p is const int*
// j2 is a const int
// k2 is a const int&

#include <iostream>

int main()
{
        const int i = 42;
        auto j = i;
        const auto &k = i;
        auto *p = &i;
        const auto j2 = i, &k2 = i;

        return 0;
}
