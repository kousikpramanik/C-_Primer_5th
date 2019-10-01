#include <iostream>
#include <cctype>

int main() {
    std::cout << "Keep entering text, EOF to stop" << std::endl;
    char input;
    unsigned long long aCnt, eCnt, iCnt, oCnt, uCnt;
    aCnt = eCnt = iCnt = oCnt = uCnt = 0;
    while (std::cin >> input) {
        if (std::tolower(input) == 'a')
            ++aCnt;
        else if (std::tolower(input) == 'e')
            ++eCnt;
        else if (std::tolower(input) == 'i')
            ++iCnt;
        else if (std::tolower(input) == 'o')
            ++oCnt;
        else if (std::tolower(input) == 'u')
            ++uCnt;
    }
    std::cout << "The text contained:" << std::endl;
    std::cout << "                 a: " << aCnt << std::endl;
    std::cout << "                 e: " << eCnt << std::endl;
    std::cout << "                 i: " << iCnt << std::endl;
    std::cout << "                 o: " << oCnt << std::endl;
    std::cout << "                 u: " << uCnt << std::endl;

    return 0;
}
