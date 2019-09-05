#include <iostream>
#include <iterator>
#include <cstddef>

using std::cout;
using std::endl;

using std::begin;
using std::end;

using std::ptrdiff_t;

int main()
{
        constexpr ptrdiff_t a_size = 40;
        int a[a_size];
        for (auto beg = begin(a); beg != end(a); ++beg)
                *beg = 0;

        for (auto n : a)
                cout << n << ' ';
        cout << endl;

        return 0;
}
