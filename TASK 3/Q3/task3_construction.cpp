// Tasks 3.1 - 3.3: derived-class constructors, member classes, order of construction/destruction
#include <iostream>
#include <string>
using std::cout;
using std::string;

class Address {                                   // member class of Person
    string city; int pin;
public:
    Address(const string& c, int p) : city(c), pin(p) { cout << "Address "; }
    ~Address() { cout << "~Address "; }
    string str() const { return city + "-" + std::to_string(pin); }
};

class Course {                                    // member class of Student
    string title;
public:
    explicit Course(const string& t) : title(t) { cout << "Course "; }
    ~Course() { cout << "~Course "; }
    const string& getTitle() const { return title; }
};

class Person {
protected:
    string name; int id;
    Address addr;                                 // has-a
public:
    Person(const string& n, int i, const string& city, int pin) : name(n), id(i), addr(city, pin) { cout << "Person "; }
    virtual ~Person() { cout << "~Person "; }
};

class Student : virtual public Person {
protected:
    string programme;
    Course course;                                // has-a
public:
    Student(const string& n, int i, const string& city, int pin, const string& prog, const string& crs)
        : Person(n, i, city, pin), programme(prog), course(crs) { cout << "Student "; }
    ~Student() override { cout << "~Student "; }
};

class Staff : virtual public Person {
protected:
    string department;
public:
    Staff(const string& n, int i, const string& city, int pin, const string& d)
        : Person(n, i, city, pin), department(d) { cout << "Staff "; }
    ~Staff() override { cout << "~Staff "; }
};

class TeachingAssistant : public Student, public Staff {
public:
    // The most-derived class initialises the virtual base Person DIRECTLY.
    TeachingAssistant(const string& n, int i, const string& city, int pin,
                      const string& prog, const string& crs, const string& dept)
        : Person(n, i, city, pin),
          Student(n, i, city, pin, prog, crs),
          Staff(n, i, city, pin, dept) { cout << "TA "; }
    ~TeachingAssistant() override { cout << "~TA "; }
};

int main() {
    cout << "Student          : ";
    { Student s("Kavya", 1, "Salem", 636001, "MCA", "C++"); cout << "| "; }
    cout << "\nStaff            : ";
    { Staff f("Ravi", 2, "Erode", 638001, "CSE"); cout << "| "; }
    cout << "\nTeachingAssistant: ";
    { TeachingAssistant t("Arun", 3, "Chennai", 600001, "MCA", "DSA", "CSE"); cout << "| "; }
    cout << '\n';
}
