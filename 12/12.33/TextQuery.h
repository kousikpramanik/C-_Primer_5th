#ifndef C_PRIMER_5TH_TEXTQUERY_H
#define C_PRIMER_5TH_TEXTQUERY_H

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <iostream>

class QueryResult;

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;

    TextQuery(std::ifstream &is);

    QueryResult query(const std::string &sought) const;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    friend std::ostream &print(std::ostream &os, const QueryResult &qr);

public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<TextQuery::line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) :
            sought(s), lines(p), file(f) {}

    std::set<TextQuery::line_no>::iterator begin() { return lines->begin(); }

    std::set<TextQuery::line_no>::iterator end() { return lines->end(); }

    std::shared_ptr<std::vector<std::string>> get_file() { return file; }

private:
    std::string sought;
    std::shared_ptr<std::set<TextQuery::line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

std::ostream &print(std::ostream &os, const QueryResult &qr);

#endif //C_PRIMER_5TH_TEXTQUERY_H
