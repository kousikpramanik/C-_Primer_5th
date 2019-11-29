#ifndef WINDOW_MGR_H_
#define WINDOW_MGR_H_

#include <vector>

class Screen;

class Window_mgr {
public: // type members
    using ScreenIndex = std::vector<Screen>::size_type;
public: // constructors
    Window_mgr(); // depends on Screen, defined in Screen_5.h

public: // other interface
    void clear(ScreenIndex i);

private: // data members
    std::vector<Screen> screens;
};

#endif
