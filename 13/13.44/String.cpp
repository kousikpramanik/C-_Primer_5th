#include "String.h"

#include <memory>

// internal usage
void String::reallocate(size_type request) {
    if (!request) { request = 2 * size(); }
    auto newbegin = std::allocator_traits<Allocator>::allocate(allocator, request + account_for_null);
    auto newend = newbegin;
    auto old = first_element;
    for (size_type i = 0, upto = request < size() ? request : size(); i != upto; ++i) {
        std::allocator_traits<Allocator>::construct(allocator, newend++, *old++);
    }
    std::allocator_traits<Allocator>::construct(allocator, newend, '\0');
    free();
    first_element = newbegin;
    first_free = newend;
    one_past_capacity = first_element + request;
}
