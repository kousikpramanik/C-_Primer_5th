#include <iostream>
#include <cstring>

int main()
{
        char st1[] = "I am";
        char st2[] = "Batman!";
        const std::size_t str_size = std::strlen(st1) + std::strlen(st2) + 2;
        char str[str_size];
        std::strcpy(str, st1);
        std::strcat(str, " ");
        std::strcat(str, st2);
        std::cout << str << std::endl;

        return 0;
}
