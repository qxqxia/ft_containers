#include <iostream>
#include "vector.hpp"
#include <memory>

int main()
{
    ft::vector<int> v1;

    for(int i = 1; i < 10; i++){
        v1.push_back(i);
    }
    v1.resize(5);
    v1.resize(8,100);
    v1.resize(12);

    std::cout << "v1 contains: ";
    for(int i = 0; i < v1.size(); i++){
        std::cout << ' ' << v1[i];
    }
    std::cout << '\n';
    ft::vector<int>::size_type sz;

    ft::vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow: \n";
    for (int i = 0; i < 100; ++i)
    {
        foo.push_back(i);
        if (sz != foo.capacity())
        {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }

    ft::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);
    std::cout << "making bar grow: \n";
    for (int i = 0; i < 100; ++i)
    {
        bar.push_back(i);
        if (sz != bar.capacity())
        {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
    return 0;
}
