// Without virtual inheritance, ta.name is ambiguous (two Person sub-objects).
// Compile normally (works, virtual) or with -DNONVIRTUAL (error).
#include <iostream>
#include <string>
#ifdef NONVIRTUAL
#define VB
#else
#define VB virtual
#endif
struct Person { std::string name = "Kavya"; };
struct Student : VB Person {};
struct Staff : VB Person {};
struct TeachingAssistant : Student, Staff {};
int main() {
    TeachingAssistant ta;
    std::cout << ta.name << '\n';        // ambiguous when NONVIRTUAL
}
