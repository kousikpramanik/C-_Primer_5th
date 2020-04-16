#ifndef C_PRIMER_5TH_BOOK_H
#define C_PRIMER_5TH_BOOK_H

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <string>
#include <stdexcept>

class Book {
    friend std::ostream &operator<<(std::ostream &os, const Book &b);

    friend std::istream &operator>>(std::istream &is, Book &b);

public: // type members
    using page = unsigned;

public: // constructors
    explicit Book(std::string n) : name(std::move(n)) {}

    Book(std::string n, page r) : name(std::move(n)), reading(r) {}

    Book(std::string n, std::string a) : name(std::move(n)), author(std::move(a)) {}

    Book(std::string n, std::string a, page r) : name(std::move(n)), author(std::move(a)), reading(r) {}

    Book(std::string n, std::string a, std::string i) : name(std::move(n)), author(std::move(a)), isbn(std::move(i)) {}

    Book(std::string n, std::string a, std::string i, page r) : name(std::move(n)), author(std::move(a)),
                                                                isbn(std::move(i)), reading(r) {}

public: // operations related to page reading
    Book &operator=(page i);

    int compare(const Book &other) const;

private: // data members
    std::string name;
    std::string author;
    std::string isbn;
    page reading = 0;
    std::map<page, std::vector<std::string>> notes; // notes are inserted/deleted/viewed with member functions only
};

inline std::ostream &operator<<(std::ostream &os, const Book &b) {
    return os << b.name << " by " << b.author << ": Currently reading page " << b.reading;
}

inline std::istream &operator>>(std::istream &is, Book &b) {
    if (!(is >> b.name >> b.author >> b.isbn)) {
        b.name.clear();
        b.author.clear();
        b.isbn.clear();
    }
    b.reading = 0;
    b.notes.clear();
    return is;
}

inline Book &Book::operator=(page i) {
    reading = i;
    return *this;
}

inline bool operator==(const Book &lhs, const Book &rhs) {
    int result = 0;
    try {
        result = lhs.compare(rhs);
    } catch (const std::invalid_argument &e) {
        return false;
    }
    return result;
}

inline bool operator!=(const Book &lhs, const Book &rhs) { return !(lhs == rhs); }

inline bool operator<(const Book &lhs, const Book &rhs) { return lhs.compare(rhs) == -1; }

inline bool operator<=(const Book &lhs, const Book &rhs) { return lhs.compare(rhs) != 1; }

inline bool operator>(const Book &lhs, const Book &rhs) { return lhs.compare(rhs) == 1; }

inline bool operator>=(const Book &lhs, const Book &rhs) { return lhs.compare(rhs) != -1; }

#endif // C_PRIMER_5TH_BOOK_H
