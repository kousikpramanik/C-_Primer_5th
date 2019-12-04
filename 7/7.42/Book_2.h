#ifndef BOOK_2_H_
#define BOOK_2_H_

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
    Book(std::string n, std::string a, std::string i, page r) : name(n), author(a), isbn(i), page(r) {}

    Book(std::string n, std::string a, std::string i) : Book(n, a, i, 0) {}

    Book(std::string n, std::string a, page r) : Book(n, a, "", r) {}

    Book(std::string n, std::string a) : Book(n, a, "", 0) {}

    Book(std::string n, page r) : Book(n, "", "", r) {}

    Book(std::string n) : Book(n, "", "", 0) {}

private: // data members
    std::string name;
    std::string author;
    std::string isbn;
    page reading = 0;
    std::vector<note> bookmarks; // notes are inserted/deleted/viewed with member functions only
};

#endif
