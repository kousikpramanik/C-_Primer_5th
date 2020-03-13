#include <iostream>
#include <cstring>

char *concat(const char *arr1, const char *arr2) {
    auto ret = new char[std::strlen(arr1) + std::strlen(arr2) + 1];
    size_t i = 0;
    for (size_t j = 0; j != std::strlen(arr1); ++j, ++i) { ret[i] = arr1[j]; }
    for (size_t j = 0; j != std::strlen(arr2); ++j, ++i) { ret[i] = arr2[j]; }
    ret[i] = '\0';

    return ret;
}

int main() {
    char arr1[] = "this is a test.";
    char arr2[] = "this is also a test.";

    auto arr1spc = concat(arr1, " ");
    auto arr12 = concat(arr1spc, arr2);
    delete[] arr1spc;

    std::cout << arr12;

    delete[] arr12;
    return 0;
}
