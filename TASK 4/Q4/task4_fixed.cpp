// Task 4.3 - repaired program: virtual functions, virtual destructor, override, no slicing
#include <iostream>
#include <memory>
class Account {
public:
    Account() { std::cout << "Account() "; }
    Account(const Account&) = delete;                    // copying (and so slicing) is impossible
    Account& operator=(const Account&) = delete;
    virtual ~Account() { std::cout << "~Account\n"; }    // virtual destructor
    virtual double rate() const { return 3.5; }          // virtual function
};
class SeniorAccount final : public Account {
    std::unique_ptr<double[]> history = std::make_unique<double[]>(100);
public:
    SeniorAccount() { std::cout << "SeniorAccount() "; }
    double rate() const override { return 4.0; }         // override checked by the compiler
    ~SeniorAccount() override { std::cout << "~SeniorAccount (history released) "; }
};
int main() {
    Account* accounts[2] = { new Account, new SeniorAccount };
    std::cout << '\n';
    for (Account* a : accounts) std::cout << a->rate() << "\n";   // 3.5 and 4
    for (Account* a : accounts) delete a;                        // both destructors run

    SeniorAccount s;                                             // use a reference instead of a copy
    const Account& ref = s;
    std::cout << "\nref.rate() = " << ref.rate() << '\n';
#ifdef TRY_SLICE
    Account copy = SeniorAccount();                              // does not compile now
#endif
}
