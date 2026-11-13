// Alternative: std::vector<std::unique_ptr<Account>> - no manual delete
#include <iostream>
#include <memory>
#include <vector>
class Account {
public:
    Account() = default;
    virtual ~Account() { std::cout << "~Account\n"; }
    virtual double rate() const { return 3.5; }
};
class SeniorAccount final : public Account {
    std::unique_ptr<double[]> history = std::make_unique<double[]>(100);
public:
    double rate() const override { return 4.0; }
    ~SeniorAccount() override { std::cout << "~SeniorAccount (history released) "; }
};
int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& a : accounts) std::cout << a->rate() << '\n';
}   // vector destroyed -> every account released automatically
