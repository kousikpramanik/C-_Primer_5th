#ifndef C_PRIMER_5TH_STRBLOB_H
#define C_PRIMER_5TH_STRBLOB_H

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>
#include <utility>
#include <stdexcept>

class StrBlobPtr;

class ConstStrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;

    friend class ConstStrBlobPtr;

public: // data types
    using value_type = std::vector<std::string>::value_type;
    using size_type = std::vector<std::string>::size_type;
    using difference_type = std::vector<std::string>::difference_type;
    using reference = std::vector<std::string>::reference;
    using const_reference = std::vector<std::string>::const_reference;
    using pointer = std::vector<std::string>::pointer;
    using const_pointer = std::vector<std::string>::const_pointer;
    using iterator = StrBlobPtr;
    using const_iterator = ConstStrBlobPtr;

public: // constructors
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

    StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

public: // functions - related to size
    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

public: // functions - add and remove data
    void push_back(const std::string &s) { data->push_back(s); }

    void push_back(std::string &&s) { data->push_back(std::move(s)); }

    void pop_back();

public: // functions - data access
    reference front();

    const_reference front() const;

    reference back();

    const_reference back() const;

    reference operator[](size_type pos) { return (*data)[pos]; }

    const_reference operator[](size_type pos) const { return (*data)[pos]; }

public: // functions - data access through iterators
    iterator begin() noexcept;

    const_iterator begin() const noexcept;

    const_iterator cbegin() const noexcept;

    iterator end() noexcept;

    const_iterator end() const noexcept;

    const_iterator cend() const noexcept;

public: // non-members - order
    friend bool operator==(const StrBlob &lhs, const StrBlob &rhs);

    friend bool operator!=(const StrBlob &lhs, const StrBlob &rhs);

    friend bool operator<(const StrBlob &lhs, const StrBlob &rhs);

    friend bool operator<=(const StrBlob &lhs, const StrBlob &rhs);

    friend bool operator>(const StrBlob &lhs, const StrBlob &rhs);

    friend bool operator>=(const StrBlob &lhs, const StrBlob &rhs);

private: // internal data members
    std::shared_ptr<std::vector<std::string>> data;
};

// non-members - order
inline bool operator==(const StrBlob &lhs, const StrBlob &rhs) { return *(lhs.data) == *(rhs.data); }

inline bool operator!=(const StrBlob &lhs, const StrBlob &rhs) { return *(lhs.data) != *(rhs.data); }

inline bool operator<(const StrBlob &lhs, const StrBlob &rhs) { return *(lhs.data) < *(rhs.data); }

inline bool operator<=(const StrBlob &lhs, const StrBlob &rhs) { return *(lhs.data) <= *(rhs.data); }

inline bool operator>(const StrBlob &lhs, const StrBlob &rhs) { return *(lhs.data) > *(rhs.data); }

inline bool operator>=(const StrBlob &lhs, const StrBlob &rhs) { return *(lhs.data) >= *(rhs.data); }

class StrBlobPtr {
public: // constructors
    StrBlobPtr() : curr_position(0) {}

    explicit StrBlobPtr(StrBlob &a, StrBlob::size_type sz = 0) : wptr(a.data), curr_position(sz) {}

public: // InputIterator + OutputIterator
    StrBlob::reference operator*() const;

    StrBlob::pointer operator->() const { return &**this; }

    StrBlobPtr &operator++();

    friend bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

    friend bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

public: // ForwardIterator
    StrBlobPtr operator++(int);

public: // BidirectionalIterator
    StrBlobPtr &operator--();

    StrBlobPtr operator--(int);

public: // RandomAccessIterator
    StrBlobPtr &operator+=(StrBlob::difference_type n);

    friend StrBlobPtr operator+(const StrBlobPtr &lhs, StrBlob::difference_type n);

    friend StrBlobPtr operator+(StrBlob::difference_type n, const StrBlobPtr &rhs);

    StrBlobPtr &operator-=(StrBlob::difference_type n);

    friend StrBlob::difference_type operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

    friend bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

    friend bool operator<=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

