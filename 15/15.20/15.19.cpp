class Base {
    void memfcn(Base &b) { b = *this; }
};

class Pub_Derv : public Base {
    void memfcn(Base &b) { b = *this; }
};

class Priv_Derv : private Base {
    void memfcn(Base &b) { b = *this; }
};

class Prot_Derv : protected Base {
    void memfcn(Base &b) { b = *this; }
};

class Derived_from_Public : public Pub_Derv {
    void memfcn(Base &b) { b = *this; }
};

class Derived_from_Private : public Priv_Derv {
    // void memfcn(Base &b) { b = *this; } // error: 'Base' is a private member of 'Base'
    // error: cannot cast 'const Derived_from_Private' to its private base class 'const Base'
};

class Derived_from_Protected : public Prot_Derv {
    void memfcn(Base &b) { b = *this; }
};

int main() {
    return 0;
}
