#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    // std::integral_constant 是所有traits类的基类
    template <class T, T Var> // T: value_type
    struct integral_constant
    {
        typedef T value_type;
        static const T value = Var;
        typedef integral_constant<T, Var> type;
        operator T() const { return Var; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // std::enable_if
    template <bool, typename T = void>
    struct enable_if
    {
    };

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    // std::is_integral
    template <class T>
    struct is_integral : public false_type
    {
    };

    template <>
    struct is_integral<bool> : public true_type
    {
    };
    template <>
    struct is_integral<char> : public true_type
    {
    };
    template <>
    struct is_integral<wchar_t> : public true_type
    {
    };
    template <>
    struct is_integral<signed char> : public true_type
    {
    };
    template <>
    struct is_integral<short int> : public true_type
    {
    };
    template <>
    struct is_integral<int> : public true_type
    {
    };
    template <>
    struct is_integral<long int> : public true_type
    {
    };
    template <>
    struct is_integral<long long int> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned char> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned short int> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned int> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned long int> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned long long int> : public true_type
    {
    };

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

    // std::lexicographical_compare
    template <class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    // std::pair
    template <class T1, class T2>
    struct pair
    {
        // Member types
        typedef T1 first_type;
        typedef T2 second_type;
        // Member variables
        T1 first;
        T2 second;

    public:
        // default constructor
        pair(void) : first(T1()), second(T2()) {}
        pair(const T1 &a, const T2 &b) : first(a), second(b) {}
        // copy constructor
        template <class U, class V>
        pair(const pair<U, V> &pr) : first(pr, first), second(pr.second) {}
        // Member functions
        // copy assignment operator
        pair &operator=(pair const &rhs)
        {
            this->first = rhs.first;
            this->second = rhs.second;
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
        return (!(lhs == rhs));
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); // why
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (!(lhs < rhs));
    }

    // std::make_pair
    template <class T1, class T2>
    std::pair<T1, T2> make_pair(T1 t, T2 u)
    {
        return (pair<T1, T2>(t, u));
    }

    template <class T>
    class AvlNode
    {
    public:
        typedef T value_type;

    public:
        value_type *data;
        int height;
        int bf;
        AvlNode *parent;
        AvlNode *left;
        AvlNode *right;

    public:
        AvlNode() : data(nullptr), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

        AvlNode(value_type val) : data(val), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

        AvlNode(AvlNode const &src) : data(src.data), parent(src.parent), left(src.left), right(src.right), height(src.height), bf(src.bf) {}

        virtual ~AvlNode() {}

        AvlNode &operator=(AvlNode const &rhs)
        {
            if (this == &rhs)
                return *this;
            data = rhs.value;
            left = rhs.left;
            right = rhs.right;
            parent = rhs.parent;
            height = rhs.height;
            bf = rhs.bf;
            return (*this);
        }
    };

    // why
    template <class T>
    bool operator==(const AvlNode<T> &lhs, const AvlNode<T> &rhs)
    {
        std::cout << "wow" << std::endl;
        if (lhs->data == nullptr && rhs->data == nullptr)
            return true;
        return (lhs->data == rhs.data);
    }

    template <class T>
    bool operator!=(const AvlNode<T> &lhs, const AvlNode<T> &rhs)
    {
        return (!(lhs == rhs));
    }
}

// binary_function used in the map/value_compare
// binary_function is a base class for creating function objects with two arguments.

#endif