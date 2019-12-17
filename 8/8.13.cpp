#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iostream>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

inline bool valid(const std::string &num) {
    static const std::regex GLOBAL_PHONE_NUMBER_PATTERN("[\\+]?[0-9.-]+"); // from Android's PhoneNumberUtils.java
    return std::regex_match(num, GLOBAL_PHONE_NUMBER_PATTERN);
}

// TODO: rewrite this from Android's PhoneNumberUtils.java
inline std::string format(const std::string &num) {
    return num;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " [INPUT FILE] [OUTPUT FILE] append(optional)\n";
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "Failed to open \'" << argv[1] << "\'\n";
        return EXIT_FAILURE;
    }

    std::ofstream ofs;
    if (argc == 4 && (std::strcmp(argv[3], "append") == 0))
        ofs.open(argv[2], std::fstream::out | std::fstream::app);
    else
        ofs.open(argv[2]); // out and trunc

    if (!ofs) {
        std::cerr << "Failed to open \'" << argv[2] << "\'\n";
        return EXIT_FAILURE;
    }

    std::string line, word;
    std::vector<PersonInfo> people;
    std::istringstream record;
    while (getline(ifs, line) && !line.empty()) {
        PersonInfo info;
        record.str(line);
        record.clear();
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }
    for (const auto &entry : people) {
        std::ostringstream formatted, badNums;
        for (const auto &nums : entry.phones) {
            if (!valid(nums)) {
                badNums << ' ' << nums;
            } else
                formatted << ' ' << format(nums);
        }
        if (badNums.str().empty())
            ofs << entry.name << ' ' << formatted.str() << '\n';
        else
            std::cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() << '\n';
    }

    return 0;
}
