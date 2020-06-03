#ifndef C_PRIMER_5TH_SIZE_H
#define C_PRIMER_5TH_SIZE_H

#include <cstdlib>

template<class T, std::size_t N>
constexpr std::size_t size(const T (&arr)[N]) { return N; }

#endif //C_PRIMER_5TH_SIZE_H
