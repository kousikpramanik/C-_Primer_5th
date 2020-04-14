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

StrVec &StrVec::operator=(StrVec &&other) noexcept {
    if (this != &other) {
        free();
        first_element = other.first_element;
        first_free = other.first_free;
        one_past_capacity = other.one_past_capacity;
        other.first_element = other.first_free = other.one_past_capacity = nullptr;
    }
    return *this;
}

// non-member functions
bool operator==(const StrVec &lhs, const StrVec &rhs) {
    if (lhs.size() == rhs.size()) {
        for (auto l = lhs.cbegin(), r = rhs.cbegin(), lend = lhs.cend(); l != lend; ++l, ++r) {
            if (*l != *r) { return false; }
        }
        return true;
    } else {
        return false;
    }
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
