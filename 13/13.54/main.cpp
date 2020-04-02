#include "HasPtr.h"

int main() {
    HasPtr test("Hello");
    HasPtr test2("World!");
    // works fine, HasPtr(HasPtr other) called
    test = test2;
    // compile error. ambiguous since both HasPtr(HasPtr other) and HasPtr(HasPtr &&other) noexcept work with rvalues
    // test = std::move(test2);
    return 0;
}
