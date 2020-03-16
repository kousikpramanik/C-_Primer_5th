#include "TextQuery.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include "StrBlob.h"

TextQuery::TextQuery(std::istream &is) {
    std::string input;
    for (StrBlob::size_type linenum = 0; std::getline(is, input); ++linenum) {
        textptr.push_back(input);
        std::istringstream inputstream(input);
        for (std::string word; inputstream >> word;) {
            if (!wordmap[word]) { wordmap[word].reset(new std::multiset<StrBlob::size_type>); }
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
        for (auto set_iter = (*qr.wordset).cbegin();
             set_iter != (*qr.wordset).cend(); set_iter = (*qr.wordset).upper_bound(*set_iter)) {
            StrBlob::const_iterator blob_iter(qr.textptr, *set_iter);
            std::cout << "Line " << *set_iter + 1 << ": " << blob_iter.deref() << '\n';
        }
        std::cout << "Word \"" << qr.query << "\" occurred " << qr.wordset->size() << " times.";
    } else {
        os << "Word \"" << qr.query << "\" not found.";
    }

    return os;
}
