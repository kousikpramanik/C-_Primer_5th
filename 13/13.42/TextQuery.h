#ifndef C_PRIMER_5TH_TEXTQUERY_H
#define C_PRIMER_5TH_TEXTQUERY_H

#include "StrVec.h"
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <iostream>
#include <utility>

class QueryResult;

class TextQuery {
public:
    using line_no = StrVec::size_type;

    explicit TextQuery(std::ifstream &is);

    // no reason for two TextQuery objects to share the same pointer but have different maps
    // just create a new object for a new file/instance of the same file
    TextQuery(const TextQuery &other) = delete;

    TextQuery &operator=(const TextQuery &other) = delete;

    QueryResult query(const std::string &) const;

private:
    std::shared_ptr<StrVec> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, std::shared_ptr<StrVec> f) :
            sought(std::move(s)), lines(std::move(p)), file(std::move(f)) {}

    // the synthesised ones are fine, mention explicitly for the exercise.
    QueryResult(const QueryResult &other) = default;

    QueryResult &operator=(const QueryResult &other) = default;

    std::set<TextQuery::line_no>::iterator begin() { return lines->begin(); }

    std::set<TextQuery::line_no>::iterator end() { return lines->end(); }

    std::shared_ptr<StrVec> get_file() { return file; }

private:
    std::string sought;
    std::shared_ptr<std::set<TextQuery::line_no>> lines;
    std::shared_ptr<StrVec> file;
};

#endif //C_PRIMER_5TH_TEXTQUERY_H
