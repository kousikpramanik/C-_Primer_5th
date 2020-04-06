#ifndef C_PRIMER_5TH_STRING_H
#define C_PRIMER_5TH_STRING_H

#include <string>
#include <memory>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <cstring>
#include <utility>

class String {
public: // should have been template parameters
    // CharT is never a class type, no need to use std::allocator_traits<Allocator>::construct() or destruct()
    using CharT = char;
    using Traits = std::char_traits<CharT>;
    using Allocator = std::allocator<CharT>;
public: // member types
    using traits_type = Traits;
    using value_type = CharT;
    using allocator_type = Allocator;
    using size_type = std::allocator_traits<Allocator>::size_type;
    using difference_type = std::allocator_traits<Allocator>::difference_type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = std::allocator_traits<Allocator>::pointer;
    using const_pointer = std::allocator_traits<Allocator>::const_pointer;
    // no clue how to inherit the library iterators yet
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public: // member functions
    String() : String(Allocator()) {}

    explicit String(const Allocator &alloc) : __alloc(alloc) { clear(); }

    String(const CharT *s, const Allocator &alloc = Allocator());

    String(const String &other);

    String(String &&other) noexcept;

    String(std::initializer_list<CharT> ilist, const Allocator &alloc = Allocator());

    ~String() { _free(); };

    String &operator=(const String &other);

    String &operator=(String &&other);

    allocator_type get_allocator() const { return __alloc; };

public: // element access
    const CharT *data() const noexcept { return __first_element; }

    const CharT *c_str() const noexcept { return data(); }

public: // iterators
    iterator begin() noexcept { return __first_element; }

    const_iterator begin() const noexcept { return __first_element; }

    const_iterator cbegin() const noexcept { return __first_element; }

    iterator end() noexcept { return __first_free; }

    const_iterator end() const noexcept { return __first_free; }

    const_iterator cend() const noexcept { return __first_free; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

public: // capacity
    bool empty() const noexcept { return begin() == end(); };

    size_type size() const noexcept { return __first_free - __first_element; }

    size_type length() const noexcept { return size(); }

    size_type max_size() const noexcept { return std::numeric_limits<difference_type>::max() - __account_for_null; }

    void reserve(size_type new_cap = 0);

    size_type capacity() const noexcept { return __one_past_capacity - __first_element; }

    void shrink_to_fit();

public: // operations
    void clear();

    void push_back(CharT ch);

    void pop_back() { *--__first_free = '\0'; }

    String &append(size_type count, CharT ch);

    String &append(const String &str);

    String &append(const CharT *s, size_type count);

    String &append(const String::CharT *s) { return append(s, std::strlen(s)); }

    String &operator+=(const String &str) { return append(str); }

    String &operator+=(CharT ch) { return append(1, ch); }

    String &operator+=(const CharT *s) { return append(s); }

public: // input/output
    friend std::ostream &operator<<(std::ostream &os, const String &str);

private: // internal usage
    static pointer _alloc_only(const_iterator b, const_iterator e, allocator_type &alloc);

    static iterator _copy_only(const_iterator b, const_iterator e, pointer first);

    std::pair<iterator, iterator> _alloc_and_copy(const_iterator b, const_iterator e);

    void _reallocate(size_type request = 0);

    void _check_and_reallocate(size_type extra = 0);

    void _free();

    static constexpr size_type __account_for_null = 1;

private:
    Allocator __alloc; // = Allocator();
    CharT *__first_element = nullptr;
    // first_free and one_past_capacity are actually one less than what they should be.
    // the constructors and modifiers manage this by inserting and removing the terminating
    // null character as necessary.
    CharT *__first_free = nullptr;
    CharT *__one_past_capacity = nullptr;
};

// member functions
inline String::String(const CharT *s, const Allocator &alloc) : __alloc(alloc) {
    // works because iterators and pointers are same thing at the moment
    auto data = _alloc_and_copy(s, s + std::strlen(s));
    __first_element = data.first;
    __first_free = __one_past_capacity = data.second;
}

inline String::String(const String &other) :
        __alloc(std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.__alloc)) {
    auto newdata = _alloc_and_copy(other.begin(), other.end());
    __first_element = newdata.first;
    __first_free = __one_past_capacity = newdata.second;
}

inline String::String(String &&other) noexcept : __alloc(std::move(other.__alloc)),
                                                 __first_element(other.__first_element),
                                                 __first_free(other.__first_free),
                                                 __one_past_capacity(other.__one_past_capacity) {
    other.__first_element = nullptr;
}

inline String::String(std::initializer_list<CharT> ilist, const Allocator &alloc) : __alloc(alloc) {
    // works because iterators and pointers are same thing at the moment
    auto data = _alloc_and_copy(ilist.begin(), ilist.end());
    __first_element = data.first;
    __first_free = __one_past_capacity = data.second;
}

// capacity
inline void String::reserve(size_type new_cap) {
    if (new_cap < size()) {
        shrink_to_fit();
    } else {
        _reallocate(new_cap);
    }
}

inline void String::shrink_to_fit() {
    if (size() < capacity()) { _reallocate(size()); }
}

// operations
inline void String::clear() {
    _free();
    auto data = _alloc_and_copy(nullptr, nullptr);
    __first_element = data.first;
    __first_free = __one_past_capacity = data.second;
}

inline void String::push_back(CharT ch) {
    _check_and_reallocate();
    *__first_free++ = ch;
    *__first_free = '\0';
}

inline String &String::append(const String &str) {
    _check_and_reallocate(str.size());
    for (auto c : str) { *__first_free++ = c; }
    *__first_free = '\0';
    return *this;
}

inline String &String::append(const CharT *s, size_type count) {
    _check_and_reallocate(count);
    for (size_type i = 0; i != count; ++i) { *__first_free++ = s[i]; }
    *__first_free = '\0';
    return *this;
}

// input/output
inline std::ostream &operator<<(std::ostream &os, const String &str) { return os << str.__first_element; }

// internal usage
inline String::pointer String::_alloc_only(const_iterator b, const_iterator e, allocator_type &alloc) {
    return std::allocator_traits<allocator_type>::allocate(alloc, e - b + __account_for_null);
}

inline String::iterator String::_copy_only(const_iterator b, const_iterator e, pointer first) {
    for (; b != e; ++b) { *first++ = *b; }
    *first = '\0';
    return first;
}

inline std::pair<String::iterator, String::iterator> String::_alloc_and_copy(const_iterator b, const_iterator e) {
    auto first = _alloc_only(b, e, __alloc);
    return std::make_pair(first, _copy_only(b, e, first));
}

inline void String::_check_and_reallocate(size_type extra) {
    if (size() + extra >= capacity()) { _reallocate(extra ? size() + extra : 0); }
}

inline void String::_free() {
    if (__first_element) {
        std::allocator_traits<allocator_type>::deallocate(__alloc, __first_element, capacity() + __account_for_null);
    }
}

#endif //C_PRIMER_5TH_STRING_H
