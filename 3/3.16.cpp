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
        for (auto n : v1)
            cout << n << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v2.size() is " << v2.size() << endl;
    cout << "v2 is ";
    if (v2.empty())
        cout << "empty" << endl;
    else {
        for (auto n : v2)
            cout << n << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v3.size() is " << v3.size() << endl;
    cout << "v3 is ";
    if (v3.empty())
        cout << "empty" << endl;
    else {
        for (auto n : v3)
            cout << n << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v4.size() is " << v4.size() << endl;
    cout << "v4 is ";
    if (v4.empty())
        cout << "empty" << endl;
    else {
        for (auto n : v4)
            cout << n << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v5.size() is " << v5.size() << endl;
    cout << "v5 is ";
    if (v5.empty())
        cout << "empty" << endl;
    else {
        for (auto n : v5)
            cout << n << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v6.size() is " << v6.size() << endl;
    cout << "v6 is ";
    if (v6.empty())
        cout << "empty" << endl;
    else {
        for (auto s : v6)
            cout << "\"" << s << "\"" << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "v7.size() is " << v7.size() << endl;
    cout << "v7 is ";
    if (v7.empty())
        cout << "empty" << endl;
    else {
        for (auto s : v7)
            cout << "\"" << s << "\"" << ' ';
        cout << endl;
    }

    return 0;
}
