#include <iostream>

int main()
{
        int ia[3][4] = {
                { 0, 1, 2, 3 },
                { 4, 5, 6, 7 },
                { 8, 9, 10, 11 }
        };

        using int_array_ptr = const int (*)[4];
        using int_ptr = const int *;
        for (int_array_ptr row = ia; row != ia + 3; ++row) {
                for (int_ptr col = *row; col != *row + 4; ++col)
                        std::cout << *col << ' ';
                std::cout << std::endl;
        }

        return 0;
}
