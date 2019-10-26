#include <iostream>
#include <cctype>

int main() {
    std::cout << "Keep entering text, EOF to stop" << std::endl;
    char input;
    unsigned long long aCnt = 0;
    unsigned long long eCnt = 0;
    unsigned long long iCnt = 0;
    unsigned long long oCnt = 0;
    unsigned long long uCnt = 0;
    unsigned long long tabCnt = 0;
    unsigned long long spcCnt = 0;
    unsigned long long newCnt = 0;
    unsigned long long ffCnt = 0;
    unsigned long long flCnt = 0;
    unsigned long long fiCnt = 0;
    bool inSequence = false;
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
            default:
                if (inSequence)
                    switch (std::tolower(input)) {
                        case 'f':
                            ++ffCnt;
                            inSequence = false;
                            break;
                        case 'l':
                            ++flCnt;
                            inSequence = false;
                            break;
                        case 'i':
                            ++fiCnt;
                            inSequence = false;
                            break;
                    }
                else if (std::tolower(input) == 'f')
                    inSequence = true;
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
    std::cout << "       ff sequence: " << ffCnt << std::endl;
    std::cout << "       fl sequence: " << flCnt << std::endl;
    std::cout << "       fi sequence: " << fiCnt << std::endl;

    return 0;
}
