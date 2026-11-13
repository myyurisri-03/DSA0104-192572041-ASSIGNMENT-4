// Task 3.4: effect of removing virtual (compile with -DNONVIRTUAL)
#include <iostream>
#include <string>
#ifdef NONVIRTUAL
#define VB
#else
#define VB virtual
#endif
struct Person { std::string name; int id = 0; Person() { std::cout << "Person "; } ~Person() { std::cout << "~Person "; } };
struct Student : VB Person { double cgpa = 0; Student() { std::cout << "Student "; } ~Student() { std::cout << "~Student "; } };
struct Staff : VB Person { double salary = 0; Staff() { std::cout << "Staff "; } ~Staff() { std::cout << "~Staff "; } };
struct TeachingAssistant : Student, Staff {
    TeachingAssistant() { std::cout << "TA "; }
    ~TeachingAssistant() { std::cout << "~TA "; }
};
int main() {
    { TeachingAssistant ta; std::cout << "| "; }
    std::cout << "\nsizeof(Person)=" << sizeof(Person) << " sizeof(TeachingAssistant)=" << sizeof(TeachingAssistant) << '\n';
}
