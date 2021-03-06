#include <vector>
#include <algorithm>
#include <iostream>

class Foo {
public:
    Foo sorted() &&;

    Foo sorted() const &;

public:
    std::vector<int> data;
};

Foo Foo::sorted() &&{
#ifndef NDEBUG
    std::clog << "In file: " << __FILE__ << "\nIn function: Foo::" << __func__ << "() &&\n";
#endif //NDEBUG
    std::sort(data.begin(), data.end());
    return *this;
}

Foo Foo::sorted() const &{
#ifndef NDEBUG
    std::clog << "In file: " << __FILE__ << "\nIn function: Foo::" << __func__ << "() const &\n";
#endif //NDEBUG
    Foo ret(*this);
    // causes infinite loop
    return ret.sorted();
}

int main() {
    Foo bar;
    bar.data.push_back(3);
    bar.data.push_back(5);
    bar.data.push_back(0);
    bar.data.push_back(2);
    bar.data.push_back(1);
    bar.data.push_back(-7);
    bar.data.push_back(-7);
    Foo bar2 = bar.sorted();

    return 0;
}
