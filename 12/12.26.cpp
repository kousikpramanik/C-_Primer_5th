#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>

int main() {
    std::size_t n;
    std::cout << "Enter number of strings: ";
    std::cin >> n;
    {
        std::string discard;
        std::getline(std::cin, discard);
    }
    std::allocator<std::string> str_alloc;
    auto const p = str_alloc.allocate(n);
    auto q = p;
    std::string s;
    while (std::cin >> s && q != p + n) { str_alloc.construct(q++, s); }
    const std::size_t size = q - p;
    q = p;
    for (std::size_t i = 0; i != size; ++i, ++q) {
        std::cout << *q << '\n';
    }
    while (q != p) { str_alloc.destroy(--q); }
    str_alloc.deallocate(p, n);

    return 0;
}
