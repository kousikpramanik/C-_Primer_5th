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
            __alloc = alloc_new;
            __first_element = ptr;
            __first_free = __one_past_capacity = _copy_only(str.begin(), str.end(), __first_element);
        } else {
            auto data = _alloc_and_copy(str.begin(), str.end());
            _free();
            __first_element = data.first;
            __first_free = __one_past_capacity = data.second;
        }
    }
    return *this;
}

String &String::operator=(String &&str) {
    if (this != &str) {
        if (!std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value &&
            __alloc != str.__alloc) {
            return *this = str; // copy-assignment
        } else {
            _free();
            if (std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value) {
                __alloc = std::move(str.__alloc);
            }
            __first_element = str.__first_element;
            __first_free = str.__first_free;
            __one_past_capacity = str.__one_past_capacity;
            str.__first_element = nullptr;
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
        for (size_type i = 0; i != count; ++i) { *__first_free++ = ch; }
        *__first_free = '\0';
    }
    return *this;
}

// internal usage
void String::_reallocate(size_type request) {
    if (!request) { request = size() ? 2 * size() : 1; }
    if (request > max_size()) {
        throw std::length_error("String reallocation: requested size is greater than max_size()");
    }
    auto newbegin = std::allocator_traits<allocator_type>::allocate(__alloc, request + __account_for_null);
    auto newend = newbegin;
    auto old = __first_element;
    for (size_type i = 0, upto = request < size() ? request : size(); i != upto; ++i) { *newend++ = *old++; }
    *newend = '\0';
    _free();
    __first_element = newbegin;
    __first_free = newend;
    __one_past_capacity = __first_element + request;
}
