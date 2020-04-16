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

StrVec &StrVec::operator=(std::initializer_list<T> ilist) {
    auto data = alloc_n_copy(ilist.begin(), ilist.end());
    free();
    first_element = data.first;
    first_free = one_past_capacity = data.second;
    return *this;
}

// internal usage
int StrVec::compare(const StrVec &other) const {
    if (this->size() <= other.size()) {
        for (size_type curr = 0, last = this->size(); curr != last; ++curr) {
            if (this->data()[curr] < other.data()[curr]) {
                return -1;
            } else if (this->data()[curr] > other.data()[curr]) {
                return 1;
            }
        }
        if (this->size() < other.size()) {
            return -1;
        } else {
            return 0;
        }
    } else {
        for (size_type curr = 0, last = other.size(); curr != last; ++curr) {
            if (this->data()[curr] < other.data()[curr]) {
                return -1;
            } else if (this->data()[curr] > other.data()[curr]) {
                return 1;
            }
        }
        return 1;
    }
}

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
