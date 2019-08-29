#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

using std::size_t;

int main()
{
        constexpr size_t array_size = 10;
        int array[array_size];
        for (size_t i = 0; i < array_size; ++i)
                array[i] = i;

        int arr2[array_size];
        for (size_t i = 0; i < array_size; ++i)
                arr2[i] = array[i];

        cout << "array" << endl;
        for (auto n : array) {
                cout << n << ' ';
        }
        cout << endl;

        cout << "arr2" << endl;
        for (auto n : arr2) {
                cout << n << ' ';
        }

        return 0;
}
