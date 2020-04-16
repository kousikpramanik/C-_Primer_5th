#ifndef C_PRIMER_5TH_STRBLOB_H
#define C_PRIMER_5TH_STRBLOB_H

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

class StrBlobPtr;

class ConstStrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;

    friend class ConstStrBlobPtr;

    friend bool operator==(const StrBlob &lhs, const StrBlob &rhs);

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
    StrBlob() : data(new std::vector<std::string>) {}

    StrBlob(std::initializer_list<std::string> il) : data(new std::vector<std::string>(il)) {}

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

    iterator begin() noexcept;

    const_iterator begin() const noexcept;

    const_iterator cbegin() const noexcept;

    iterator end() noexcept;

    const_iterator end() const noexcept;

    const_iterator cend() const noexcept;

private: // internal function - data access tests
    void check(size_type i, const std::string &msg) const;

private: // internal data members
    std::shared_ptr<std::vector<std::string>> data;
};

// checks if the two StrBlobs have the same data, not whether they own the same object
inline bool operator==(const StrBlob &lhs, const StrBlob &rhs) { return *(lhs.data) == *(rhs.data); }

inline bool operator!=(const StrBlob &lhs, const StrBlob &rhs) { return !(lhs == rhs); }

class StrBlobPtr {
    friend bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

public: // constructors
    StrBlobPtr() : curr_position(0) {}

    explicit StrBlobPtr(StrBlob &a, StrBlob::size_type sz = 0) : wptr(a.data), curr_position(sz) {}

public: // other functions
    StrBlob::reference deref() const;

    StrBlobPtr &incr();

private: // internal function - test if weak ptr points to valid data
    std::shared_ptr<std::vector<std::string>> check(StrBlob::size_type i, const std::string &msg) const;

private: // internal data members
    std::weak_ptr<std::vector<std::string>> wptr;
    StrBlob::size_type curr_position;
};

inline bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position == rhs.curr_position);
}

inline bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !(lhs == rhs); }

class ConstStrBlobPtr {
    friend bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

public: // constructors
    ConstStrBlobPtr() : curr_position(0) {}

    explicit ConstStrBlobPtr(const StrBlob &a, StrBlob::size_type sz = 0) : wptr(a.data), curr_position(sz) {}

public: // other functions
    StrBlob::const_reference deref() const;

    ConstStrBlobPtr &incr();

private: // internal function - test if weak ptr points to valid data
    std::shared_ptr<const std::vector<std::string>> check(StrBlob::size_type i, const std::string &msg) const;

private: // internal data members
    std::weak_ptr<const std::vector<std::string>> wptr;
    StrBlob::size_type curr_position;
};

inline bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position == rhs.curr_position);
}

inline bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) { return !(lhs == rhs); }

inline StrBlob::iterator StrBlob::begin() noexcept { return iterator(*this); }

inline StrBlob::const_iterator StrBlob::begin() const noexcept { return const_iterator(*this); }

inline StrBlob::const_iterator StrBlob::cbegin() const noexcept { return const_iterator(*this); }

inline StrBlob::iterator StrBlob::end() noexcept { return iterator(*this, data->size()); }

inline StrBlob::const_iterator StrBlob::end() const noexcept { return const_iterator(*this, data->size()); }

inline StrBlob::const_iterator StrBlob::cend() const noexcept { return const_iterator(*this, data->size()); }

#endif //C_PRIMER_5TH_STRBLOB_H