    friend bool operator>(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

    friend bool operator>=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

private: // internal function - test if weak_ptr points to valid data
    std::shared_ptr<std::vector<std::string>> check(StrBlob::size_type i, const std::string &msg) const;

private: // internal data members
    std::weak_ptr<std::vector<std::string>> wptr;
    StrBlob::size_type curr_position;
};

// InputIterator + OutputIterator
inline StrBlob::reference StrBlobPtr::operator*() const {
    auto p = check(curr_position, "invalid dereference attempt");
    return (*p)[curr_position];
}

inline StrBlobPtr &StrBlobPtr::operator++() {
    ++curr_position;
    return *this;
}

inline bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position == rhs.curr_position);
}

inline bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !(lhs == rhs); }

// ForwardIterator
inline StrBlobPtr StrBlobPtr::operator++(int) {
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

// BidirectionalIterator
inline StrBlobPtr &StrBlobPtr::operator--() {
    --curr_position;
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator--(int) {
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

// RandomAccessIterator
inline StrBlobPtr &StrBlobPtr::operator+=(StrBlob::difference_type n) {
    curr_position += n;
    return *this;
}

inline StrBlobPtr operator+(const StrBlobPtr &lhs, StrBlob::difference_type n) {
    StrBlobPtr temp = lhs;
    temp += n;
    return temp;
}

inline StrBlobPtr operator+(StrBlob::difference_type n, const StrBlobPtr &rhs) { return rhs + n; }

inline StrBlobPtr &StrBlobPtr::operator-=(StrBlob::difference_type n) { return *this += -n; }

inline StrBlobPtr operator-(const StrBlobPtr &lhs, StrBlob::difference_type n) {
    StrBlobPtr temp = lhs;
    temp -= n;
    return temp;
}

inline StrBlob::difference_type operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    if (!lhs.wptr.lock() != !rhs.wptr.lock()) {
        throw std::runtime_error("comparing iterators to different StrBlob objects");
    }
    if (lhs.curr_position >= rhs.curr_position) {
        return lhs.curr_position - rhs.curr_position;
    } else {
        return -(static_cast<StrBlob::difference_type>(rhs.curr_position - lhs.curr_position));
    }
}

inline bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position < rhs.curr_position);
}

inline bool operator<=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position <= rhs.curr_position);
}

inline bool operator>(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position > rhs.curr_position);
}

inline bool operator>=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position >= rhs.curr_position);
}

// internal function - test if weak_ptr points to valid data
inline std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(StrBlob::size_type i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) { throw std::runtime_error("unbound StrBlobPtr"); }
    if (i >= ret->size()) { throw std::out_of_range(msg); }
    return ret;
}

// functions - add and remove data
inline void StrBlob::pop_back() {
    *iterator(*this);
    data->pop_back();
}

// functions - data access
inline StrBlob::reference StrBlob::front() { return *iterator(*this); }

inline StrBlob::reference StrBlob::back() { return *iterator(*this, this->size() - 1); }

// functions - data access through iterators
inline StrBlob::iterator StrBlob::begin() noexcept { return iterator(*this); }

inline StrBlob::iterator StrBlob::end() noexcept { return iterator(*this, data->size()); }

class ConstStrBlobPtr {
public: // constructors
    ConstStrBlobPtr() : curr_position(0) {}

    explicit ConstStrBlobPtr(const StrBlob &a, StrBlob::size_type sz = 0) : wptr(a.data), curr_position(sz) {}

public: // InputIterator
    StrBlob::const_reference operator*() const;

    StrBlob::const_pointer operator->() const { return &**this; }

    ConstStrBlobPtr &operator++();

    friend bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

    friend bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

public: // ForwardIterator
    ConstStrBlobPtr operator++(int);

public: // BidirectionalIterator
    ConstStrBlobPtr &operator--();

    ConstStrBlobPtr operator--(int);

public: // RandomAccessIterator
    ConstStrBlobPtr &operator+=(StrBlob::difference_type n);

    friend ConstStrBlobPtr operator+(const ConstStrBlobPtr &lhs, StrBlob::difference_type n);

    friend ConstStrBlobPtr operator+(StrBlob::difference_type n, const ConstStrBlobPtr &rhs);

