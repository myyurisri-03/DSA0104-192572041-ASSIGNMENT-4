// Adding a NEW vehicle type (ElectricBus) WITHOUT changing vehicles.h or any existing class
#include <memory>
#include <vector>
#include "vehicles.h"

class ElectricBus : public MotorVehicle {
    int seats; double batteryKWh;
public:
    ElectricBus(const std::string& reg, double rate, double lvl, ServiceDate due, int s, double kwh)
        : MotorVehicle(reg, rate, lvl, due), seats(s), batteryKWh(kwh) {}
    double charge(int days, int lateDays, double kwhUsed) const override {
        return baseCharge(days) + kwhUsed * ENERGY_PER_KWH + lateCharge(lateDays);
    }
    std::string type() const override { return "ElectricBus"; }
    std::string details() const override {
        return MotorVehicle::details() + " seats=" + std::to_string(seats) + " battery=" + std::to_string(static_cast<int>(batteryKWh)) + "kWh";
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Car>("CAR-22", 1200, 40, ServiceDate{1, 1, 2027}, 5));
    fleet.push_back(std::make_unique<ElectricBus>("EB-01", 6000, 95, ServiceDate{10, 3, 2027}, 40, 250));   // new type

    std::cout << std::fixed << std::setprecision(2);
    for (const auto& v : fleet) v->print();
    for (const auto& v : fleet) v->rent();
    std::cout << "CAR-22 bill: Rs " << fleet[0]->giveBack(2, 0, 10) << '\n';
    std::cout << "EB-01  bill: Rs " << fleet[1]->giveBack(1, 1, 120) << "  (1 day + 120 kWh + 1 late day)\n";
}
