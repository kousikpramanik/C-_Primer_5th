#include <cstddef>
#include <vector>
#include <iterator>
#include <iostream>

int main()
{
        constexpr std::size_t arr_size = 5;
        std::vector<int> vect;
        int arr[arr_size];

        for (int i = 0; i != arr_size; ++i)
                vect.push_back(i + 1);

        auto it_vect = vect.cbegin();
        auto it_arr = std::begin(arr);
        while (it_arr != std::end(arr)) {
                *it_arr = *it_vect;

                ++it_arr;
                ++it_vect;
        }

        std::cout << "Here is the vector: ";
        for (auto n : vect)
                std::cout << n << ' ';
        std::cout << std::endl;

        std::cout << "Here is the array: ";
        for (auto n : arr)
                std::cout << n << ' ';
        std::cout << std::endl;

        return 0;
}
