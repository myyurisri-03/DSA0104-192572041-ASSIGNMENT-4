// Task 1.2 - Repaired payroll hierarchy
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

constexpr double DA_RATE = 0.42;          // named constant replaces the magic number 0.42

class Staff {                             // abstract base: common data and interface
protected:
    std::string name;
    int id;
public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;       // pure virtual: each category has its own rule
    virtual std::string category() const = 0;
    const std::string& getName() const { return name; }
    int getId() const { return id; }
};

class SalariedStaff : public Staff {      // shared rule: basic + dearness allowance
    double basic;
protected:
    double basicWithDA() const { return basic + basic * DA_RATE; }
public:
    SalariedStaff(const std::string& n, int i, double b) : Staff(n, i), basic(b) {}
};

class Professor : public SalariedStaff {
    double research;
public:
    Professor(const std::string& n, int i, double b, double r) : SalariedStaff(n, i, b), research(r) {}
    double pay() const override { return basicWithDA() + research; }
    std::string category() const override { return "Professor"; }
};

class LabAssistant : public SalariedStaff {
public:
    LabAssistant(const std::string& n, int i, double b) : SalariedStaff(n, i, b) {}
    double pay() const override { return basicWithDA(); }
    std::string category() const override { return "LabAssistant"; }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(const std::string& n, int i, double h, double r) : Staff(n, i), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
    std::string category() const override { return "GuestFaculty"; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Dr. Meena", 101, 80000, 15000));
    staff.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000));
    staff.push_back(std::make_unique<GuestFaculty>("Anita", 103, 40, 1500));

    std::cout << std::fixed << std::setprecision(2);
    double total = 0;
    for (const auto& s : staff) {                       // one loop for all categories
        std::cout << std::left << std::setw(14) << s->category() << std::setw(12) << s->getName()
                  << std::right << std::setw(12) << s->pay() << '\n';
        total += s->pay();
    }
    std::cout << "Total payroll: " << total << '\n';
    std::cout << "sizeof(Professor)=" << sizeof(Professor) << " sizeof(LabAssistant)=" << sizeof(LabAssistant)
              << " sizeof(GuestFaculty)=" << sizeof(GuestFaculty) << '\n';
}
