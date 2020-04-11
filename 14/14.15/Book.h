#ifndef C_PRIMER_5TH_BOOK_H
#define C_PRIMER_5TH_BOOK_H

#include <vector>
#include <string>

class Book {
    friend std::ostream &operator<<(std::ostream &os, const Book &b);

    friend std::istream &operator>>(std::istream &is, Book &b);

    friend bool operator==(const Book &lhs, const Book &rhs);

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

    Book(std::string n, std::string a, std::string i, page r) : name(n), author(a), isbn(i), page(r) {}

public: // operators
    inline Book &operator=(page i);

private: // data members
    std::string name;
    std::string author;
    std::string isbn;
    page reading = 0;
    std::vector<note> bookmarks; // notes are inserted/deleted/viewed with member functions only
};

inline std::ostream &operator<<(std::ostream &os, const Book &b) {
    return os << b.name << " by " << b.author << ": Currently reading page " << b.reading;
}

inline std::istream &operator>>(std::istream &is, Book &b) {
    if (!is >> name >> author >> isbn) {
        name.clear();
        author.clear();
        isbn.clear();
        reading = 0;
        bookmarks.clear();
    }
    return is;
}

inline bool operator==(const Book &lhs, const Book &rhs) {
    return lhs.name == rhs.name && lhs.author == rhs.author && lhs.isbn == rhs.isbn && lhs.reading == rhs.reading &&
           lhs.bookmarks == rhs.bookmarks;
}

inline bool operator!=(const Book &lhs, const Book &rhs) { return !(lhs == rhs); }

inline Book &operator=(page i) {
    reading = i;
    return *this;
}

#endif // C_PRIMER_5TH_BOOK_H
