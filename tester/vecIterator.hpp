#ifndef VECTITERATOR_HPP
#define VECTITERATOR_HPP

#include <iostream>
#include <cstddef>

#include "iterator.hpp"

namespace ft
{
    // member types
    // member functions
    template <class T>
    class vectIterator : ft::iterator<std::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category    iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type           value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type      difference_type;
            typedef T*                                                                              pointer;
            typedef T&                                                                              reference;

        public:
            /*constructeur and destructeur*/
            vectIterator(void) : _element(0) {}
            vectIterator(pointer element) : _element(element) {}
            vectIterator(vectIterator const &src) : _element(src._element) {}
            virtual ~vectIterator(void) {}

            vectIterator &operator=(const vectIterator &rhs)
            {
                if (this == &rhs)
                    return (*this);
                this->_element = rhs._element;
                return (*this);
            }

            // Member functions
            pointer base() const { return (_element); }

            reference &operator*() const
            {
                return (*_element);
            }

            vectIterator operator+(difference_type n) const
            {
                return (_element + n);
            }

            vectIterator &operator++()
            {
                ++_element;
                return (*this);
            }

            vectIterator operator++(int)
            {
                vectIterator tmp = *this;
                ++(*this);
                return tmp;
            }

            vectIterator &operator+=(difference_type n)
            {
                _element += n;
                return (*this);
            }

            vectIterator operator-(difference_type n) const
            {
                return (_element - n);
            }

            vectIterator &operator--()
            {
                --_element;
                return (*this);
            }

            vectIterator operator--(int)
            {
                vectIterator tmp = *this;
                --(*this);
                return tmp;
            }

            vectIterator &operator-=(difference_type n)
            {
                _element -= n;
                return (*this);
            }

            pointer operator->() const
            {
                return &(operator*());
            }

            reference operator[](difference_type n) const
            {
                return *(_element + n);
            }

        protected:
            pointer _element;
        };
        // non-memeber functions overloads
        // relational operators
        template <class T>
        bool operator==(const vectIterator<T> &lhs, const vectIterator<T> &rhs)
        {
            return (lhs.base() == rhs.base());
        }

        template <class T>
        bool operator!=(const vectIterator<T> &lhs, const vectIterator<T> &rhs)
        {
            return (lhs.base() != rhs.base());
        }

        template <class T>
        bool operator<(const vectIterator<T> &lhs, const vectIterator<T> &rhs)
        {
            return (lhs.base() < rhs.base());
        }

        template <class T>
        bool operator<=(const vectIterator<T> &lhs, const vectIterator<T> &rhs)
        {
            return (lhs.base() <= rhs.base());
        }

        template <class T>
        bool operator>(const vectIterator<T> &lhs, const vectIterator<T> &rhs)
        {
            return (lhs.base() > rhs.base());
        }

        template <class T>
        bool operator>=(const vectIterator<T> &lhs, const vectIterator<T> &rhs)
        {
            return (lhs.base() >= rhs.base());
        }
        // std::operator+
        template <class T>
        vectIterator<T> operator+(typename vectIterator<T>::difference_type n, const vectIterator<T> &_it)
        {
            return (_it + n);
        }
        // std::operator-
        template <class T>
        typename vectIterator<T>::difference_type operator-(const vectIterator<T> &lhs, const vectIterator<T> &rhs)
        {
            return (lhs.base() - rhs.base());
        }

}

#endif
