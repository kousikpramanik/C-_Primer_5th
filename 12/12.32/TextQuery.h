#ifndef C_PRIMER_5TH_TEXTQUERY_H
#define C_PRIMER_5TH_TEXTQUERY_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include "StrBlob.h"

class QueryResult;

class TextQuery {
public: // constructors
    explicit TextQuery(std::istream &is); // fstream inherits from iostream

public: // functions
    QueryResult query(const std::string &s) const;

private: // data members
    StrBlob textptr;
    std::map<std::string, std::shared_ptr<std::multiset<StrBlob::size_type>>> wordmap;
};

class QueryResult {
    friend class TextQuery;

    friend std::ostream &print(std::ostream &os, const QueryResult &qr);

private: // constructor
    explicit QueryResult(const std::string &s,
                         const StrBlob &t,
                         std::shared_ptr<std::multiset<StrBlob::size_type>> w = nullptr) :
            query(s),
            textptr(t),
            wordset(w) {}

private: // data members
    std::string query;
    StrBlob textptr;
    std::shared_ptr<std::multiset<StrBlob::size_type>> wordset;
};

std::ostream &print(std::ostream &os, const QueryResult &qr);

#endif //C_PRIMER_5TH_TEXTQUERY_H
