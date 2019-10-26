// it worsens readability. val, ++val is hard to understand. if there are more
// statements joined like this, it would become impossible to understand.

#include <iostream>

int main() {
    int sum = 0, val = 1;
    while (val <= 10)
        sum += val, ++val;
    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;

    return 0;
}
