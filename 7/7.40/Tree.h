#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <string>

class Tree {
    friend std::istream &read(std::istream &is, Tree &tr);

public:
    Tree(std::string k, std::string p, std::string c, std::string o, std::string f, std::string g, std::string s)
            : kingdom(k), phylum(p), bio_class(c), order(o), family(f), genus(g), species(s);

    Tree(std::istream &is) { read(is, *this); }

private:
    std::string kingdom;
    std::string phylum;
    std::string bio_class;
    std::string order;
    std::string family;
    std::string genus;
    std::string species;
};

std::istream &read(std::istream &is, Tree &tr);

#endif
