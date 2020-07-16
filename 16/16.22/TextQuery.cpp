#include "TextQuery.h"

#include <fstream>
#include <vector>
#include <string>
#include "DebugDelete.h"
#include <memory>
#include <sstream>
#include <set>

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>, DebugDelete()) {
    std::string text;
    while (std::getline(is, text)) {
        file->push_back(text);
        auto n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            auto &lines = wm[word];
            if (!lines) { lines.reset(new std::set<line_no>, DebugDelete()); }
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>, DebugDelete());
    auto loc = wm.find(sought);
    if (loc == wm.end()) {
        return QueryResult(sought, nodata, file);
    } else {
        return QueryResult(sought, loc->second, file);
    }
}
