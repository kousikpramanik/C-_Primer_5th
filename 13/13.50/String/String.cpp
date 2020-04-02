#include "String.h"

#include <iostream>
#include <memory>

// member functions
String &String::operator=(String &&other) noexcept {
#ifndef NDEBUG
    std::clog << "In function: String &String::operator=(String &&other) noexcept" << "\n";
#endif // NDEBUG
    if (this != &other) {
        free();
        first_element = other.first_element;
        first_free = other.first_free;
        one_past_capacity = other.one_past_capacity;
        other.first_element = other.first_free = other.one_past_capacity = nullptr;
    }
    return *this;
}

// operations
String &String::append(size_type count, CharT ch) {
    if (count == 1) {
        push_back(ch);
    } else {
        chk_n_realloc(count);
        std::allocator_traits<Allocator>::destroy(allocator, first_free);
        first_free = std::uninitialized_fill_n(first_free, count, ch);
        std::allocator_traits<Allocator>::construct(allocator, first_free, '\0');
    }
    return *this;
}

// internal usage
void String::reallocate(size_type request) {
    if (!request) { request = size() ? 2 * size() : 1; }
    auto newbegin = std::allocator_traits<Allocator>::allocate(allocator, request + account_for_null);
    auto newend = std::uninitialized_copy_n(first_element, request < size() ? request : size(), newbegin);
    std::allocator_traits<Allocator>::construct(allocator, newend, '\0');
    free();
    first_element = newbegin;
    first_free = newend;
    one_past_capacity = first_element + request;
}
