// 10,000,000 charge() calls: virtual call vs switch (build with -O2)
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

struct Base { virtual ~Base() = default; virtual double charge(int d) const = 0; };
struct A : Base { double charge(int d) const override { return d * 100.0; } };
struct B : Base { double charge(int d) const override { return d * 300.0 + 10; } };
struct C : Base { double charge(int d) const override { return d * 1200.0 + 20; } };
struct D : Base { double charge(int d) const override { return d * 1500.0 + 30; } };

struct Flat { int type; };
static double chargeSwitch(const Flat& f, int d) {
    switch (f.type) { case 0: return d * 100.0; case 1: return d * 300.0 + 10; case 2: return d * 1200.0 + 20; default: return d * 1500.0 + 30; }
}

int main() {
    const int N = 10000000;
    std::vector<std::unique_ptr<Base>> objs;
    objs.push_back(std::make_unique<A>()); objs.push_back(std::make_unique<B>());
    objs.push_back(std::make_unique<C>()); objs.push_back(std::make_unique<D>());
    Flat flat[4] = {{0}, {1}, {2}, {3}};
    using clk = std::chrono::steady_clock;
    double s1 = 0, s2 = 0;
    auto t0 = clk::now();
    for (int i = 0; i < N; ++i) s1 += objs[i & 3]->charge(i & 7);
    auto t1 = clk::now();
    for (int i = 0; i < N; ++i) s2 += chargeSwitch(flat[i & 3], i & 7);
    auto t2 = clk::now();
    std::cout << "virtual call : " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms (sum=" << s1 << ")\n";
    std::cout << "switch       : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms (sum=" << s2 << ")\n";
}
