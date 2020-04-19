#ifndef C_PRIMER_5TH_IF_THEN_ELSE_H
#define C_PRIMER_5TH_IF_THEN_ELSE_H

struct if_then_else {
    int operator()(bool a, int b, int c) { return a ? b : c; }
};

#endif //C_PRIMER_5TH_IF_THEN_ELSE_H
