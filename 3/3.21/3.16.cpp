#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

using std::string;

using std::vector;

int main() {
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 42);
    vector<int> v4{10};
    vector<int> v5{10, 42};
    vector<string> v6{10};
    vector<string> v7{10, "hi"};

    cout << "v1.size() is " << v1.size() << endl;
    cout << "v1 is ";
    if (v1.empty())
        cout << "empty" << endl;
    else {
        for (auto it = v1.cbegin(); it != v1.cend(); ++it)
            cout << *it << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v2.size() is " << v2.size() << endl;
    cout << "v2 is ";
    if (v2.empty())
        cout << "empty" << endl;
    else {
        for (auto it = v2.cbegin(); it != v2.cend(); ++it)
            cout << *it << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v3.size() is " << v3.size() << endl;
    cout << "v3 is ";
    if (v3.empty())
        cout << "empty" << endl;
    else {
        for (auto it = v3.cbegin(); it != v3.cend(); ++it)
            cout << *it << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v4.size() is " << v4.size() << endl;
    cout << "v4 is ";
    if (v4.empty())
        cout << "empty" << endl;
    else {
        for (auto it = v4.cbegin(); it != v4.cend(); ++it)
            cout << *it << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v5.size() is " << v5.size() << endl;
    cout << "v5 is ";
    if (v5.empty())
        cout << "empty" << endl;
    else {
        for (auto it = v5.cbegin(); it != v5.cend(); ++it)
            cout << *it << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v6.size() is " << v6.size() << endl;
    cout << "v6 is ";
    if (v6.empty())
        cout << "empty" << endl;
    else {
        for (auto it = v6.cbegin(); it != v6.cend(); ++it)
            cout << '\"' << *it << '\"' << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v7.size() is " << v7.size() << endl;
    cout << "v7 is ";
    if (v7.empty())
        cout << "empty" << endl;
    else {
        for (auto it = v7.cbegin(); it != v7.cend(); ++it)
            cout << '\"' << *it << '\"' << ' ';
        cout << endl;
    }

    return 0;
}
