#ifndef C_PRIMER_5TH_9_5_H
#define C_PRIMER_5TH_9_5_H

#include <vector>

std::vector<int>::iterator search(std::vector<int>::iterator begin, std::vector<int>::iterator end, int toSearch);

std::vector<int>::const_iterator
search(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end, int toSearch);

#endif
