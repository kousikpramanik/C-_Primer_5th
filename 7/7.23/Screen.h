#ifndef C_PRIMER_5TH_SCREEN_H
#define C_PRIMER_5TH_SCREEN_H

#include <string>

class Screen {
public: // type members
    using pos = std::string::size_type;
public: // constructors
    Screen() = default;

    Screen(pos ht, pos wd, char ch) : height(ht), width(wd), contents(ht * wd, ch) {}

public: // other interface
    char get() const { return contents[cursor]; }

    char get(pos r, pos c) const { return contents[r * width + c]; }

    Screen &move(pos r, pos c);

private: // data members
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};

inline Screen &Screen::move(pos r, pos c) {
    cursor = r * width + c;
    return *this;
}

#endif //C_PRIMER_5TH_SCREEN_H
