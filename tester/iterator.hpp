#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    /*5 type d'iterators迭代器按功能分成五类:
    InputIterator：输入迭代器。支持对容器元素的逐个遍历，以及对元素的读取（input);
    OutputIterator：输出迭代器。支持对容器元素的逐个遍历，以及对元素的写入（output);
    forwardIterator：前向迭代器。向前逐个遍历元素。可以对元素读取;
    BidirectionalIterator：双向迭代器。支持向前向后逐个遍历元素，可以对元素读取;
    RandomAccessIterator：随机访问迭代器。支持O(1)时间复杂度对元素的随机位置访问，支持对元素的读取
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};*/

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
        /*迭代器要求五个类型定义
        value_type:迭代器所指对象的类型
        difference_type:两个迭代器之间距离的类型
        pointer:迭代器所指对象的原生指针类型
        reference:迭代器所指对象的原生引用类型
        iterator_category:迭代器的类型。*/
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
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };
    template <class T>
    class iterator_traits<const T *>
    {
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type rtn = 0;
        while (first != last)
        {
            first++;
            rtn++;
        }
        return (rtn);
    }

    template <class T>
    class bidirectional_iterator : iterator<std::bidirectional_iterator_tag, T>
    {
        typedef typename iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::value_type value_type;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::difference_type difference_type;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::pointer pointer;
        typedef typename iterator<std::bidirectional_iterator_tag, T>::reference reference;

    private:
        pointer m_ptr;
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

    public:
        reverse_iterator() : _it(iterator_type()) {}

        explicit reverse_iterator(iterator_type const &it)
        {
            iterator_type tmp = it;
            _it = --tmp;
        }

        reverse_iterator(reverse_iterator const &rev_it) : _it(rev_it._it) {}

        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> &it) : _it(--it.base()) {} //??reverse_iterator::base

        virtual ~reverse_iterator() {}
        // Member functions
        //++ and -- has two modeles
        iterator_type base() const
        {
            iterator_type tmp = _it;
            return ++tmp;
        }

        // Returns a reference to the element pointed to by the iterator
        reference &operator*() const
        {
            iterator_type tmp = _it;
            return *(tmp);
        }

        reverse_iterator operator+(difference_type n) const
        {
            return (reverse_iterator(_it - (n - 1)));
        }
        reverse_iterator &operator++()
        {
            --_it;
            return (*this);
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        reverse_iterator &operator+=(difference_type n)
        {
            _it -= n;
            return (*this);
        }
        reverse_iterator operator-(difference_type n) const
        {
            return (reverse_iterator(_it + (n + 1)));
        }
        reverse_iterator &operator--()
        {
            ++_it;
            return (*this);
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            --(*this);
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
            return (_it[-n]);
        }

    private:
        iterator_type _it;
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
        return (rev_it + n);
    }
    // std::operator-//??
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
    {
        return (rhs.base() - lhs.base());
    }
}

#endif