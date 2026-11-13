// Tasks 5.1 and 5.2 - four ways to reach an object, chaining with this, array of pointers
#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string owner;
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;
public:
    explicit Cart(const std::string& owner) : owner(owner) {}      // member and parameter share a name
    Cart& add(const std::string& item, double price) {
        if (n < 10) { items[n] = item; prices[n] = price; ++n; }
        return *this;                                              // *this = the object the call was made on
    }
    Cart& setDiscount(double discount) { this->discount = discount; return *this; }
    double total() const {
        double t = 0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100 - discount) / 100;
    }
    const std::string& getOwner() const { return owner; }
    const Cart* self() const { return this; }                      // 'this' is a pointer to the current object
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Cart a("Asha");                                                // (a) directly by name
    a.add("Rice", 60).add("Dal", 120);

    Cart* p = &a;                                                  // (b) through a pointer
    p->add("Oil", 180);

    Cart& r = a;                                                   // (c) through a reference
    r.setDiscount(10);

    Cart* h = new Cart("Hari");                                    // (d) heap object: new / delete
    h->add("Milk", 50).add("Bread", 40);

    std::cout << "a.total()  = " << a.total()  << '\n';
    std::cout << "p->total() = " << p->total() << '\n';
    std::cout << "r.total()  = " << r.total()  << '\n';
    std::cout << "h->total() = " << h->total() << '\n';
    std::cout << "this == &a ? " << std::boolalpha << (a.self() == &a) << '\n';

    // Task 5.2 - array of pointers; find the cart with the highest total (pointer arithmetic)
    Cart b("Bala"); b.add("Soap", 35);
    Cart* carts[3] = { &a, &b, h };
    Cart** best = carts;
    for (Cart** q = carts + 1; q < carts + 3; ++q)
        if ((*q)->total() > (*best)->total()) best = q;
    std::cout << "Highest total: " << (*best)->getOwner() << " = " << (*best)->total() << '\n';

    delete h;                                                      // release the heap object
}
