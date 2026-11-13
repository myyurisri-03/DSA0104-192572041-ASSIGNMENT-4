// Alternative: Student holds a pointer to a dynamically created Address
#include <iostream>
#include <string>
class Person {
protected:
    std::string name; int age;
public:
    Person(const std::string& n, int a) : name(n), age(a) {}
};
class Address {
    std::string city; int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};
class Student : public Person {
    long long regNo;
    Address* home;
public:
    Student(const std::string& n, int a, long long reg, const std::string& city, int pin)
        : Person(n, a), regNo(reg), home(new Address(city, pin)) {}              // constructor allocates
    Student(const Student& o) : Person(o), regNo(o.regNo), home(new Address(*o.home)) {}   // deep copy
    Student& operator=(const Student& o) {
        if (this != &o) { Person::operator=(o); regNo = o.regNo; Address* f = new Address(*o.home); delete home; home = f; }
        return *this;
    }
    ~Student() { delete home; }                                                   // destructor releases
    void print() const { std::cout << regNo << ' ' << name << " (" << age << ") " << home->str() << '\n'; }
};
int main() {
    Student s("Kavya", 19, 192311001, "Salem", 636001);
    Student t = s;
    s.print(); t.print();
}
