#include <iostream>
#include "Sales_item.h"

int main()
{
        Sales_item book;

        if (std::cin >> book) {
                Sales_item temp;
                while (std::cin >> temp)
                        book += temp;
        }

        std::cout << book << std::endl;

        return 0;
}
