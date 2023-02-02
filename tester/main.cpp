#include <iostream>
#include "vector.hpp"

int main(){
    ft::vector<int> v1;
    ft::vector<int> v2(15,10);
    if (v1.empty()){
        std::cout << "size is 0.\n"; 
    }
    if (v2.empty()){
        std::cout << "size is 0.\n"; 
    }
    std::cout << "test compile.\n";
}