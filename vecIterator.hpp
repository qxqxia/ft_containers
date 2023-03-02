#ifndef VECTITERATOR_HPP
#define VECTITERATOR_HPP

#include <iostream>
#include <cstddef>

#include "iterator.hpp"

namespace ft
{
    // member types
    // member functions
    template <typename Iterator>
    class vectIterator : public ft::iterator<random_access_iterator_tag, Iterator>
    {
    protected:
        Iterator _element;

    public:
        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::reference reference;

    public:
        /*constructeur and destructeur*/
        vectIterator() : _element() {}
        explicit vectIterator(Iterator src) : _element(src) {}
        vectIterator(const vectIterator &src) : _element(src._element) {}
        // virtual ~vectIterator(void){}

        template <typename Iter> // Allow it to const_it conversion
        vectIterator(const vectIterator<Iter> &src) : _element(src.base())
        {
        }

        vectIterator operator=(vectIterator const &rhs)
        {
            if (this == &rhs)
                return (*this);
            _element = rhs._element;
            return (*this);
        }

        // Member functions
        iterator_type base() const { return (_element); }

        reference operator*() const
        {
            Iterator tmp = _element;
            return (*tmp);
        }

        vectIterator operator+(difference_type n) const
        {
            return vecIterator(_element + n);
        }

        vectIterator &operator++()
        {
            _element++;
            return (*this);
        }

        vectIterator operator++(int)
        {
            vectIterator tmp(*this);
            _element++;
            return tmp;
        }

        vectIterator &operator+=(difference_type n)
        {
            _element += n;
            return (*this);
        }

        vectIterator operator-(difference_type n) const
        {
            return vectIterator(_element - n);
        }

        vectIterator &operator--()
        {
            _element--;
            return (*this);
        }

        vectIterator operator--(int)
        {
            vectIterator tmp(*this);
            _element--;
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

        reference operator[](difference_type &n) const
        {
            return *(_element + n);
        }
    };
    // non-memeber functions overloads
    // relational operators
    template <class T,class Allocator>
    bool operator == (const vectIterator<T>& lhs, const vectIterator<T>& rhs){
        return (lhs.base() == rhs.base());
    }

    template <class T,class Allocator>
    bool operator!= (const vectIterator<T>& lhs, const vectIterator<T>& rhs){
        return (lhs.base() != rhs.base());
    }

    template <class T,class Allocator>
    bool operator<  (const vectIterator<T>& lhs, const vectIterator<T>& rhs){
        return (lhs.base() < rhs.base());
    }

    template <class T,class Allocator>
    bool operator<= (const vectIterator<T>& lhs, const vectIterator<T>& rhs){
        return !(rhs < lhs);
    }

    template <class T,class Allocator>
    bool operator>  (const vectIterator<T>& lhs, const vectIterator<T>& rhs){
        return rhs < lhs;
    }

    template <class T,class Allocator>
    bool operator>= (const vectIterator<T>& lhs, const vectIterator<T>& rhs){
        return !(lhs < rhs);
    }
    //std::operator+
    template <class T>
    vectIterator<T> operator+(typename vectIterator<T>::difference_type n, const vectIterator<T>& _it){
        return vecIterator<T>(_it.base() + n);
    }
    //std::operator-
    template <class T,class Allocator>
    typename vectIterator<T>::difference_type operator-(const vectIterator<T>& lhs, const vectIterator<T>& rhs){
        return (lhs.base() - rhs.base());
    }

}

#endif
