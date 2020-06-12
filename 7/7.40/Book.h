#ifndef C_PRIMER_5TH_BOOK_H
#define C_PRIMER_5TH_BOOK_H

#include <vector>
#include <string>

class Book {
public: // type members
    using page = unsigned;

private: // type members
    using note = struct {
        std::string text;
        page pgNum;
    };

public: // constructors
    Book(std::string n) : name(n) {}

    Book(std::string n, page r) : name(n), reading(r) {}

    Book(std::string n, std::string a) : name(n), author(a) {}

    Book(std::string n, std::string a, page r) : name(n), author(a), reading(r) {}

    Book(std::string n, std::string a, std::string i) : name(n), author(a), isbn(i) {}

    Book(std::string n, std::string a, std::string i, page r) : name(n), author(a), isbn(i), reading(r) {}

private: // data members
    std::string name;
    std::string author;
    std::string isbn;
    page reading = 0;
    std::vector<note> bookmarks; // notes are inserted/deleted/viewed with member functions only
};

#endif //C_PRIMER_5TH_BOOK_H
