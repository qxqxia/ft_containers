#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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
            typedef Category    iterator_category; //迭代器自身的类型
            typedef T           value_type;//迭代器所指向的元素的类型
            typedef Distance    difference_type; //两个迭代器之间的距离，也可以表示所指容器的最大容量
            typedef Pointer     pointer; //迭代器所指向元素的指针类型
            typedef Reference   reference; //迭代器所指向元素的引用类型
    };

    // std::iterator_traits
    //迭代器类型萃取可以提取迭代器的各个类型
    template <class Iterator> //泛化的版本
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };
    // Specializations 特化版本
    template <class T> //解决原生指针的问题
    class iterator_traits<T*>
    {
        public:
            typedef random_access_iterator_tag      iterator_category;
            typedef T                               value_type;
            typedef ptrdiff_t                       difference_type;
            typedef T*                              pointer;
            typedef T&                              reference;
    };
    template <class T>
    class iterator_traits<const T*>
    {
        public:
            typedef random_access_iterator_tag      iterator_category;
            typedef T                               value_type;
            typedef ptrdiff_t                       difference_type;
            typedef T*                              pointer;
            typedef T&                              reference;
    };

    //distance function 计算两个迭代器之间的距离
    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            first++;
            n++;
        }
        return (n);
    }

    template <class T>
    class bidirectional_iterator : iterator<std::bidirectional_iterator_tag, T>
    {
        typedef typename iterator<std::bidirectional_iterator_tag, T>::iterator_category    iterator_category;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::value_type           value_type;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::difference_type      difference_type;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::pointer              pointer;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::reference            reference;

        private:
            pointer m_ptr;
    };

    // std::reverse_iterator
    template <class Iterator>
    class reverse_iterator
    {
        public:
            // Member types
            typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename iterator_traits<Iterator>::value_type          value_type;
            typedef typename iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename iterator_traits<Iterator>::pointer             pointer;
            typedef typename iterator_traits<Iterator>::reference           reference;
            typedef Iterator                                                iterator_type;

        public:
            reverse_iterator() : _it() {}
            explicit reverse_iterator(iterator_type it):_it(it) {}
            reverse_iterator(reverse_iterator<Iterator> &rev_it) : _it(rev_it._it) {}
            virtual ~reverse_iterator() {}
            // Member functions
            //++ and -- has two modeles
            iterator_type base() const { return (this->_it);}

            //operator overload
            reverse_iterator &operator= (reverse_iterator const &rhs){
                this->_it = rhs._it;
                return (*this);
            }

            reference operator*() const
            {
                iterator_type tmp = _it;
                return *(--tmp);
            }

            reverse_iterator operator+(difference_type n) const
            {
                return (reverse_iterator(this->_it - n));
            }
            reverse_iterator &operator++()
            {
                --_it;
                return (*this);
            }
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                --(*this);
                return tmp;
            }
            reverse_iterator &operator+=(difference_type n)
            {
                _it -= n;
                return (*this);
            }
            reverse_iterator operator-(difference_type n) const
            {
                return (reverse_iterator(this->_it + n));
            }
            reverse_iterator &operator--()
            {
                ++_it;
                return (*this);
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp(*this);
                ++(this->_it);
                return tmp;
            }
            reverse_iterator &operator-=(difference_type n)
            {
                _it += n;
                return (*this);
            }
            pointer operator->() const
            {
                return &(this->operator*());
            }
            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }

        protected:
            iterator_type   _it;
        private:
            // Non-member function overloads
            friend bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
            {
                return (lhs.base() == rhs.base());
            }

            friend bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
            {
                return (lhs.base() != rhs.base());
            }

            friend bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
            {
                return (lhs.base() > rhs.base());
            }

            friend bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
            {
                return (lhs.base() >= rhs.base());
            }

            friend bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
            {
                return (lhs.base() < rhs.base());
            }

            friend bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
            {
                return (lhs.base() <= rhs.base());
            }
            // std::operator+
            friend reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
            {
                return reverse_iterator<Iterator>(rev_it.base() - n);
            }
            // std::operator-
            friend typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
            {
                return reverse_iterator<Iterator>(rhs.base() - lhs.base());
            }
    };
    
}

#endif