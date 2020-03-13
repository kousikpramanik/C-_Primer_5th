#ifndef C_PRIMER_5TH_STRBLOB_H
#define C_PRIMER_5TH_STRBLOB_H

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

class StrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;

public: // data types
    using size_type = std::vector<std::string>::size_type;
public: // constructors
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

    StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

public: // functions - related to size
    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

public: // functions - add and remove data
    void push_back(const std::string &s) { data->push_back(s); }

    void pop_back();

public: // functions - data access
    std::string &front();

    const std::string &front() const;

    std::string &back();

    const std::string &back() const;

    StrBlobPtr begin();

    StrBlobPtr end();

private: // internal function - data access tests
    void check(size_type i, const std::string &msg) const;

private: // internal data members
    std::shared_ptr<std::vector<std::string>> data;
};

class StrBlobPtr {
    friend bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

public: // constructors
    StrBlobPtr() : curr_position(0) {}

    explicit StrBlobPtr(StrBlob &a, StrBlob::size_type sz = 0) : wptr(a.data), curr_position(sz) {}

public: // other functions
    std::string &deref() const;

    StrBlobPtr &incr();

private: // internal function - test if weak ptr points to valid data
    std::shared_ptr<std::vector<std::string>> check(StrBlob::size_type i, const std::string &msg) const;

private: // internal data members
    std::weak_ptr<std::vector<std::string>> wptr;
    StrBlob::size_type curr_position;
};

inline bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr_position == rhs.curr_position);
}

inline bool unequal(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !equal(lhs, rhs); }

inline StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

inline StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }

#endif //C_PRIMER_5TH_STRBLOB_H
