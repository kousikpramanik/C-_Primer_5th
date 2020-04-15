#include "Book.h"

#include <exception>

int Book::compare(const Book &other) const {
    if (this->name == other.name && this->author == other.author && this->isbn == other.isbn &&
        this->notes == other.notes) {
        if (this->reading < other.reading) {
            return -1;
        } else if (this->reading == other.reading) {
            return 0;
        } else {
            return 1;
        }
    } else {
        throw std::invalid_argument("Comparing different books");
    }
}
