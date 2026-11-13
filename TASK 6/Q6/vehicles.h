// Vehicle rental fleet - class hierarchy (Task 6, Stage 4)
#pragma once
#include <iomanip>
#include <iostream>
#include <string>

constexpr double LATE_FACTOR      = 1.5;     // late days are charged at 1.5 x daily rate
constexpr double PETROL_PER_LITRE = 105.0;   // fuel vehicles: charged per litre used
constexpr double ENERGY_PER_KWH   = 8.0;     // electric vehicles: charged per kWh used

struct ServiceDate {                          // member class (has-a)
    int day, month, year;
    std::string str() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }
};

// ---------------- abstract base ----------------
class Vehicle {
    std::string regNo;
    double dailyRate;
    bool rented = false;
protected:
    double baseCharge(int days) const { return days * dailyRate; }
    double lateCharge(int lateDays) const { return lateDays * dailyRate * LATE_FACTOR; }
public:
    Vehicle(const std::string& reg, double rate) : regNo(reg), dailyRate(rate) {}
    Vehicle(const Vehicle&) = delete;                    // fleet objects are never copied (no slicing)
    Vehicle& operator=(const Vehicle&) = delete;
    virtual ~Vehicle() = default;

    // pure virtual: every vehicle type computes its own charge
    virtual double charge(int days, int lateDays, double usage) const = 0;
    virtual std::string type() const = 0;
    virtual std::string details() const { return ""; }

    const std::string& getRegNo() const { return regNo; }
    bool isRented() const { return rented; }

    bool rent() { if (rented) return false; rented = true; return true; }
    double giveBack(int days, int lateDays, double usage) {      // returns the bill, or -1 if not rented
        if (!rented) return -1.0;
        rented = false;
        return charge(days, lateDays, usage);
    }
    void print() const {
        std::cout << std::left << std::setw(13) << type() << std::setw(8) << regNo
                  << std::right << std::setw(7) << dailyRate << "  " << std::left << std::setw(8)
                  << (rented ? "RENTED" : "free") << details() << '\n';
    }
};

// ---------------- Bicycle ----------------
class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}
    double charge(int days, int lateDays, double) const override { return baseCharge(days) + lateCharge(lateDays); }
    std::string type() const override { return "Bicycle"; }
};

// ---------------- Motor vehicles (abstract) ----------------
class MotorVehicle : public Vehicle {
protected:
    double level;                // fuel litres or charge percent
    ServiceDate serviceDue;      // member class
public:
    MotorVehicle(const std::string& reg, double rate, double lvl, ServiceDate due)
        : Vehicle(reg, rate), level(lvl), serviceDue(due) {}
    std::string details() const override {
        return "level=" + std::to_string(static_cast<int>(level)) + " service due " + serviceDue.str();
    }
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double lvl, ServiceDate due) : MotorVehicle(reg, rate, lvl, due) {}
    double charge(int days, int lateDays, double litres) const override {
        return baseCharge(days) + litres * PETROL_PER_LITRE + lateCharge(lateDays);
    }
    std::string type() const override { return "TwoWheeler"; }
};

class Car : public MotorVehicle {
protected:
    int seats;
public:
    Car(const std::string& reg, double rate, double lvl, ServiceDate due, int s) : MotorVehicle(reg, rate, lvl, due), seats(s) {}
    double charge(int days, int lateDays, double litres) const override {
        return baseCharge(days) + litres * PETROL_PER_LITRE + lateCharge(lateDays);
    }
    std::string type() const override { return "Car"; }
    std::string details() const override { return MotorVehicle::details() + " seats=" + std::to_string(seats); }
};

class ElectricCar : public Car {
    double batteryKWh;
public:
    ElectricCar(const std::string& reg, double rate, double lvl, ServiceDate due, int s, double kwh)
        : Car(reg, rate, lvl, due, s), batteryKWh(kwh) {}
    double charge(int days, int lateDays, double kwhUsed) const override {      // per kWh instead of per litre
        return baseCharge(days) + kwhUsed * ENERGY_PER_KWH + lateCharge(lateDays);
    }
    std::string type() const override { return "ElectricCar"; }
    std::string details() const override { return Car::details() + " battery=" + std::to_string(static_cast<int>(batteryKWh)) + "kWh"; }
};
