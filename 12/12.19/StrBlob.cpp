#include "StrBlob.h"
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

void StrBlob::check(StrBlob::size_type i, const std::string &msg) const {
    if (i >= data->size()) { throw std::out_of_range(msg); }
}

std::string &StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

const std::string &StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

const std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string &StrBlobPtr::deref() const {
    auto p = check(curr_position, "dereference past end");
    return (*p)[curr_position];
}

StrBlobPtr &StrBlobPtr::incr() {
    check(curr_position, "increment past end of StrBlobPtr");
    ++curr_position;
    return *this;
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(StrBlob::size_type i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) { throw std::runtime_error("unbound StrBlobPtr"); }
    if (i >= ret->size()) { throw std::out_of_range(msg); }
    return ret;
}
