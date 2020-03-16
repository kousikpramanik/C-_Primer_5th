#ifndef C_PRIMER_5TH_TEXTQUERY_H
#define C_PRIMER_5TH_TEXTQUERY_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>

class QueryResult;

class TextQuery {
public: // constructors
    explicit TextQuery(std::istream &is); // fstream inherits from iostream

public: // functions
    QueryResult query(const std::string &s) const;

private: // data members
    std::shared_ptr<std::vector<std::string>> textptr;
    std::map<std::string, std::shared_ptr<std::multiset<std::vector<std::string>::size_type>>> wordmap;
};

class QueryResult {
    friend class TextQuery;

    friend std::ostream &print(std::ostream &os, const QueryResult &qr);

private: // constructor
    explicit QueryResult(const std::string &s,
                         std::shared_ptr<std::vector<std::string>> t,
                         std::shared_ptr<std::multiset<std::vector<std::string>::size_type>> w = nullptr) :
            query(s),
            textptr(t),
            wordset(w) {}

private: // data members
    std::string query;
    std::shared_ptr<std::vector<std::string>> textptr;
    std::shared_ptr<std::multiset<std::vector<std::string>::size_type>> wordset;
};

std::ostream &print(std::ostream &os, const QueryResult &qr);

#endif //C_PRIMER_5TH_TEXTQUERY_H
