#include "String.h"

#include <stdexcept>
#include <memory>

// member functions
String &String::operator=(const String &str) {
    if (this != &str) {
        if (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value) {
            auto alloc_new = str.get_allocator();
            auto ptr = _alloc_only(str.begin(), str.end(), alloc_new);
            _free();
            _alloc = alloc_new;
            _first_element = ptr;
            _first_free = _one_past_capacity = _copy_only(str.begin(), str.end(), _first_element);
        } else {
            auto data = _alloc_and_copy(str.begin(), str.end());
            _free();
            _first_element = data.first;
            _first_free = _one_past_capacity = data.second;
        }
    }
    return *this;
}

String &String::operator=(String &&str) {
    if (this != &str) {
        if (!std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value &&
            _alloc != str._alloc) {
            return *this = str; // copy-assignment
        } else {
            _free();
            if (std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value) {
                _alloc = std::move(str._alloc);
            }
            _first_element = str._first_element;
            _first_free = str._first_free;
            _one_past_capacity = str._one_past_capacity;
            str._first_element = nullptr;
        }
    }
    return *this;
}

// operations
String &String::append(size_type count, CharT ch) {
    if (count == 1) {
        push_back(ch);
    } else {
        _check_and_reallocate(count);
        for (size_type i = 0; i != count; ++i) { *_first_free++ = ch; }
        *_first_free = '\0';
    }
    return *this;
}

// internal usage
void String::_reallocate(size_type request) {
    if (!request) { request = size() ? 2 * size() : 1; }
    if (request > max_size()) {
        throw std::length_error("String reallocation: requested size is greater than max_size()");
    }
    auto newbegin = std::allocator_traits<allocator_type>::allocate(_alloc, request + _account_for_null);
    auto newend = newbegin;
    auto old = _first_element;
    for (size_type i = 0, upto = request < size() ? request : size(); i != upto; ++i) { *newend++ = *old++; }
    *newend = '\0';
    _free();
    _first_element = newbegin;
    _first_free = newend;
    _one_past_capacity = _first_element + request;
}
