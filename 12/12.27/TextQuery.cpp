#include "TextQuery.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <set>

TextQuery::TextQuery(std::istream &is) : textptr(new std::vector<std::string>) {
    std::string input;
    for (std::vector<std::string>::size_type linenum = 0; std::getline(is, input); ++linenum) {
        textptr->push_back(input);
        std::istringstream inputstream(input);
        for (std::string word; inputstream >> word;) {
            if (!wordmap[word]) { wordmap[word].reset(new std::multiset<std::vector<std::string>::size_type>); }
            wordmap[word]->insert(linenum);
        }
    }
}

QueryResult TextQuery::query(const std::string &s) const {
    auto w = wordmap.find(s);
    if (w != wordmap.cend()) {
        return QueryResult(s, textptr, w->second);
    } else {
        return QueryResult(s, textptr);
    }
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
    if (qr.wordset) {
        for (auto iter = (*qr.wordset).cbegin();
             iter != (*qr.wordset).cend(); iter = (*qr.wordset).upper_bound(*iter)) {
            std::cout << "Line " << *iter + 1 << ": " << (*qr.textptr)[*iter] << '\n';
        }
        std::cout << "Word \"" << qr.query << "\" occurred " << qr.wordset->size() << " times.";
    } else {
        os << "Word \"" << qr.query << "\" not found.";
    }

    return os;
}
