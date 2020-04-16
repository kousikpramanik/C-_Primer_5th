#ifndef C_PRIMER_5TH_STRVEC_H
#define C_PRIMER_5TH_STRVEC_H

#include <string>
#include <memory>
#include <initializer_list>
#include <limits>
#include <exception>
#include <utility>

class StrVec {
public: // types that should be part of the template
    using T = std::string;
    using Allocator = std::allocator<T>;
public: // member types
    using value_type = T;
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
public: // member functions
    StrVec() = default;

    StrVec(const StrVec &other);

    StrVec(StrVec &&other) noexcept;

    StrVec(std::initializer_list<T> init);

    ~StrVec() { free(); }

    StrVec &operator=(const StrVec &other);

    StrVec &operator=(StrVec &&other) noexcept;

    StrVec &operator=(std::initializer_list<T> ilist);

public: // element access
    T *data() noexcept { return first_element; }

    const T *data() const noexcept { return first_element; }

public: // iterators
    iterator begin() noexcept { return first_element; }

    const_iterator begin() const noexcept { return first_element; }

    const_iterator cbegin() const noexcept { return first_element; }

    iterator end() noexcept { return first_free; }

    const_iterator end() const noexcept { return first_free; }

    const_iterator cend() const noexcept { return first_free; }

public: // capacity
    size_type size() const noexcept { return first_free - first_element; }

    size_type max_size() const noexcept { return std::numeric_limits<difference_type>::max(); }

    void reserve(size_type new_cap);

    size_type capacity() const noexcept { return one_past_capacity - first_element; }

public: // modifiers
    void push_back(const T &value);

public: // non-member functions
    friend bool operator==(const StrVec &lhs, const StrVec &rhs);

    friend bool operator!=(const StrVec &lhs, const StrVec &rhs);

    friend bool operator<(const StrVec &lhs, const StrVec &rhs);

    friend bool operator<=(const StrVec &lhs, const StrVec &rhs);

    friend bool operator>(const StrVec &lhs, const StrVec &rhs);

    friend bool operator>=(const StrVec &lhs, const StrVec &rhs);

private: // internal usage
    int compare(const StrVec &other) const;

    std::pair<iterator, iterator> alloc_n_copy(const_iterator b, const_iterator e);

    void free();

    void reallocate(size_type request = 0);

    void chk_n_realloc();

private:
    Allocator allocator;
    T *first_element = nullptr;
    T *first_free = nullptr;
    T *one_past_capacity = nullptr;
};

// member functions
inline StrVec::StrVec(const StrVec &other) {
    auto newdata = alloc_n_copy(other.begin(), other.end());
    first_element = newdata.first;
    first_free = one_past_capacity = newdata.second;
}

inline StrVec::StrVec(StrVec &&other) noexcept: first_element(other.first_element),
                                                first_free(other.first_free),
                                                one_past_capacity(other.one_past_capacity) {
    other.first_element = other.first_free = other.one_past_capacity = nullptr;
}

inline StrVec::StrVec(std::initializer_list<T> init) {
    // works because iterators and pointers are same thing at the moment
    auto data = alloc_n_copy(init.begin(), init.end());
    first_element = data.first;
    first_free = one_past_capacity = data.second;
}

// capacity
inline void StrVec::reserve(StrVec::size_type new_cap) {
    if (new_cap > max_size()) {
        throw std::length_error("StrVec::reserve: " + std::to_string(new_cap) +
                                " larger than max_size(" + std::to_string(max_size()) + ")");
    }
    if (new_cap > capacity()) { reallocate(new_cap); }
}

// modifiers
inline void StrVec::push_back(const T &value) {
    chk_n_realloc();
    std::allocator_traits<Allocator>::construct(allocator, first_free++, value);
}

// non-member functions
inline bool operator==(const StrVec &lhs, const StrVec &rhs) { return lhs.compare(rhs); }

inline bool operator!=(const StrVec &lhs, const StrVec &rhs) { return !lhs.compare(rhs); }

inline bool operator<(const StrVec &lhs, const StrVec &rhs) { return lhs.compare(rhs) == -1; }

inline bool operator<=(const StrVec &lhs, const StrVec &rhs) { return lhs.compare(rhs) != 1; }

inline bool operator>(const StrVec &lhs, const StrVec &rhs) { return lhs.compare(rhs) == 1; }

inline bool operator>=(const StrVec &lhs, const StrVec &rhs) { return lhs.compare(rhs) != -1; }

// internal usage
inline std::pair<StrVec::iterator, StrVec::iterator> StrVec::alloc_n_copy(const_iterator b, const_iterator e) {
    auto data = std::allocator_traits<Allocator>::allocate(allocator, e - b);
    return std::make_pair(data, std::uninitialized_copy(b, e, data));
}

inline void StrVec::chk_n_realloc() {
    if (size() == capacity()) { reallocate(); }
}

inline void StrVec::free() {
    if (first_element) {
        for (auto p = first_free; p != first_element;) { std::allocator_traits<Allocator>::destroy(allocator, --p); }
        std::allocator_traits<Allocator>::deallocate(allocator, first_element, one_past_capacity - first_element);
    }
}

#endif //C_PRIMER_5TH_STRVEC_H
