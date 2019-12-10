#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>

class Object {
    friend std::istream &read(std::istream &is, Object &obj);

public:
    Object(std::string n, std::string o = "") : name(n), owner(o) {}

    Object(std::istream &is) { read(is, *this); }

private:
    std::string name;
    std::string owner;
};

std::istream &read(std::istream &is, Object &obj);

#endif
