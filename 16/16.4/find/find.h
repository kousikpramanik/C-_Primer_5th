#ifndef C_PRIMER_5TH_FIND_H
#define C_PRIMER_5TH_FIND_H

template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T &value) {
    for (; first != last; ++first) {
        if (*first == value) {
            return first;
        }
    }
    return last;
}

#endif //C_PRIMER_5TH_FIND_H
