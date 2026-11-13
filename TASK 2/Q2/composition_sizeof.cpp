// Space comparison: virtual diamond vs non-virtual diamond vs composition
#include <iostream>
#include <string>

struct Person { std::string name; int id; std::string phone; };

// 1. virtual inheritance
struct StudentV : virtual Person { std::string programme; double cgpa; };
struct StaffV   : virtual Person { std::string department; double salary; };
struct TAV : StudentV, StaffV {};

// 2. non-virtual inheritance (two Person sub-objects)
struct StudentN : Person { std::string programme; double cgpa; };
struct StaffN   : Person { std::string department; double salary; };
struct TAN : StudentN, StaffN {};

// 3. composition (has-a): a Student object and a Staff object as members
struct TAC { StudentN student; StaffN staff; };

int main() {
    std::cout << "sizeof(Person)                          = " << sizeof(Person) << '\n';
    std::cout << "sizeof(TeachingAssistant) virtual       = " << sizeof(TAV) << "  (one Person)\n";
    std::cout << "sizeof(TeachingAssistant) non-virtual   = " << sizeof(TAN) << "  (two Persons)\n";
    std::cout << "sizeof(TeachingAssistant) composition   = " << sizeof(TAC) << "  (two Persons)\n";

    TAV a; a.name = "Kavya";                  // direct, unambiguous
    TAC c; c.student.name = "Kavya"; c.staff.name = "Kavya (staff copy)";   // two separate names
    std::cout << "virtual: ta.name -> " << a.name << '\n';
    std::cout << "composition: ta.student.name -> " << c.student.name << ", ta.staff.name -> " << c.staff.name << '\n';
}
