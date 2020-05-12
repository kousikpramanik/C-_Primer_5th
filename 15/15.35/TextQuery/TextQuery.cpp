#include "TextQuery.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <set>

TextQuery::TextQuery(std::istream &is) : file(std::make_shared<std::vector<std::string>>()) {
    std::string text;
    while (std::getline(is, text)) {
        file->push_back(text);
        auto n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            auto &lines = wm[word];
            if (!lines) { lines = std::make_shared<std::set<line_no>>(); }
            lines->insert(n);
        }
    }
}
