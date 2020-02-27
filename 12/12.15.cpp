#include <memory>
#include <array>
#include <cstring>
#include <iostream>
#include <type_traits>

extern "C" {
#include "connect.h"
}

void f(const destination &dest) {
    std::array<char, 256> msg{};
    std::shared_ptr<std::remove_pointer<connectionptr>::type> conn(connect(&dest), [](connectionptr conn) {
        if (conn) {
            disconnect(conn);
        }
    });
    std::strcpy(msg.data(), "test 1");
    std::cout << R"(msg after calling strcpy() with "test 1": ")" << msg.data() << "\"\n";
    send(conn.get(), true, msg.data());
    std::strcpy(msg.data(), "");
    std::cout << R"(msg after calling send() and calling strcpy() with "": ")" << msg.data() << "\"\n";
    receive(conn.get(), msg.data());
    std::cout << R"(msg after calling receive(): ")" << msg.data() << "\"\n";
}

int main() {
    destination dest{2130706433, 80}; // 2130706433 = 127.0.0.1
    f(dest);
    return 0;
}
