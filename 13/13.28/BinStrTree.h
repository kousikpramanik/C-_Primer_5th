#ifndef C_PRIMER_5TH_BINSTRTREE_H
#define C_PRIMER_5TH_BINSTRTREE_H

#include <string>

class TreeNode {
    friend class BinStrTree;

private: // constructors, destructor
    explicit TreeNode(const std::string &v) : value(v) {}

    ~TreeNode();

private: // copy control
    // copyptr used to copy pointers when deleting individual nodes
    // set copyptr to false when copying entire trees
    TreeNode(const TreeNode &other, bool copyptr = true);

    TreeNode &operator=(const TreeNode &other) = delete;

private: // data members
    std::string value;
    // int count; i have no clue where this would be used
private: // pointers to children
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

inline TreeNode::~TreeNode() {
    delete left;
    delete right;
}

inline TreeNode::TreeNode(const TreeNode &other, bool copyptr) : TreeNode(other.value) {
    if (copyptr) {
        left = other.left;
        right = other.right;
    }
}

class BinStrTree {
public:
    explicit BinStrTree(const std::string &s = std::string("")) : root(new TreeNode(s)) {}

    ~BinStrTree() { delete root; }

public: // copy control
    BinStrTree(const BinStrTree &other);

    BinStrTree &operator=(const BinStrTree &other);

private:
    TreeNode *root;
};

inline BinStrTree::BinStrTree(const BinStrTree &other) : root(new TreeNode(*other.root, false)) {
    // use insert function to insert remaining nodes
}

inline BinStrTree &BinStrTree::operator=(const BinStrTree &other) {
    if (this != &other) {
        delete root;
        root = new TreeNode(*other.root, false);
        // use insert function to insert remaining nodes
    }
    return *this;
}

#endif //C_PRIMER_5TH_BINSTRTREE_H
