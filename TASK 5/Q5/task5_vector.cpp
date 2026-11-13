// Alternative: std::vector<Cart> (objects stored inside the vector)
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
class Cart {
    std::string items[10]; double prices[10]; int n = 0;
public:
    Cart& add(const std::string& s, double p) { if (n < 10) { items[n] = s; prices[n] = p; ++n; } return *this; }
    double total() const { double t = 0; for (int i = 0; i < n; ++i) t += prices[i]; return t; }
};
int main() {
    std::cout << "sizeof(Cart) = " << sizeof(Cart) << " bytes (copied into the vector)   sizeof(Cart*) = " << sizeof(Cart*) << " bytes\n";
    std::vector<Cart> v;
    v.push_back(Cart().add("Item", 10));
    std::uintptr_t before = reinterpret_cast<std::uintptr_t>(&v[0]);
    std::size_t cap = v.capacity();
    while (v.capacity() == cap) v.push_back(Cart().add("Item", 10));
    std::uintptr_t after = reinterpret_cast<std::uintptr_t>(&v[0]);
    std::cout << "capacity grew " << cap << " -> " << v.capacity() << "; address of element 0 "
              << (before == after ? "stayed the same" : "CHANGED (old pointers into the vector now dangle)") << '\n';
    double best = -1; for (const Cart& c : v) if (c.total() > best) best = c.total();
    std::cout << "highest total found by one pass over " << v.size() << " carts: " << best << '\n';
}
