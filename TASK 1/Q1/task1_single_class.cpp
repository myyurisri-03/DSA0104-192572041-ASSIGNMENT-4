// Alternative: one Staff class with a type field and a switch inside pay()
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr double DA_RATE = 0.42;

struct Staff {
    enum Type { PROFESSOR, LAB_ASSISTANT, GUEST } type;
    std::string name;
    int id;
    double basic = 0, research = 0;   // unused for GUEST
    double hours = 0, rate = 0;        // unused for PROFESSOR / LAB_ASSISTANT

    double pay() const {
        switch (type) {
            case PROFESSOR:     return basic + basic * DA_RATE + research;
            case LAB_ASSISTANT: return basic + basic * DA_RATE;
            case GUEST:         return hours * rate;
        }
        return 0;
    }
};

int main() {
    std::vector<Staff> v;
    Staff p{Staff::PROFESSOR, "Dr. Meena", 101};  p.basic = 80000; p.research = 15000;
    Staff l{Staff::LAB_ASSISTANT, "Ravi", 102};   l.basic = 30000;
    Staff g{Staff::GUEST, "Anita", 103};          g.hours = 40; g.rate = 1500;
    v.push_back(p); v.push_back(l); v.push_back(g);

    std::cout << std::fixed << std::setprecision(2);
    double total = 0;
    for (const auto& s : v) { std::cout << std::left << std::setw(12) << s.name << std::right << std::setw(12) << s.pay() << '\n'; total += s.pay(); }
    std::cout << "Total payroll: " << total << '\n';
    std::cout << "sizeof(Staff) = " << sizeof(Staff) << " bytes for EVERY object (unused fields included)\n";
}
