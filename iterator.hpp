#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    struct input_iterator_tag
    {
    };
    struct output_iterator_tag
    {
    };
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };

    // std::iterator
    // std::iterator is the base class provided to simplify definitions of the required types for iterators.
    template <class Category,
              class T,
              class Distance = std::ptrdiff_t,
              class Pointer = T *,
              class Reference = T &>
    class iterator
    {
    public:
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
    };

    // std::iterator_traits
    //迭代器类型萃取可以提取迭代器的各个类型
    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };
    // Specializations
    template <class T>
    class iterator_traits<T *>
    {
    public:
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };
    template <class T>
    class iterator_traits<const T *>
    {
    public:
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    // std::reverse_iterator
    template <class Iterator>
    class reverse_iterator
    {
    public:
        // Member types
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;
        typedef Iterator iterator_type;

    protected:
        iterator_type _it;

    public:
        reverse_iterator() : _it() {}

        explicit reverse_iterator(iterator_type it) : _it(it) {}

        reverse_iterator(const reverse_iterator &it) : _it(it._it) {}

        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> &it) : _it(it.base()) {} //??reverse_iterator::base

        virtual ~reverse_iterator() {}

        reverse_iterator &operator=(reverse_iterator const &src)
        {
            if (*this == src)
            {
                return *this;
            }
            _it = src._it;
            return *this;
        }
        //++ and -- has two modeles
        iterator_type base() const { return this->_it; }
        // Returns a reference to the element pointed to by the iterator

        reference operator*() const
        {
            iterator_type tmp = _it;
            return *(--tmp);
        }

        reverse_iterator operator+(difference_type n) const
        {
            return (reverse_iterator(_it - n));
        }

        reverse_iterator &operator++()
        {
            _it--;
            return (*this);
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            _it--;
            return tmp;
        }
        reverse_iterator &operator+=(difference_type n)
        {
            _it -= n;
            return (*this);
        }
        reverse_iterator operator-(difference_type n) const
        {
            return (reverse_iterator(_it + n));
        }
        reverse_iterator &operator--()
        {
            _it++;
            return (*this);
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            _it++;
            return tmp;
        }
        reverse_iterator &operator-=(difference_type n)
        {
            _it += n;
            return (*this);
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        reference operator[](difference_type n) const
        {
            return *(_it - n - 1);
        }
    };
    // Non-member function overloads
    // relational operators
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    // std::operator+
    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
    {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }
    // std::operator-
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return reverse_iterator<Iterator>(rhs.base() - lhs.base());
    }
}

#endif