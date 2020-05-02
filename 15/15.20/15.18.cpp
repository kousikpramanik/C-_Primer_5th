class Base {
};

class Pub_Derv : public Base {
};

class Priv_Derv : private Base {
};

class Prot_Derv : protected Base {
};

class Derived_from_Public : public Pub_Derv {
};

class Derived_from_Private : public Priv_Derv {
};

class Derived_from_Protected : public Prot_Derv {
};

int main() {
    Pub_Derv d1;
    Priv_Derv d2;
    Prot_Derv d3;
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;

    Base *p = &d1;
    // p = &d2; // error: cannot cast 'Priv_Derv' to its private base class 'Base'
    // p = &d3; // error: cannot cast 'Prot_Derv' to its protected base class 'Base'
    p = &dd1;
    // p = &dd2; // error: cannot cast 'Derived_from_Private' to its private base class 'Base'
    // p = &dd3; // error: cannot cast 'Derived_from_Protected' to its protected base class 'Base'
    return 0;
}
