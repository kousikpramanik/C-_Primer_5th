#ifndef C_PRIMER_5TH_QUERY_H
#define C_PRIMER_5TH_QUERY_H

#include "TextQuery.h"
#include <iostream>
#include <string>
#include <utility>
#include <memory>

class Query_base {
    friend class Query;

protected:
    using line_no = TextQuery::line_no;

    Query_base();

    Query_base(const Query_base &other);

    Query_base &operator=(const Query_base &other) = default;

    Query_base(Query_base &&other) noexcept;

    Query_base &operator=(Query_base &&other) noexcept = default;

    virtual ~Query_base() = default;

private:
    virtual std::string what() const = 0;
};

inline Query_base::Query_base() {
#ifndef NDEBUG
    std::clog << "In function: Query_base::" << __func__ << "()\n";
#endif // NDEBUG
}

inline Query_base::Query_base(const Query_base &other) {
#ifndef NDEBUG
    std::clog << "In function: Query_base::" << __func__ << "(const Query_base &other)\n";
#endif // NDEBUG
}

inline Query_base::Query_base(Query_base &&other) noexcept {
#ifndef NDEBUG
    std::clog << "In function: Query_base::" << __func__ << "(Query_base &&other) noexcept\n";
#endif // NDEBUG
}

class WordQuery : public Query_base {
    friend class Query;

private:
    WordQuery(std::string s);

    std::string what() const override;

private:
    std::string query_word;
};

inline WordQuery::WordQuery(std::string s) : query_word(std::move(s)) {
#ifndef NDEBUG
    std::clog << "In function: WordQuery::" << __func__ << "(std::string s)\n";
#endif // NDEBUG
}

inline std::string WordQuery::what() const {
#ifndef NDEBUG
    std::clog << "In function: WordQuery::" << __func__ << "() const\n";
#endif // NDEBUG
    return query_word;
}

class Query {
    friend Query operator~(Query operand);

    friend Query operator|(Query lhs, Query rhs);

    friend Query operator&(Query lhs, Query rhs);

public:
    Query(std::string s);

    std::string what() const;

private:
    Query(std::shared_ptr<Query_base> query);

    std::shared_ptr<Query_base> q;
};

inline Query::Query(std::string s) : q(new WordQuery(std::move(s))) {
#ifndef NDEBUG
    std::clog << "In function: Query::" << __func__ << "(std::string s)\n";
#endif // NDEBUG
}

inline std::string Query::what() const {
#ifndef NDEBUG
    std::clog << "In function: Query::" << __func__ << "() const\n";
#endif // NDEBUG
    return q->what();
}

inline Query::Query(std::shared_ptr<Query_base> query) : q(std::move(query)) {
#ifndef NDEBUG
    std::clog << "In function: Query::" << __func__ << "(std::shared_ptr<Query_base> query)\n";
#endif // NDEBUG
}

inline std::ostream &operator<<(std::ostream &os, const Query &query) { return os << query.what(); }

class NotQuery : public Query_base {
    friend Query operator~(Query operand);

private:
    NotQuery(Query q);

    std::string what() const override;

private:
    Query query;
};

inline NotQuery::NotQuery(Query q) : query(std::move(q)) {
#ifndef NDEBUG
    std::clog << "In function: NotQuery::" << __func__ << "(Query q)\n";
#endif // NDEBUG
}

inline std::string NotQuery::what() const {
#ifndef NDEBUG
    std::clog << "In function: NotQuery::" << __func__ << "()\n";
#endif // NDEBUG
    return "~ ( " + query.what() + " )";
}

inline Query operator~(Query operand) {
    return std::shared_ptr<Query_base>(new NotQuery(std::move(operand)));
}

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(Query l, Query r, char s);

    std::string what() const override;

    Query lhs, rhs;
    char opSym;
};

inline BinaryQuery::BinaryQuery(Query l, Query r, char s) : lhs(std::move(l)), rhs(std::move(r)), opSym(s) {
#ifndef NDEBUG
    std::clog << "In function: BinaryQuery::" << __func__ << "(Query l, Query r, char s)\n";
#endif // NDEBUG
}

inline std::string BinaryQuery::what() const {
#ifndef NDEBUG
    std::clog << "In function: BinaryQuery::" << __func__ << "()\n";
#endif // NDEBUG
    return "( " + lhs.what() + ' ' + opSym + ' ' + rhs.what() + " )";
}

class AndQuery : public BinaryQuery {
    friend Query operator&(Query lhs, Query rhs);

private:
    AndQuery(Query left, Query right);
};

inline AndQuery::AndQuery(Query left, Query right) : BinaryQuery(std::move(left), std::move(right), '&') {
#ifndef NDEBUG
    std::clog << "In function: AndQuery::" << __func__ << "(Query left, Query right)\n";
#endif // NDEBUG
}

inline Query operator&(Query lhs, Query rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(std::move(lhs), std::move(rhs)));
}

class OrQuery : public BinaryQuery {
    friend Query operator|(Query lhs, Query rhs);

private:
    OrQuery(Query left, Query right);
};

inline OrQuery::OrQuery(Query left, Query right) : BinaryQuery(std::move(left), std::move(right), '|') {
#ifndef NDEBUG
    std::clog << "In function: OrQuery::" << __func__ << "(Query left, Query right)\n";
#endif // NDEBUG
}

inline Query operator|(Query lhs, Query rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(std::move(lhs), std::move(rhs)));
}

#endif //C_PRIMER_5TH_QUERY_H
