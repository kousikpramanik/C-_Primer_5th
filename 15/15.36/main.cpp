#include "Query.h"

int main() {
    Query q = Query("fiery") & Query("bird") | Query("wind");
    q.what();
    return 0;
}
