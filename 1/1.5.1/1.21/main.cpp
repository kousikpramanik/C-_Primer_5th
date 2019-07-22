#include <iostream>
#include "Sales_item.h"

int main()
{
        Sales_item book, temp;

        std::cin >> book;
        std::cin >> temp;

        book += temp;
        std::cout << book << std::endl;

        return 0;
}
