#include "StrBlob.h"
#include <iostream>
#include <utility>

struct StrBlobPtrPtr {
    StrBlobPtr data;

    explicit StrBlobPtrPtr(StrBlobPtr ptr) : data(std::move(ptr)) {}

    StrBlob::reference operator*() const { return data.operator*(); }

    StrBlobPtr &operator->() { return data; }

    const StrBlobPtr &operator->() const { return data; }
};

int main() {
    StrBlob a1 = {"hi", "bye", "now"};
    StrBlobPtr ptr(a1);
    StrBlobPtrPtr p(ptr);
    *p = "okay";
    std::cout << *ptr << ' ' << *p << '\n';
    std::cout << ptr->size() << '\n';
    std::cout << (*ptr).size() << '\n';
    std::cout << p->size() << '\n';
    std::cout << (*p).size() << '\n';
    *ptr = "no";
    std::cout << *ptr << ' ' << *p << '\n';
    std::cout << ptr->size() << '\n';
    std::cout << (*ptr).size() << '\n';
    std::cout << p->size() << '\n';
    std::cout << (*p).size() << '\n';

    return 0;
}
