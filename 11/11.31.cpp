#include <map>
#include <string>
#include <iostream>
#include <sstream>

bool delete_author(std::multimap<std::string, std::string> literature) {
    std::cout << "Enter author name to delete from the previous list.\n";
    std::string delete_name;
    std::getline(std::cin, delete_name);
    auto delete_iter = literature.find(delete_name);
    if (delete_iter != literature.end()) {
        literature.erase(delete_iter);
        return true;
    } else {
        return false;
    }
}

int main() {
    std::multimap<std::string, std::string> literature;
    std::cout << "Enter author name and book name in \"author name/book name\" format (without the quotes).\n"
                 "Blank line to stop.\n";
    for (std::string input; std::getline(std::cin, input) && !input.empty();) {
        std::istringstream inp_stream(input);
        std::string author;
        std::getline(inp_stream, author, '/');
        std::string book;
        std::getline(inp_stream, book);
        literature.emplace(author, book);
    }
    delete_author(literature);

    for (auto curr = literature.cbegin(), last = literature.cend(); curr != last;) {
        std::cout << curr->first << '\n';
        auto range = literature.equal_range(curr->first);
        while (range.first != range.second) {
            std::cout << '\t' << range.first->second << '\n';
            ++range.first;
        }
        curr = range.second;
    }


    return 0;
}
