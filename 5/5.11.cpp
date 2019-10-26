#include <iostream>
#include <cctype>

int main() {
    std::cout << "Keep entering text, EOF to stop" << std::endl;
    char input;
    unsigned long long aCnt, eCnt, iCnt, oCnt, uCnt, tabCnt, spcCnt, newCnt;
    aCnt = eCnt = iCnt = oCnt = uCnt = tabCnt = spcCnt = newCnt = 0;
    while (std::cin.get(input)) { // cin.operator>>() skips whitespace
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
            case ' ':
                ++spcCnt;
                break;
            case '\t':
                ++tabCnt;
                break;
            case '\n':
                ++newCnt;
                break;
        }
    }
    std::cout << "The text contained:" << std::endl;
    std::cout << "                 a: " << aCnt << std::endl;
    std::cout << "                 e: " << eCnt << std::endl;
    std::cout << "                 i: " << iCnt << std::endl;
    std::cout << "                 o: " << oCnt << std::endl;
    std::cout << "                 u: " << uCnt << std::endl;
    std::cout << "             space: " << spcCnt << std::endl;
    std::cout << "               tab: " << tabCnt << std::endl;
    std::cout << "           newline: " << newCnt << std::endl;

    return 0;
}
