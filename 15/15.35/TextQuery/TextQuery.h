#ifndef C_PRIMER_5TH_TEXTQUERY_H
#define C_PRIMER_5TH_TEXTQUERY_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <utility>

class QueryResult;

class TextQuery {
public: // constructors
    TextQuery(std::istream &is);

public:
    QueryResult query(const std::string &) const;

public: // types
    using line_no = std::vector<std::string>::size_type;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    friend std::ostream &operator<<(std::ostream &os, const QueryResult &qr);

public: // constructors
    QueryResult(std::string s,
                std::shared_ptr<std::set<TextQuery::line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) :
            sought(std::move(s)), lines(std::move(p)), file(std::move(f)) {}

public: // iterators
    std::set<TextQuery::line_no>::iterator begin() { return lines->begin(); }

    std::set<TextQuery::line_no>::const_iterator begin() const { return lines->begin(); }

    std::set<TextQuery::line_no>::const_iterator cbegin() const { return lines->begin(); }

    std::set<TextQuery::line_no>::iterator end() { return lines->end(); }

    std::set<TextQuery::line_no>::const_iterator end() const { return lines->end(); }

    std::set<TextQuery::line_no>::const_iterator cend() const { return lines->end(); }

public:
    std::shared_ptr<std::vector<std::string>> get_file() { return file; }

private:
    std::string sought;
    std::shared_ptr<std::set<TextQuery::line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

inline QueryResult TextQuery::query(const std::string &sought) const {
    static auto nodata = std::make_shared<std::set<line_no>>();
    auto loc = wm.find(sought);
    if (loc == wm.end()) {
        return QueryResult(sought, nodata, file);
    } else {
        return QueryResult(sought, loc->second, file);
    }
}

inline std::ostream &operator<<(std::ostream &os, const QueryResult &qr) {
    os << qr.sought << " occurred " << qr.lines->size() << " time" << (qr.lines->size() == 1 ? "" : "s") << '\n';
    for (auto num : qr) { os << "\t(line " << num + 1 << ") " << (*qr.file)[num] << '\n'; }
    return os;
}

#endif //C_PRIMER_5TH_TEXTQUERY_H
