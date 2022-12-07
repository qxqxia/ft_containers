#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <cstddef>

namespace ft{
//std::integral_constant
template<class T, T Var> //T: value_type
struct integral_constant{
    typedef T                           value_type;
    static const T                      value = Var;
    typedef integral_constant<T, Var>   type;
    const operator value_type()const{return value;}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

//std::enable_if
template <bool, typename T=void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {typedef T type;};

//std::is_integral
template<class T>
struct is_integral: public false_type{};

template<> struct is_integral<bool>: public true_type{};
template<> struct is_integral<char>: public true_type{}; 
template<> struct is_integral<wchar_t>: public true_type{};
template<> struct is_integral<signed char>: public true_type{};
template<> struct is_integral<short int>: public true_type{};
template<> struct is_integral<int>: public true_type{};
template<> struct is_integral<long int>: public true_type{};
template<> struct is_integral<long long int>: public true_type{};
template<> struct is_integral<unsigned char>: public true_type{};
template<> struct is_integral<unsigned short int>: public true_type{};
template<> struct is_integral<unsigned int>: public true_type{};
template<> struct is_integral<unsigned long int>: public true_type{};
template<> struct is_integral<unsigned long long int>: public true_type{};

//std::equal 
template<class InputIt1, class InputIt2>
bool equal( InputIt1 first1, InputIt1 last1,InputIt2 first2 )
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)){
            return false;
            }
    }
    return true;
}

//std::lexicographical_compare
template<class InputIt1, class InputIt2>
bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
    return (first1 == last1) && (first2 != last2);
}

//std::pair
template<class T1, class T2> 
struct pair{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    public:
    pair():first(T1()), second(T2()){}
    pair(const T1& a, const T2& b) : first(a), second(b){} 
    //copy constructor
    template<class U, class V> 
    pair (const pair<U,V>& pr) : first(pr,first), second(pr.second){}
    //copy assignment operator
    pair& operator=(pair const &rhs){
        this->first = rhs.first;
        this->second = rhs.second;
        return (*this);
    }
}

//std::make_pair
template< class T1, class T2>
std::pair<T1, T2> make_pair( T1 t, T2 u){
    return (pair<T1, T2>(t, u));
}
}

#endif