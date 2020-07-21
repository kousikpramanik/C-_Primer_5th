#ifndef C_PRIMER_5TH_BLOB_H
#define C_PRIMER_5TH_BLOB_H

#include <vector>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <cstdlib>

template<typename T>
class BlobPtr;

template<typename T>
class Blob;

template<typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs);

template<typename T>
bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs);

template<typename T>
bool operator<(const Blob<T> &lhs, const Blob<T> &rhs);

template<typename T>
bool operator<=(const Blob<T> &lhs, const Blob<T> &rhs);

template<typename T>
bool operator>(const Blob<T> &lhs, const Blob<T> &rhs);

template<typename T>
bool operator>=(const Blob<T> &lhs, const Blob<T> &rhs);

template<typename T>
class Blob {
    friend class BlobPtr<T>;

public: // types
    using value_type = T;
    using size_type = typename std::vector<T>::size_type;

public: // constructors
    Blob() : data(std::make_shared<std::vector<T>>()) {}

    template<typename Iter, typename std::enable_if<std::is_base_of<std::input_iterator_tag,
            typename std::iterator_traits<Iter>::iterator_category>::value, bool>::type = true>
    Blob(Iter first, Iter last) : data(std::make_shared<std::vector<T>>(first, last)) {}

    Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {}

public: // size related
    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

public: // add and remove elements
    void push_back(const T &t) { data->push_back(t); }

    void push_back(T &&t) { data->push_back(std::move(t)); }

    void pop_back();

public: // element access
    T &front();

    const T &front() const;

    T &back();

    const T &back() const;

    T &operator[](size_type i);

    const T &operator[](size_type i) const;

public: // non-members - order
    friend bool operator==<T>(const Blob<T> &lhs, const Blob<T> &rhs);

    friend bool operator!=<T>(const Blob<T> &lhs, const Blob<T> &rhs);

    friend bool operator<<
    T>(
    const Blob<T> &lhs,
    const Blob<T> &rhs
    );

    friend bool operator<=<T>(const Blob<T> &lhs, const Blob<T> &rhs);

    friend bool operator><T>(const Blob<T> &lhs, const Blob<T> &rhs);

    friend bool operator>=<T>(const Blob<T> &lhs, const Blob<T> &rhs);

private:
    std::shared_ptr<std::vector<T>> data;

    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

// add and remove elements
template<typename T>
inline void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

// element access
template<typename T>
inline T &Blob<T>::front() {
    check(0, "front on empty Blob");
    return data->front();
}

template<typename T>
inline const T &Blob<T>::front() const {
    check(0, "front on empty Blob");
    return data->front();
}

template<typename T>
inline T &Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
inline const T &Blob<T>::back() const {
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
inline T &Blob<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
inline const T &Blob<T>::operator[](size_type i) const {
    check(i, "subscript out of range");
    return (*data)[i];
}

// non-members - order
template<typename T>
inline bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
    return *(lhs.data) == *(rhs.data);
}

template<typename T>
inline bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs) { return *(lhs.data) != *(rhs.data); }

template<typename T>
inline bool operator<(const Blob<T> &lhs, const Blob<T> &rhs) { return *(lhs.data) < *(rhs.data); }

template<typename T>
inline bool operator<=(const Blob<T> &lhs, const Blob<T> &rhs) { return *(lhs.data) <= *(rhs.data); }

template<typename T>
inline bool operator>(const Blob<T> &lhs, const Blob<T> &rhs) { return *(lhs.data) > *(rhs.data); }

template<typename T>
inline bool operator>=(const Blob<T> &lhs, const Blob<T> &rhs) { return *(lhs.data) >= *(rhs.data); }

// private
template<typename T>
inline void Blob<T>::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) { throw std::out_of_range(msg); }
}

template<typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T>
bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T>
bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T>
bool operator<=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T>
bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T>
bool operator>=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

// BlobPtr throws an exception on attempts to access a nonexistent element
template<typename T>
class BlobPtr {
public: // constructors
    BlobPtr() : curr_position(0) {}

    explicit BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr_position(sz) {}

public: // dereference
    T &operator*() const;

public: // iterate through the vector
    BlobPtr &operator++();

    BlobPtr operator++(int) &;

    BlobPtr &operator--();

    BlobPtr operator--(int) &;

public: // relational operators

    friend bool operator==<T>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

    friend bool operator!=<T>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

    friend bool operator<<
    T>(
    const BlobPtr<T> &lhs,
    const BlobPtr<T> &rhs
    );

    friend bool operator<=<T>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

    friend bool operator><T>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

    friend bool operator>=<T>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

private:
    std::shared_ptr<std::vector<T>> check(std::size_t i, const std::string &msg) const;

    static void relational_check(const BlobPtr &lhs, const BlobPtr &rhs);

    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr_position;
};

// dereference
template<typename T>
inline T &BlobPtr<T>::operator*() const {
    auto p = check(curr_position, "dereference past end");
    return (*p)[curr_position];
}

// iterate through the vector
template<typename T>
inline BlobPtr<T> &BlobPtr<T>::operator++() {
    check(curr_position, "increment past end of BlobPtr");
    ++curr_position;
    return *this;
}

template<typename T>
inline BlobPtr<T> BlobPtr<T>::operator++(int) &{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template<typename T>
inline BlobPtr<T> &BlobPtr<T>::operator--() {
    auto ret = wptr.lock();
    if (!ret) { throw std::runtime_error("unbound BlobPtr"); }
    if (curr_position == 0) { throw std::out_of_range("decrement past begin of BlobPtr"); }
    --curr_position;
    return *this;
}

template<typename T>
inline BlobPtr<T> BlobPtr<T>::operator--(int) &{
    BlobPtr ret = *this;
    --*this;
    return ret;
}

// relational operators
template<typename T>
inline bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    BlobPtr<T>::relational_check(lhs, rhs);
    return lhs.curr_position == rhs.curr_position;
}

template<typename T>
inline bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    BlobPtr<T>::relational_check(lhs, rhs);
    return lhs.curr_position != rhs.curr_position;
}

template<typename T>
inline bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    BlobPtr<T>::relational_check(lhs, rhs);
    return lhs.curr_position < rhs.curr_position;
}

template<typename T>
inline bool operator<=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    BlobPtr<T>::relational_check(lhs, rhs);
    return lhs.curr_position <= rhs.curr_position;
}

template<typename T>
inline bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    BlobPtr<T>::relational_check(lhs, rhs);
    return lhs.curr_position > rhs.curr_position;
}

template<typename T>
inline bool operator>=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    BlobPtr<T>::relational_check(lhs, rhs);
    return lhs.curr_position >= rhs.curr_position;
}

// private
template<typename T>
inline std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) { throw std::runtime_error("unbound BlobPtr"); }
    if (i >= ret->size()) { throw std::out_of_range(msg); }
    return ret;
}

template<typename T>
inline void BlobPtr<T>::relational_check(const BlobPtr &lhs, const BlobPtr &rhs) {
    if (lhs.wptr.lock() != rhs.wptr.lock()) { throw std::invalid_argument("comparison between different Blobs"); }
}

#endif //C_PRIMER_5TH_BLOB_H
