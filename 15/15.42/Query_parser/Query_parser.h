#ifndef C_PRIMER_5TH_QUERY_PARSER_H
#define C_PRIMER_5TH_QUERY_PARSER_H

#include "Query.h"
#include <string>
#include <vector>

Query strToQuery(const std::string &s, const std::vector<Query> &history);

#endif //C_PRIMER_5TH_QUERY_PARSER_H
