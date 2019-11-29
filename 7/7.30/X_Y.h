#ifndef X_Y_H_
#define X_Y_H_

class Y;

class X {
    Y *yptr;
};

class Y {
    X xobj;
};

#endif
