#include <functional>
#include <cstring>
#include <iostream>

template<typename T>
int compare(const T &v1, const T &v2) {
    if (std::less<T>()(v1, v2)) {
        return -1;
    } else if (std::less<T>()(v2, v1)) {
        return 1;
    } else {
        return 0;
    }
}

template<unsigned long M, unsigned long N>
int compare(const char (&s1)[M], const char (&s2)[N]) {
    return std::strcmp(s1, s2);
}

int main() {
    std::cout << compare("Te", "Bye") << '\n';
    std::cout << compare(3, 5) << '\n';
    std::cout << compare<3, 3>("Hi", "Bi") << '\n';
    std::cout << compare<char[3]>("Hi", "Bi") << '\n';
    std::cout << compare(static_cast<const char *>("Hi"), static_cast<const char *>("Bi")) << '\n';

    return 0;
}
