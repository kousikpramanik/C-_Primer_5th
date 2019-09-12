#include <iostream>
#include <cstddef>

int main()
{
        int ia[3][4] = {
                { 0, 1, 2, 3 },
                { 4, 5, 6, 7 },
                { 8, 9, 10, 11 }
        };

        using std::size_t;
        for (size_t i = 0; i != 3; ++i) {
                for (size_t j = 0; j != 4; ++j)
                        std::cout << ia[i][j] << ' ';
                std::cout << std::endl;
        }

        return 0;
}