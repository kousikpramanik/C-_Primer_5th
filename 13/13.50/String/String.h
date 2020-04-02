#ifndef C_PRIMER_5TH_STRING_H
#define C_PRIMER_5TH_STRING_H

#include <string>
#include <memory>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <cstring>
#include <iostream>
#include <exception>
#include <utility>

class String {
public: // should have been template parameters
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
    String() { clear(); }

    String(const CharT *s);

    String(const String &other);

    String(String &&other) noexcept;

    String(std::initializer_list<CharT> ilist);

    ~String() { free(); };

    String &operator=(const String &other);

    String &operator=(String &&other) noexcept;

public: // element access
    const CharT *data() const noexcept { return first_element; }

    const CharT *c_str() const noexcept { return data(); }

public: // iterators
    iterator begin() noexcept { return first_element; }

    const_iterator begin() const noexcept { return first_element; }

    const_iterator cbegin() const noexcept { return first_element; }

    iterator end() noexcept { return first_free; }

    const_iterator end() const noexcept { return first_free; }

    const_iterator cend() const noexcept { return first_free; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

public: // capacity
    bool empty() const noexcept { return begin() == end(); };

    size_type size() const noexcept { return first_free - first_element; }

    size_type length() const noexcept { return size(); }

    size_type max_size() const noexcept { return std::numeric_limits<difference_type>::max() - account_for_null; }

    void reserve(size_type new_cap = 0);

    size_type capacity() const noexcept { return one_past_capacity - first_element; }

    void shrink_to_fit();

public: // operations
    void clear();

    void push_back(CharT ch);

    void pop_back();

    String &append(size_type count, CharT ch);

    String &append(const String &str);

    String &append(const CharT *s, size_type count);

    String &append(const String::CharT *s) { return append(s, std::strlen(s)); }

    String &operator+=(const String &str) { return append(str); }

    String &operator+=(CharT ch) { return append(1, ch); }

    String &operator+=(const CharT *s) { return append(s); }

private: // internal usage
    std::pair<iterator, iterator> alloc_n_copy(const_iterator b, const_iterator e);

    void reallocate(size_type request = 0);

    void chk_n_realloc(size_type extra = 0);

    void free();

    static constexpr size_type account_for_null = 1;

private:
    Allocator allocator;
    CharT *first_element = nullptr;
    // first_free and one_past_capacity are actually one less than what they should be.
    // the constructors and modifiers manage this by inserting and removing the terminating
    // null character as necessary.
    CharT *first_free = nullptr;
    CharT *one_past_capacity = nullptr;
};

// member functions
inline String::String(const CharT *s) {
    // works because iterators and pointers are same thing at the moment
    auto data = alloc_n_copy(s, s + std::strlen(s));
    first_element = data.first;
    first_free = one_past_capacity = data.second;
}

inline String::String(const String &other) {
#ifndef NDEBUG
    std::clog << "In function: String::String(const String &other)" << "\n";
#endif // NDEBUG
    auto newdata = alloc_n_copy(other.begin(), other.end());
    first_element = newdata.first;
    first_free = one_past_capacity = newdata.second;
}

inline String::String(String &&other) noexcept : first_element(other.first_element),
                                                 first_free(other.first_free),
                                                 one_past_capacity(other.one_past_capacity) {
#ifndef NDEBUG
    std::clog << "In function: String::String(String &&other) noexcept" << "\n";
#endif // NDEBUG
    other.first_element = other.first_free = other.one_past_capacity = nullptr;
}

inline String::String(std::initializer_list<CharT> ilist) {
    // works because iterators and pointers are same thing at the moment
    auto data = alloc_n_copy(ilist.begin(), ilist.end());
    first_element = data.first;
    first_free = one_past_capacity = data.second;
}

inline String &String::operator=(const String &other) {
#ifndef NDEBUG
    std::clog << "In function: String &String::operator=(const String &other)" << "\n";
#endif // NDEBUG
    if (this != &other) {
        auto data = alloc_n_copy(other.begin(), other.end());
        free();
        first_element = data.first;
        first_free = one_past_capacity = data.second;
    }
    return *this;
}

// capacity
inline void String::reserve(size_type new_cap) {
    if (new_cap > max_size()) {
        throw std::length_error("String::reserve: " + std::to_string(new_cap) +
                                " larger than max_size(" + std::to_string(max_size()) + ")");
    }
    if (new_cap < size()) {
        shrink_to_fit();
    } else {
        reallocate(new_cap);
    }
}

inline void String::shrink_to_fit() {
    if (size() < capacity()) { reallocate(size()); }
}

// operations
inline void String::clear() {
    free();
    auto data = alloc_n_copy(nullptr, nullptr);
    first_element = data.first;
    first_free = one_past_capacity = data.second;
}

inline void String::push_back(CharT ch) {
    if (size() == max_size()) { throw std::length_error("String::push_back: size already max"); }
    chk_n_realloc();
    *first_free = ch;
    std::allocator_traits<Allocator>::construct(allocator, ++first_free, '\0');
}

inline void String::pop_back() {
    std::allocator_traits<Allocator>::destroy(allocator, first_free--);
    *first_free = '\0';
}

inline String &String::append(const String &str) {
    chk_n_realloc(str.size());
    std::allocator_traits<Allocator>::destroy(allocator, first_free);
    first_free = std::uninitialized_copy(str.cbegin(), str.cend(), first_free);
    std::allocator_traits<Allocator>::construct(allocator, first_free, '\0');
    return *this;
}

inline String &String::append(const CharT *s, size_type count) {
    chk_n_realloc(count);
    std::allocator_traits<Allocator>::destroy(allocator, first_free);
    first_free = std::uninitialized_copy(s, s + count, first_free);
    std::allocator_traits<Allocator>::construct(allocator, first_free, '\0');
    return *this;
}

// internal usage
inline std::pair<String::iterator, String::iterator> String::alloc_n_copy(const_iterator b, const_iterator e) {
    auto first = std::allocator_traits<Allocator>::allocate(allocator, e - b + account_for_null);
    auto last = std::uninitialized_copy(b, e, first);
    std::allocator_traits<Allocator>::construct(allocator, last, '\0');
    return std::make_pair(first, last);
}

inline void String::chk_n_realloc(size_type extra) {
    if (size() + extra >= capacity()) { reallocate(extra ? size() + extra : 0); }
}

inline void String::free() {
    if (first_element) {
        std::allocator_traits<Allocator>::destroy(allocator, first_free);
        for (auto p = first_free; p != first_element;) { std::allocator_traits<Allocator>::destroy(allocator, --p); }
        std::allocator_traits<Allocator>::deallocate(allocator, first_element,
                                                     one_past_capacity - first_element + account_for_null);
    }
}

#endif //C_PRIMER_5TH_STRING_H
