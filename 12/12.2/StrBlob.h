#ifndef C_PRIMER_5TH_STRBLOB_H
#define C_PRIMER_5TH_STRBLOB_H

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

class StrBlob {
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

private: // internal function - data access tests
    void check(size_type i, const std::string &msg) const;

private: // internal data members
    std::shared_ptr<std::vector<std::string>> data;
};

#endif //C_PRIMER_5TH_STRBLOB_H
