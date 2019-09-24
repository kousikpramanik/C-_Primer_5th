// output will be
// 10
// 2

#include <iostream>

int main()
{
        using std::cout;
        using std::endl;

        int x[10];
        int *p = x;
        cout << sizeof(x) / sizeof(*x) << endl;
        cout << sizeof(p) / sizeof(*p) << endl;

        return 0;
}
