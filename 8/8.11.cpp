#include <string>
#include <vector>
#include <sstream>
#include <iostream>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

std::ostream &print(std::ostream &os, const PersonInfo &person) {
    os << person.name << '\n';
    for (const auto &s : person.phones)
        os << '\t' << s << '\n';

    return os;
}

int main() {
    std::string line, word;
    std::vector<PersonInfo> people;
    std::istringstream record;
    while (std::getline(std::cin, line) && !line.empty()) {
        PersonInfo info;
        record.str(line);
        record.clear();
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }
    for (const auto &person : people) {
        print(std::cout, person) << "---------------------------\n";
    }

    return 0;
}
