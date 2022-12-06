#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <cstddef>

namespace ft{
//std::integral_constant
template<class T, T Var> //T: value_type
struct integral_constant{
    typedef T                   type;
    typedef integral_constant   value_type;
    static const T value = Var;
    operator value_type(){
        return value;
    }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


}
#endif