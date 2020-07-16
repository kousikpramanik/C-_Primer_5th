#ifndef C_PRIMER_5TH_DEBUGDELETE_H
#define C_PRIMER_5TH_DEBUGDELETE_H

#include <iostream>

class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}

    template<typename T>
    void operator()(T *p) const {
        os << "DebugDelete called\n";
        delete p;
    }

private:
    std::ostream &os;
};

#endif //C_PRIMER_5TH_DEBUGDELETE_H
