#include <iostream>
#include "vector.h"

class a {
    int _a;
public:
    explicit a(int init) : _a(init) {};
    int operator()() const { return _a; }
//    ~a() { std::cout << "delete " << _a << std::endl; };
};

int main() {
    vector<a> vec;
    vec.push_back(a(10));
    for (int i = 0; i < 10; ++i) vec.push_back(a(i));
    vec.pop_back();
    std::cout << vec.pop_back()() << std::endl;
    vec.insert(0, a(0));
    vec.insert(5, a(50));
    vec.insert(vec.size() - 1, a(100));
    vec.insert(vec.size(), a(1001));
    for (int i = 0; i < vec.size(); ++i) std::cout << vec[i]() << ' '; std::cout << std::endl;
    vec.clear();
    for (int i = 0; i < vec.size(); ++i) std::cout << vec[i]() << ' '; std::cout << std::endl;
    vector<int> c;
    for (int i = 0; i < 10; ++i) c.push_back(i);
    c.insert(5, 50);
    for (int i = 0; i < c.size(); ++i) std::cout << c[i] << ' '; std::cout << std::endl;
    vector<int> b; b.push_back(1); b.push_back(2); b.push_back(3); b.pop_back();
    vector<int> d; d.push_back(4); d.push_back(5); d.push_back(6);
    b.swap(d);
    for (int i = 0; i < d.size(); ++i) std::cout << d[i] << ' '; std::cout << std::endl;
    return 0;
}