#include "StrBlob.h"
#include <string>
#include <vector>
#include <stdexcept>

void StrBlob::check(StrBlob::size_type i, const std::string &msg) const {
    if (i >= data->size()) { throw std::out_of_range(msg); }
}

StrBlob::reference StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

StrBlob::const_reference StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

StrBlob::reference StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlob::const_reference StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlob::reference StrBlobPtr::deref() const {
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

StrBlob::const_reference ConstStrBlobPtr::deref() const {
    auto p = check(curr_position, "dereference past end");
    return (*p)[curr_position];
}

ConstStrBlobPtr &ConstStrBlobPtr::incr() {
    check(curr_position, "increment past end of ConstStrBlobPtr");
    ++curr_position;
    return *this;
}

std::shared_ptr<const std::vector<std::string>>
ConstStrBlobPtr::check(StrBlob::size_type i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) { throw std::runtime_error("unbound ConstStrBlobPtr"); }
    if (i >= ret->size()) { throw std::out_of_range(msg); }
    return ret;
}
