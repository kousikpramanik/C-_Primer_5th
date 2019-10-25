#include <iostream>

int called() {
    static bool firstOpen = false;
    static int ret = 0;
    if (firstOpen == false) {
        firstOpen = true;
        return 0;
    } else
        return ++ret;
}

int main() {
    char input;
    std::cout << "q to quit, anything else to continue: ";
    while (std::cin >> input && input != 'q') {
        std::cout << called() << std::endl;
        std::cout << "q to quit, anything else to continue: ";
    }

    return 0;
}
