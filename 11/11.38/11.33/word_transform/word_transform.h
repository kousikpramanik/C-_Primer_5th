#ifndef C_PRIMER_5TH_WORD_TRANSFORM_H
#define C_PRIMER_5TH_WORD_TRANSFORM_H

#include <fstream>
#include <unordered_map>
#include <string>

void word_transform(std::ifstream &map_file, std::ifstream &input);

std::unordered_map<std::string, std::string> buildMap(std::ifstream &map_file);

const std::string &transform(const std::string &s, const std::unordered_map<std::string, std::string> &m);

#endif //C_PRIMER_5TH_WORD_TRANSFORM_H
