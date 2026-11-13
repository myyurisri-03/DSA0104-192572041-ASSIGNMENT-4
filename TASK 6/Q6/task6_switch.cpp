// Alternative: one Vehicle class with a type code and a switch inside charge()
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr double LATE_FACTOR = 1.5, PETROL_PER_LITRE = 105.0, ENERGY_PER_KWH = 8.0;

struct Vehicle {
    enum Type { BICYCLE, TWO_WHEELER, CAR, ELECTRIC_CAR } type;
    std::string regNo;
    double dailyRate;
    double level = 0;        // unused for BICYCLE
    int day = 0, month = 0, year = 0;   // service date: unused for BICYCLE
    int seats = 0;           // used only by CAR / ELECTRIC_CAR
    double batteryKWh = 0;   // used only by ELECTRIC_CAR

    double charge(int days, int lateDays, double usage) const {
        double base = days * dailyRate, late = lateDays * dailyRate * LATE_FACTOR;
        switch (type) {
            case BICYCLE:      return base + late;
            case TWO_WHEELER:
            case CAR:          return base + usage * PETROL_PER_LITRE + late;
            case ELECTRIC_CAR: return base + usage * ENERGY_PER_KWH + late;
        }
        return 0;
    }
};

int main() {
    std::vector<Vehicle> v = {
        {Vehicle::BICYCLE, "BC-01", 100},
        {Vehicle::TWO_WHEELER, "TW-07", 300, 8, 15, 12, 2026},
        {Vehicle::CAR, "CAR-22", 1200, 40, 1, 1, 2027, 5},
        {Vehicle::ELECTRIC_CAR, "EV-05", 1500, 90, 20, 2, 2027, 5, 40}};
    struct Ret { int days, late; double usage; } r[4] = { {3, 0, 0}, {2, 1, 3}, {2, 0, 10}, {2, 1, 25} };
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < 4; ++i)
        std::cout << std::left << std::setw(8) << v[i].regNo << std::right << "bill = Rs " << std::setw(9) << v[i].charge(r[i].days, r[i].late, r[i].usage) << '\n';
    std::cout << "sizeof(Vehicle) = " << sizeof(Vehicle) << " bytes for EVERY vehicle (a bicycle wastes the motor/seat/battery fields)\n";
}
