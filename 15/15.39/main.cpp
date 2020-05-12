#include "Query.h"
#include <iostream>

int main() {
    Query q = Query("fiery") & Query("bird") | Query("wind");
    std::cout << q.eval(std::cin);
    return 0;
}
