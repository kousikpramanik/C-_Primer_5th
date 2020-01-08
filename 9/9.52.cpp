#include <iostream>
#include <stack>
#include <exception>

using precedence = unsigned;

bool isStackable(char ch) {
    switch (ch) {
        case '(':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            return true;
    }

    return false;
}

// lower in-stack precedence of opening parenthesis guarantees that anything can be stacked on top of it
precedence inStack(char ch) {
    switch (ch) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return -1;
    }
}

// higher out-stack precedence of opening parenthesis guarantees that two of them can be stacked
precedence outStack(char ch) {
    switch (ch) {
        case '(':
            return 3;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return -1;
    }
}

void inToPostfix(const std::string &infix, std::string &postfix) {
    std::stack<char> stk;
    for (auto c : infix) {
        if (isalpha(c)) { // operand
            postfix.push_back(c);
            postfix.push_back(' ');
        } else if (isStackable(c)) {
            while (!stk.empty() && inStack(stk.top()) >= outStack(c)) {
                postfix.push_back(stk.top());
                postfix.push_back(' ');
                stk.pop();
            }
            stk.push(c);
        } else if (c == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postfix.push_back(stk.top());
                postfix.push_back(' ');
                stk.pop();
            }
            if (stk.empty()) { throw std::invalid_argument("Extra ')'."); }
            stk.pop(); // pop the '(' character
        } else if (isspace(c)) {
            continue;
        } else {
            std::string err = "Invalid character '";
            err.push_back(c);
            err.append("'.");
            throw std::invalid_argument(err);
        }
    }
    while (!stk.empty()) {
        if (stk.top() == '(') { throw std::invalid_argument("Extra '('."); }
        postfix.push_back(stk.top());
        postfix.push_back(' ');
        stk.pop();
    }

    if (!postfix.empty()) { postfix.erase(postfix.end() - 1); } // delete last space
}

int main() {
    const std::string infix("(a + b) / ((c + d) * e) / g % h");
    std::string postfix;
    inToPostfix(infix, postfix);
    std::cout << "Infix: " << infix << '\n';
    std::cout << "Postfix: " << postfix << '\n';

    return 0;
}
