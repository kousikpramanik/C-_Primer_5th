#ifndef C_PRIMER_5TH_BEGIN_END_H
#define C_PRIMER_5TH_BEGIN_END_H

#include <cstdlib>

template<class T, std::size_t N>
T *begin(T (&arr)[N]) { return arr; }

template<class T, std::size_t N>
T *end(T (&arr)[N]) { return arr + N; }

#endif //C_PRIMER_5TH_BEGIN_END_H
