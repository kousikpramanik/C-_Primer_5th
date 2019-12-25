#include <iostream>
#include <vector>

int main() {
    std::vector<int> test;
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    for (int i = 0; i != 25; ++i) {
        test.push_back(i);
        if (!(i % 5)) { std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n'; }
    }

    test.resize(5);
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    test.resize(100);
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    test.clear();
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    test.reserve(200);
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    test.shrink_to_fit();
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    test.reserve(10);
    for (int i = 0; i != 5; ++i) { test.push_back(0); }
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    test.shrink_to_fit();
    std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

    return 0;
}
