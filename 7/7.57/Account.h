#ifndef C_PRIMER_5TH_ACCOUNT_H
#define C_PRIMER_5TH_ACCOUNT_H

#include <iostream>
#include <string>

class Account {
    friend std::istream &read(std::istream &is, Account &obj);

    friend std::ostream &print(std::ostream &os, const Account &obj);

public: // constructors
    //Account and std::string are quite different things, so explicit
    explicit Account(const std::string &o) : owner(o) {}

    Account(const std::string &o, double a) : owner(o), amount(a) {}

    // Account and std::istream& are quite different things
    explicit Account(std::istream &is) { read(is, *this); }

public: // operate on object
    double balance();

private: // private functions
    void addinterest() { amount += amount * interestRate; }

private: // nonstatic members
    std::string owner;
    double amount = 0.0;

public: // operate on static
    static double rate() { return interestRate; }

    static void rate(double newRate) { interestRate = newRate; }

    static bool allowinterest() { return interestDay; }

    static void allowinterest(bool newDay) { interestDay = newDay; }

private: // static members
    static double interestRate;

    static bool interestDay;
};

inline double Account::balance() {
    if (interestDay)
        addinterest();

    return amount;
}

inline std::istream &read(std::istream &is, Account &obj) { return is >> obj.owner >> obj.amount; }

inline std::ostream &print(std::ostream &os, const Account &obj) { return os << obj.owner << ' ' << obj.amount; }

#endif // C_PRIMER_5TH_ACCOUNT_H
