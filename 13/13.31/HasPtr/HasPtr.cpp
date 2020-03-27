#include "HasPtr.h"

HasPtr &HasPtr::operator=(HasPtr other) {
    swap(*this, other);
    return *this;
}