    ConstStrBlobPtr &operator-=(StrBlob::difference_type n);

    friend StrBlob::difference_type operator-(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

    friend bool operator<(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

    friend bool operator<=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

    friend bool operator>(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

    friend bool operator>=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

private: // internal function - test if weak_ptr points to valid data
    std::shared_ptr<const std::vector<std::string>> check(StrBlob::size_type i, const std::string &msg) const;

private: // internal data members
    std::weak_ptr<const std::vector<std::string>> wptr;
    StrBlob::size_type curr_position;
};

// InputIterator
inline StrBlob::const_reference ConstStrBlobPtr::operator*() const {
    auto p = check(curr_position, "invalid dereference attempt");
    return (*p)[curr_position];
}

inline ConstStrBlobPtr &ConstStrBlobPtr::operator++() {
    ++curr_position;
    return *this;
}

inline bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position == rhs.curr_position);
}

inline bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) { return !(lhs == rhs); }

// ForwardIterator
inline ConstStrBlobPtr ConstStrBlobPtr::operator++(int) {
    ConstStrBlobPtr ret = *this;
    ++*this;
    return ret;
}

// BidirectionalIterator
inline ConstStrBlobPtr &ConstStrBlobPtr::operator--() {
    --curr_position;
    return *this;
}

inline ConstStrBlobPtr ConstStrBlobPtr::operator--(int) {
    ConstStrBlobPtr ret = *this;
    --*this;
    return ret;
}

// RandomAccessIterator
inline ConstStrBlobPtr &ConstStrBlobPtr::operator+=(StrBlob::difference_type n) {
    curr_position += n;
    return *this;
}

inline ConstStrBlobPtr operator+(const ConstStrBlobPtr &lhs, StrBlob::difference_type n) {
    ConstStrBlobPtr temp = lhs;
    temp += n;
    return temp;
}

inline ConstStrBlobPtr operator+(StrBlob::difference_type n, const ConstStrBlobPtr &rhs) { return rhs + n; }

inline ConstStrBlobPtr &ConstStrBlobPtr::operator-=(StrBlob::difference_type n) { return *this += -n; }

inline ConstStrBlobPtr operator-(const ConstStrBlobPtr &lhs, StrBlob::difference_type n) {
    ConstStrBlobPtr temp = lhs;
    temp -= n;
    return temp;
}

inline StrBlob::difference_type operator-(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    if (!lhs.wptr.lock() || !rhs.wptr.lock()) { throw std::runtime_error("unbound StrBlobPtr"); }
    if (lhs.curr_position >= rhs.curr_position) {
        return lhs.curr_position - rhs.curr_position;
    } else {
        return -(static_cast<StrBlob::difference_type>(rhs.curr_position - lhs.curr_position));
    }
}

inline bool operator<(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position < rhs.curr_position);
}

inline bool operator<=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position <= rhs.curr_position);
}

inline bool operator>(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position > rhs.curr_position);
}

inline bool operator>=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position >= rhs.curr_position);
}

// internal function - test if weak_ptr points to valid data
inline std::shared_ptr<const std::vector<std::string>>
ConstStrBlobPtr::check(StrBlob::size_type i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) { throw std::runtime_error("unbound ConstStrBlobPtr"); }
    if (i >= ret->size()) { throw std::out_of_range(msg); }
    return ret;
}

// functions - data access
inline StrBlob::const_reference StrBlob::front() const { return *const_iterator(*this); }

inline StrBlob::const_reference StrBlob::back() const { return *const_iterator(*this, this->size() - 1); }

// functions - data access through iterators
inline StrBlob::const_iterator StrBlob::begin() const noexcept { return const_iterator(*this); }

inline StrBlob::const_iterator StrBlob::cbegin() const noexcept { return const_iterator(*this); }

inline StrBlob::const_iterator StrBlob::end() const noexcept { return const_iterator(*this, data->size()); }

inline StrBlob::const_iterator StrBlob::cend() const noexcept { return const_iterator(*this, data->size()); }

#endif //C_PRIMER_5TH_STRBLOB_H
