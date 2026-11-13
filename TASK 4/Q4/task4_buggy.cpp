// Task 4.1 / 4.2 - the defective program, with messages added to constructors and destructors
#include <iostream>
class Account {
public:
    Account() { std::cout << "Account() "; }
    double rate() const { return 3.5; }                 // DEFECT 1: not virtual
    ~Account() { std::cout << "~Account\n"; }           // DEFECT 2: not virtual
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    SeniorAccount() { std::cout << "SeniorAccount() "; }
    double rate() const { return 4.0; }
    ~SeniorAccount() { delete[] history; std::cout << "~SeniorAccount (history released) "; }
};
int main() {
    Account* accounts[2] = { new Account, new SeniorAccount };
    std::cout << '\n';
    for (Account* a : accounts) std::cout << a->rate() << "\n";   // prints 3.5 and 3.5
    for (Account* a : accounts) delete a;                        // senior: only ~Account runs
    Account copy = SeniorAccount();                              // DEFECT 3: slicing
    std::cout << "copy.rate() = " << copy.rate() << '\n';
}
