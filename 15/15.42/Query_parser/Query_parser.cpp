#include "Query_parser.h"

#include <string>
#include <map>
#include <cstdint>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <utility>
#include "Query.h"
#include <vector>
#include <set>
#include <cctype>

namespace {
    std::string shunting_yard(const std::string &infix) {
        // lower in-stack precedence of opening parenthesis guarantees that anything can be stacked on top of it
        static const std::map<std::string, uint8_t> inStack{{"(", 0},
                                                            {"~", 3},
                                                            {"&", 2},
                                                            {"|", 1}};
        // higher out-stack precedence of opening parenthesis guarantees that two of them can be stacked
        static const std::map<std::string, uint8_t> outStack{{"(", 4},
                                                             {"~", 3},
                                                             {"&", 2},
                                                             {"|", 1},
                                                             {")", 0}};
        std::istringstream infixStream(infix);
        std::string postfix;
        postfix.reserve(infix.length());
        std::stack<std::string> operatorStack;
        std::string current_word;
        while (infixStream >> current_word) {
            auto outIter = outStack.find(current_word);
            if (outIter == outStack.cend()) {
                postfix += current_word;
                postfix += ' ';
            } else if (current_word == ")") {
                while (!operatorStack.empty() && operatorStack.top() != "(") {
                    postfix += operatorStack.top();
                    postfix += ' ';
                    operatorStack.pop();
                }
                if (operatorStack.empty()) { throw std::invalid_argument("Extra \")\"."); }
                operatorStack.pop(); // pop the "("
            } else {
                while (!operatorStack.empty() && inStack.at(operatorStack.top()) >= outIter->second) {
                    postfix += operatorStack.top();
                    postfix += ' ';
                    operatorStack.pop();
                }
                operatorStack.push(std::move(current_word));
            }
        }
        while (!operatorStack.empty()) {
            if (operatorStack.top() == "(") { throw std::invalid_argument("Extra \"(\"."); }
            postfix += operatorStack.top();
            postfix += ' ';
            operatorStack.pop();
        }

        if (!postfix.empty()) { postfix.pop_back(); } // delete last space
        return postfix;
    }

    Query history_expand(std::string current_word, const std::vector<Query> &history) {
        current_word.erase(0, 1);
        decltype(history.size()) position = 0;
        try {
            position = std::stoull(current_word);
        } catch (const std::invalid_argument &err) {
            position = 0;
        }
        return history.at(history.size() - position);
    }
}

Query strToQuery(const std::string &s, const std::vector<Query> &history) {
    static const std::set<std::string> nonStackable{"~", "&", "|"};
    const auto postfix = shunting_yard(s);
    std::istringstream postfixStream(postfix);
    std::stack<Query> evaluationStack;
    std::string current_word;
    while (postfixStream >> current_word) {
        if (nonStackable.find(current_word) == nonStackable.cend()) {
            if (current_word.length() > 1 && current_word[0] == '\\') {
                if (std::isdigit(current_word[1])) {
                    evaluationStack.push(history_expand(std::move(current_word), history));
                } else {
                    evaluationStack.emplace(std::string(current_word.begin() + 1, current_word.end()));
                }
            } else {
                evaluationStack.emplace(std::move(current_word));
            }
        } else {
            if (evaluationStack.empty()) { throw std::invalid_argument("Invalid number of operands."); }
            auto rhs = std::move(evaluationStack.top());
            evaluationStack.pop();
            if (current_word == "~") {
                evaluationStack.emplace(~std::move(rhs));
            } else {
                if (evaluationStack.empty()) { throw std::invalid_argument("Invalid number of operands."); }
                auto lhs = std::move(evaluationStack.top());
                evaluationStack.pop();
                if (current_word == "&") {
                    evaluationStack.emplace(std::move(lhs) & std::move(rhs));
                } else {
                    evaluationStack.emplace(std::move(lhs) | std::move(rhs));
                }
            }
        }
    }
    if (evaluationStack.size() != 1) { throw std::invalid_argument("Invalid number of operands."); }
    return std::move(evaluationStack.top());
}
