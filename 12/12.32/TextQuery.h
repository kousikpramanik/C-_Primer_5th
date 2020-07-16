#ifndef C_PRIMER_5TH_TEXTQUERY_H
#define C_PRIMER_5TH_TEXTQUERY_H

#include "StrBlob.h"
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <set>
#include <iostream>

class QueryResult;

class TextQuery {
public:
    using line_no = StrBlob::size_type;

    TextQuery(std::ifstream &is);

    QueryResult query(const std::string &sought) const;

private:
    StrBlob file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    friend std::ostream &print(std::ostream &os, const QueryResult &qr);

public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<TextQuery::line_no>> p,
                StrBlob f) :
            sought(s), lines(p), file(f) {}

private:
    std::string sought;
    std::shared_ptr<std::set<TextQuery::line_no>> lines;
    StrBlob file;
};

std::ostream &print(std::ostream &os, const QueryResult &qr);

#endif //C_PRIMER_5TH_TEXTQUERY_H
