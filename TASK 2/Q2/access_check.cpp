// Verifies the access table. Compile normally (OK) or with -DE1 ... -DE5 to see each error.
class P { public: int pub = 1; protected: int prot = 2; private: int priv = 3; };

class DPub  : public P    { public: int f() { return pub + prot; } };     // pub, prot inherited as-is
class DProt : protected P { public: int f() { return pub + prot; } };     // pub, prot become protected
class DPriv : private P   { public: int f() { return pub + prot; } };     // pub, prot become private

class DPubDeeper  : public DPub   { public: int g() { return pub + prot; } };   // OK
class DPrivDeeper : public DPriv  {
public:
#ifdef E5
    int g() { return pub; }          // E5: P::pub is private in DPriv -> not accessible here
#else
    int g() { return 0; }
#endif
};

#ifdef E4
class Bad : public P { public: int f() { return priv; } };   // E4: private member never accessible in derived
#endif

int main() {
    DPub a; DProt b; DPriv c;
    int x = a.pub;                   // OK: public inheritance keeps public
#ifdef E1
    x += b.pub;                      // E1: protected inheritance -> pub is protected outside
#endif
#ifdef E2
    x += c.pub;                      // E2: private inheritance -> pub is private outside
#endif
#ifdef E3
    x += a.prot;                     // E3: protected member not accessible outside the class
#endif
    return x - 1 + a.f() * 0 + b.f() * 0 + c.f() * 0 + DPubDeeper().g() * 0 + DPrivDeeper().g() * 0;
}
