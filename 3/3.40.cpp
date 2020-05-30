#include <cstring>
#include <cstdlib>
#include <iostream>

int main() {
    constexpr char st1[] = "I am";
    constexpr char st2[] = "Batman!";
    constexpr std::size_t str_size = sizeof(st1) + sizeof(st2);
    char str[str_size];
    std::strcpy(str, st1);
    std::strcat(str, " ");
    std::strcat(str, st2);
    std::cout << str << std::endl;

    return 0;
}
