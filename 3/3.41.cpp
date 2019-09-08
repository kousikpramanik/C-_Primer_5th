#include <iostream>
#include <vector>
#include <iterator>

int main()
{
        int arr[5] = {1, 2, 3, 4, 5};

        std::cout << "Here is the array: ";
        for (auto n : arr)
                std::cout << n << ' ';
        std::cout << std::endl;

        std::cout << "Here is the vector: ";
        std::vector<int> vect(std::begin(arr), std::end(arr));
        for (auto n : vect)
                std::cout << n << ' ';
        std::cout << std::endl;

        return 0;
}
