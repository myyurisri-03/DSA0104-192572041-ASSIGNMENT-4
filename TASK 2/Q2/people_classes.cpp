// Task 2.3 - class declarations with access specifiers and inheritance modes
#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;
public:
    Person(const std::string& n, int i, const std::string& ph) : name(n), id(i), phone(ph) {}
    virtual ~Person() = default;
    void show() const { std::cout << id << ' ' << name << ' ' << phone; }
};

class Student : virtual public Person {            // public + virtual: is-a Person, shared base
protected:
    std::string programme;
    double cgpa;
public:
    Student(const std::string& n, int i, const std::string& ph, const std::string& prog, double g)
        : Person(n, i, ph), programme(prog), cgpa(g) {}
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;
public:
    Staff(const std::string& n, int i, const std::string& ph, const std::string& d, double s)
        : Person(n, i, ph), department(d), salary(s) {}
};

class TeachingAssistant : public Student, public Staff {    // multiple + diamond (hybrid)
public:
    TeachingAssistant(const std::string& n, int i, const std::string& ph,
                      const std::string& prog, double g, const std::string& d, double s)
        : Person(n, i, ph), Student(n, i, ph, prog, g), Staff(n, i, ph, d, s) {}
    void print() const {
        show();                                          // one shared Person: no ambiguity
        std::cout << " | " << programme << " CGPA " << cgpa << " | " << department << " Rs " << salary << '\n';
    }
};

class ResearchScholar : public Student {                  // single inheritance from Student
    double fellowship;
public:
    ResearchScholar(const std::string& n, int i, const std::string& ph, const std::string& prog, double g, double f)
        : Person(n, i, ph), Student(n, i, ph, prog, g), fellowship(f) {}
    void print() const {
        show();
        std::cout << " | " << programme << " CGPA " << cgpa << " | fellowship Rs " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant ta("Kavya", 1001, "9876543210", "MCA", 8.7, "CSE", 25000);
    ResearchScholar rs("Arun", 1002, "9123456780", "PhD", 9.1, 31000);
    ta.print();
    rs.print();
}
