#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    // std::enable_if
    template <bool, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };
    
    // std::integral_constant 是所有traits类的基类
    template <class T, T Var> // T: value_type
    struct integral_constant
    {
        typedef T                           value_type;
        static const T                      value = Var;
        typedef integral_constant<T, Var>   type;
        operator T() { return Var; } //not const
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // std::is_integral
    template <class T>
    struct is_integral : public false_type {};

    template <>
    struct is_integral<bool> : public true_type {};
    template <>
    struct is_integral<char> : public true_type {};
    template <>
    struct is_integral<wchar_t> : public true_type {};
    template <>
    struct is_integral<signed char> : public true_type {};
    template <>
    struct is_integral<short int> : public true_type {};
    template <>
    struct is_integral<int> : public true_type {};
    template <>
    struct is_integral<long int> : public true_type {};
    template <>
    struct is_integral<long long int> : public true_type {};
    template <>
    struct is_integral<unsigned char> : public true_type {};
    template <>
    struct is_integral<unsigned short int> : public true_type {};
    template <>
    struct is_integral<unsigned int> : public true_type {};

    // std::equal
    template <class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!(*first1 == *first2))
            {
                return false;
            }
        }
        return true;
    }

    template< class InputIt1, class InputIt2, class BinaryPredicate >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate bp ){
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!bp(*first1, *first2))
            {
                return false;
            }
        }
        return true;
    }   

    // std::lexicographical_compare
    template <class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1){
                return false;
            }
            else if (*first1 < *first2){
                return true;
            } 
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    // std::pair
    template <class T1, class T2>
    class pair
    {  
        public:
            T1 first;
            T2 second;

        public:
            // default
            pair() : first(), second() {}
            ~pair() {}

            pair(const T1 &a, const T2 &b) : first(a), second(b) {}
            // copy constructor
            template <class A, class B>
            pair(const pair<A, B> &p) : first(p, first), second(p.second) {}
            // Member functions
            // copy assignment operator
            pair &operator=(pair const &rhs)
            {
                if (this != &rhs){
                    first = rhs.first;
                    second = rhs.second;
                }
                return (*this);
            }
    };

    // non-member functions overloads
    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first != rhs.first || lhs.second != rhs.second);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        if (lhs.first == rhs.first)
            return lhs.second < rhs.second;
        return (lhs.first < rhs.first);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs < rhs || lhs == rhs);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        if (lhs.first == rhs.first)
            return lhs.second > rhs.second;
        return (lhs.first > rhs.first);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs > rhs || lhs == rhs);
    }

    // std::make_pair
    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 l, T2 r)
    {
        return (pair<T1, T2>(l, r));
    }

    //swap
    template <typename T>
    void _swap(T &x, T &y)
    {
        T tmp = x;

        x = y;
        y = tmp;
    }

};
#endif
