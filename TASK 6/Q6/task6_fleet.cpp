// Task 6 - Stage 5: rent, return (with late charge) and list every vehicle type
#include <memory>
#include <vector>
#include "vehicles.h"

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;             // base-class pointers: one loop handles all types
    fleet.push_back(std::make_unique<Bicycle>("BC-01", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TW-07", 300, 8, ServiceDate{15, 12, 2026}));
    fleet.push_back(std::make_unique<Car>("CAR-22", 1200, 40, ServiceDate{1, 1, 2027}, 5));
    fleet.push_back(std::make_unique<ElectricCar>("EV-05", 1500, 90, ServiceDate{20, 2, 2027}, 5, 40));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- Fleet before renting ---\n";
    for (const auto& v : fleet) v->print();

    std::cout << "\n--- Renting every vehicle ---\n";
    for (const auto& v : fleet) std::cout << v->getRegNo() << (v->rent() ? " rented\n" : " NOT available\n");
    std::cout << "BC-01 again: " << (fleet[0]->rent() ? "rented" : "rejected (already rented)") << '\n';

    std::cout << "\n--- Returning (days, lateDays, usage) ---\n";
    struct Ret { int days, late; double usage; } r[4] = { {3, 0, 0}, {2, 1, 3}, {2, 0, 10}, {2, 1, 25} };
    for (std::size_t i = 0; i < fleet.size(); ++i) {
        double bill = fleet[i]->giveBack(r[i].days, r[i].late, r[i].usage);
        std::cout << std::left << std::setw(8) << fleet[i]->getRegNo() << std::right << "days=" << r[i].days
                  << " late=" << r[i].late << " usage=" << std::setw(4) << r[i].usage
                  << "  bill = Rs " << std::setw(9) << bill << '\n';
    }
    std::cout << "Returning BC-01 twice: bill = " << fleet[0]->giveBack(1, 0, 0) << " (-1 means not rented)\n";

    std::cout << "\n--- Fleet after returning ---\n";
    for (const auto& v : fleet) v->print();

    std::cout << "\nsizeof: Bicycle=" << sizeof(Bicycle) << " TwoWheeler=" << sizeof(TwoWheeler)
              << " Car=" << sizeof(Car) << " ElectricCar=" << sizeof(ElectricCar) << '\n';
}
