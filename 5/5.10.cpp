#include <iostream>
#include <cctype>

int main() {
    std::cout << "Keep entering text, EOF to stop" << std::endl;
    char input;
    unsigned long long aCnt, eCnt, iCnt, oCnt, uCnt;
    aCnt = eCnt = iCnt = oCnt = uCnt = 0;
    while (std::cin >> input) {
        switch (std::tolower(input)) {
            case 'a':
                ++aCnt;
                break;
            case 'e':
                ++eCnt;
                break;
            case 'i':
                ++iCnt;
                break;
            case 'o':
                ++oCnt;
                break;
            case 'u':
                ++uCnt;
                break;
        }
    }
    std::cout << "The text contained:" << std::endl;
    std::cout << "                 a: " << aCnt << std::endl;
    std::cout << "                 e: " << eCnt << std::endl;
    std::cout << "                 i: " << iCnt << std::endl;
    std::cout << "                 o: " << oCnt << std::endl;
    std::cout << "                 u: " << uCnt << std::endl;

    return 0;
}
