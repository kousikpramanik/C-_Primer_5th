#ifndef C_PRIMER_5TH_QUERY_H
#define C_PRIMER_5TH_QUERY_H

#include "TextQuery.h"
#include <string>
#include <utility>
#include <memory>
#include <iostream>

class Query_base {
    friend class Query;

protected:
    using line_no = TextQuery::line_no;

    Query_base() = default;

    Query_base(const Query_base &other) = default;

    Query_base &operator=(const Query_base &other) = default;

    Query_base(Query_base &&other) noexcept = default;

    Query_base &operator=(Query_base &&other) noexcept = default;

    virtual ~Query_base() = default;

private:
    virtual std::string what() const = 0;
};

class WordQuery : public Query_base {
    friend class Query;

private:
    WordQuery(std::string s) : query_word(std::move(s)) {}

    std::string what() const override { return query_word; }

private:
    std::string query_word;
};

class Query {
    friend Query operator~(const Query &operand);

    friend Query operator|(const Query &lhs, const Query &rhs);

    friend Query operator&(const Query &lhs, const Query &rhs);

    friend class NotQuery;

    friend class BinaryQuery;

public:
    Query(std::string s) : q(new WordQuery(std::move(s))) {}

    std::string what() const { return q->what(); }

private:
    Query(std::shared_ptr<Query_base> query) : q(std::move(query)) {}

    std::shared_ptr<Query_base> q;
};

inline std::ostream &operator<<(std::ostream &os, const Query &query) { return os << query.what(); }

class NotQuery : public Query_base {
    friend Query operator~(const Query &operand);

private:
    NotQuery(std::shared_ptr<Query_base> q) : query(std::move(q)) {}

    std::string what() const override { return "~(" + Query(query).what() + ')'; }

private:
    std::shared_ptr<Query_base> query;
};

inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand.q));
}

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(std::shared_ptr<Query_base> l, decltype(l) r, char s) : lhs(std::move(l)), rhs(std::move(r)),
                                                                        opSym(s) {}

    std::string what() const override { return '(' + Query(lhs).what() + ' ' + opSym + ' ' + Query(rhs).what() + ')'; }

    std::shared_ptr<Query_base> lhs, rhs;
    char opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &lhs, const Query &rhs);

private:
    AndQuery(std::shared_ptr<Query_base> left, decltype(left) right) : BinaryQuery(std::move(left), std::move(right),
                                                                                   '&') {}
};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs.q, rhs.q));
}

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &lhs, const Query &rhs);

private:
    OrQuery(std::shared_ptr<Query_base> left, decltype(left) right) : BinaryQuery(std::move(left), std::move(right),
                                                                                  '|') {}
};

inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs.q, rhs.q));
}

#endif //C_PRIMER_5TH_QUERY_H
