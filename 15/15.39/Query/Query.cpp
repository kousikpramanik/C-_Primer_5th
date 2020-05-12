#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>

QueryResult NotQuery::eval(const TextQuery &text) const {
    auto before_not = query.eval(text);
    auto not_lines = std::make_shared<std::set<line_no>>();
    auto beg = before_not.begin(), end = before_not.end();
    auto sz = before_not.get_file()->size();
    for (line_no n = 0; n != sz; ++n) {
        if (beg == end || *beg != n) {
            not_lines->insert(n);
        } else if (beg != end) {
            ++beg;
        }
    }
    return QueryResult(what(), not_lines, before_not.get_file());
}
