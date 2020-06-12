#ifndef C_PRIMER_5TH_SCREEN_H
#define C_PRIMER_5TH_SCREEN_H

#include <cstdlib>
#include <array>
#include <iostream>
#include <stdexcept>

template<std::size_t HT, std::size_t WD>
class Screen {
public: // type members
    using pos = std::size_t;
public: // constructors
    Screen(char ch = ' ');

public: // other interface
    char get() const;

    char get(pos r, pos c) const;

    Screen &move(pos r, pos c);

    Screen &set(char ch);

    Screen &set(pos r, pos c, char ch);

    friend std::ostream &operator<<(std::ostream &os, const Screen &s) { return os << s.contents.data(); }

    friend std::istream &operator>>(std::istream &is, Screen &s) { return is >> s.contents[s.cursor]; }

private:
    pos bounds_check(pos r, pos c) const;

private: // data members
    pos cursor = 0;
    std::array<char, HT * WD> contents;
};

template<std::size_t HT, std::size_t WD>
inline Screen<HT, WD>::Screen(char ch) {
    for (auto &c : contents) { c = ch; }
}

template<std::size_t HT, std::size_t WD>
inline char Screen<HT, WD>::get() const { return contents[cursor]; }

template<std::size_t HT, std::size_t WD>
inline char Screen<HT, WD>::get(pos r, pos c) const {
    return contents[bounds_check(r, c)];
}

template<std::size_t HT, std::size_t WD>
inline Screen<HT, WD> &Screen<HT, WD>::move(pos r, pos c) {
    cursor = bounds_check(r, c);
    return *this;
}

template<std::size_t HT, std::size_t WD>
inline Screen<HT, WD> &Screen<HT, WD>::set(char ch) {
    contents[cursor] = ch;
    return *this;
}

template<std::size_t HT, std::size_t WD>
inline Screen<HT, WD> &Screen<HT, WD>::set(pos r, pos c, char ch) {
    contents[bounds_check(r, c)] = ch;
    return *this;
}

template<std::size_t HT, std::size_t WD>
inline typename Screen<HT, WD>::pos Screen<HT, WD>::bounds_check(pos r, pos c) const {
    auto spot = r * WD + c;
    if (spot >= contents.size()) { throw std::invalid_argument("Accesing beyond screen boundary!"); }
    return spot;
}

#endif //C_PRIMER_5TH_SCREEN_H
