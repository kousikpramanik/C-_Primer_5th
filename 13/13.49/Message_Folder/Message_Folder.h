#ifndef C_PRIMER_5TH_MESSAGE_FOLDER_H
#define C_PRIMER_5TH_MESSAGE_FOLDER_H

#include <iostream>
#include <set>
#include <string>
#include <utility>

// forward declaration for Folder
class Message;

class Folder {
    friend std::ostream &operator<<(std::ostream &os, const Folder &f);

    friend void swap(Folder &lhs, Folder &rhs);

    friend class Message;

public:
    Folder() = default;

public: // copy control
    Folder(const Folder &other) : messages(other.messages) { add_to_Messages(other); }

    Folder &operator=(const Folder &other);

    ~Folder() { remove_from_Messages(); }

private: // used by friend class Message
    // add the Message to this folder
    void addMsg(Message *m) { messages.insert(m); };

    void remMsg(Message *m) { messages.erase(m); };

private: // functions used by copy and move control members
    // add this folder to the folders member of each item in messages
    void add_to_Messages(const Folder &other);

    // delete the parameter folder from the folders member of each item in messages
    void remove_from_Messages();

private:
    std::set<Message *> messages;
};

class Message {
    friend std::istream &operator>>(std::istream &is, Message &m);

    friend std::ostream &operator<<(std::ostream &os, Message &m);

    friend void swap(Message &lhs, Message &rhs);

    friend class Folder;

public: // constructors
    explicit Message(std::string str = "") : contents(std::move(str)) {}

    Message(const Message &other) : contents(other.contents), folders(other.folders) { add_to_Folders(other); }

    Message(Message &&m) : contents(std::move(m.contents)) { move_Folders(&m); }

    Message &operator=(const Message &other);

    Message &operator=(Message &&other);

    ~Message() { remove_from_Folders(); }

public: // functions
    void save(Folder &f);

    void remove(Folder &f);

private: // functions used by copy constructor, assignment, and destructor
    // add this Message to other's set of Folders
    void add_to_Folders(const Message &other);

    // remove this Message from every Folder in folders
    void remove_from_Folders();

    // move the Folder pointers from m to this Message
    void move_Folders(Message *m);

private: // data members
    std::string contents;
    std::set<Folder *> folders;
};

inline void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}

inline void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
}

inline void Message::add_to_Folders(const Message &other) {
    for (auto f : other.folders) { f->addMsg(this); }
}

inline void Message::remove_from_Folders() {
    for (auto f : folders) { f->remMsg(this); }
}

// friend functions
//forward declaration for operator<<(Folder)
std::ostream &operator<<(std::ostream &os, Message &m);

inline std::ostream &operator<<(std::ostream &os, const Folder &f) {
    for (auto m : f.messages) { os << m << '\n'; }
    return os;
}

void swap(Folder &lhs, Folder &rhs);

inline std::istream &operator>>(std::istream &is, Message &m) { return is >> m.contents; }

inline std::ostream &operator<<(std::ostream &os, Message &m) { return os << m.contents; }

void swap(Message &lhs, Message &rhs);

// member functions that require both classes defined
inline void Folder::add_to_Messages(const Folder &other) {
    for (auto m : other.messages) { m->folders.insert(this); }
}

inline void Folder::remove_from_Messages() {
    for (auto m : messages) { m->folders.erase(this); }
}

inline void Message::move_Folders(Message *m) {
    folders = std::move(m->folders);
    for (auto f : folders) {
        f->remMsg(m);
        f->addMsg(this);
    }
    m->folders.clear();
}

#endif //C_PRIMER_5TH_MESSAGE_FOLDER_H
