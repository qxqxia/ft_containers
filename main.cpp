#include <iostream>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

#define Macro ft
//#define Macro std

int main()
{
    /*ft::vector<int> v1;

    for(int i = 1; i < 10; i++){
        v1.push_back(i);
    }
    v1.resize(5);
    v1.resize(8,100);
    v1.resize(12);

    std::cout << "v1 contains: ";
    for(size_t i = 0; (size_t)i < v1.size(); i++){
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
    return 0;*/
    
    Macro::map<int, int>   m1;
    Macro::map<int, int>	m2;
    Macro::map<int, int>::iterator it;

    m1[1] = 42;
    m1[3] = 24;
    m1[8] = 245;

    m2[2] = 143;
    m2[4] = 124;
    m2[9] = 1245;

    it = m1.begin();
    while(it != m1.end()){
        std::cout << it->first << " - " << it->second << '\n';
        it++; 
    }
    std::cout << "\n";
    it = m2.begin();
    while(it != m2.end()){
        std::cout << it->first << " - " << it->second << '\n';
        it++; 
    }

    m1.swap(m2);
     std::cout << "\n";
	
    it = m1.begin();
    while(it != m1.end()){
        std::cout << it->first << " - " << it->second << '\n';
        it++; 
    }
    std::cout << "\n";
    it = m2.begin();
    while(it != m2.end()){
        std::cout << it->first << " - " << it->second << '\n';
        it++; 
    }
}

