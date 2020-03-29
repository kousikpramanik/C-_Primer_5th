#include "StrVec.h"

#include <memory>
#include <utility>

// member functions
StrVec &StrVec::operator=(const StrVec &other) {
    if (this != &other) {
        auto data = alloc_n_copy(other.begin(), other.end());
        free();
        first_element = data.first;
        first_free = one_past_capacity = data.second;
    }
    return *this;
}

// internal usage
void StrVec::reallocate(size_type request) {
    if (!request) { request = size() ? 2 * size() : 1; }
    auto newbegin = std::allocator_traits<Allocator>::allocate(allocator, request);
    auto newend = newbegin;
    auto old = first_element;
    for (size_type i = 0; i != size(); ++i) {
        std::allocator_traits<Allocator>::construct(allocator, newend++, std::move(*old++));
    }
    free();
    first_element = newbegin;
    first_free = newend;
    one_past_capacity = first_element + request;
}
