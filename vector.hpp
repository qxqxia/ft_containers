#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <limits>
#include <cstddef>
#include "vecIterator.hpp"
#include "templates.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T>>
    class vector
    {
    public:
        typedef T           value_type;
        typedef Allocator   allocator_type;

        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef typename allocator_type::difference_type        difference_type;
        typedef typename allocator_type::size_type              size_type;

        typedef typename ft::vectIterator<pointer>              iterator;
        typedef typename ft::vectIterator<const_pointer>        const_iterator;

        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

    protected:
        allocator_type  _allocator;
        size_type       _end_of_storage;
        size_type       _size;
        value_type      *_v;

    public:
        // default
        explicit vector(const allocator_type &allocator = allocator_type()) : _allocator(allocator), _end_of_storage(0), _size(0)
        {
            _v = _allocator.allocatorate(0);
        }

        // avec size
        explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &allocator = allocator_type()) : _allocator(allocator), _end_of_storage(n), _size(n)
        {
            _v = _allocator.allocatorate(n);
            for (size_type i = 0; i < _size; i++)
            {
                _allocator.construct(_v + i, val);
            }
        }

        // 从迭代器构造vector
        // Check whether it's an integral type.  If so, it's not an iterator. SFINAE
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &allocator = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) : _allocator(allocator), _end_of_storage(0), _size(0)
        {
            _v = _allocator.allocatorate(0);
            assign(first, last);
        }

        // copy constructor
        vector(const vector &x)
        {
            _allocator = x._allocator;
            _size = x._size;
            _end_of_storage = x._end_of_storage;
            _v = _allocator.allocatorate(_end_of_storage);
            for (size_type i = 0; i < _size; i++)
            {
                _allocator.construct(_v + i, *(x._v + i)); //
            }
        }

        ~vector(void)
        {
            clear();
            _allocator.deallocatorate(_v, _end_of_storage);
        }

        vector &operator=(vector const &x)
        {
            if (this == &x)
                return (*this);

            assign(rhs.begin(), rhs.end());
            return (*this);
        }

        // iterator
        iterator begin()
        {
            return (iterator(_v));
        }

        const_iterator begin() const
        {
            return (const_iterator(_v));
        }

        iterator end()
        {
            return (iterator(_v + size()));
        }

        const_iterator end() const
        {
            return (const_iterator(_v + size()));
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }

        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(begin()));
        }

        // capacity
        size_type size() const
        {
            return (_size);
        }

        size_type max_size() const
        {
            return _allocator.max_size();
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (n > max_size()){
                throw(std::length_error("vector::size error"));
            }
            if (n <= size()){
                for(; _size > n; _size--){
                    _allocator.destroy(&_v[_size - 1]);
                }
            }
            else
            {
                reserve(n);
                for(; _size < n; _size++){
                    _allocator.construct(_v + _size, val);
                }
            }
        }

        size_type capacity() const
        {
            return (_end_of_storage);
        }

        bool empty() const
        {
            if (_size != 0)
            {
                return false;
            }
            return true;
        }

        void reserve(size_type n)
        {
            if (n > max_size())
            {
                throw std::length_error("vector length error");
            }
            if (n > capacity())
            {
                T *tmp;

                size_type old_capacity = _end_of_storage;
                _end_of_storage = n;
                tmp = _allocator.allocatorate(_end_of_storage);
                for(size_type i = 0; i < _size; i++){
                    _allocator.construct(tmp + i; *(_v + i));
                    _allocator.destroy(&_v[i]);
                }
                _allocator.deallocatorate(_v, old_capacity);
                _v = tmp;
            }
        }

        // element access
        reference operator[](size_type n)
        {
            return (*(_v + n));
        }

        const_reference operator[](size_type n) const
        {
            return (*(_v + n));
        }

        reference at(size_type n)
        {
            if (n < 0 || n >= size())
            {
                throw(std::out_of_range("vector::at error"));
            }
            return *(_v + n);
        }

        const_reference at(size_type n) const
        {
            if (n < 0 || n >= size())
            {
                throw(std::out_of_range("vector::at const error"));
            }
            return *(_v + n);
        }

        reference front() { return (*_v); }

        const_reference front() const { return (*_v); }

        reference back() { return (*(_v + (_size - 1))); }

        const_reference back() const { return (*(_v + (_size - 1))); }

        // modifiers
        // assign in the range version
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
        {
            clear();
            for (; first != last; first++)
            {
                push_back(*first);
            }
        }
        // assign in the file version
        void assign(size_type n, const value_type &val)
        {
            clear();
            for (size_t i = 0; i < n; i++)
            {
                push_back(val);
            }
        }

        void push_back(const T &val)
        {
            //如果push_back之前capacity为0, 扩展后的capacity为1，否则新capacity是旧capacity的两倍
            if (_end_of_storage == 0)
            {
                reserve(1);
            }
            if (_size == _end_of_storage)
            {
                reserve(_size * 2);
            }
            T *end = &_v[_size]; // why &
            _size++;
            _allocator.construct(end, val);
        }

        void pop_back()
        {
            if (!empty())
            {
                _size--;
                _allocator.destroy(&_v[_size]);
            }
        }
        // insert- single element
        iterator insert(iterator position, const value_type &val)
        {
            size_type diff = position - begin();
            if (_size + 1 > _end_of_storage){
                reserve(_size + 1);
            }
            for(size_type i = _size; i > diff; i--){
                _allocator.construct(&_v[i], _v[i - 1]);
                _allocator.destroy(&_v[i - 1]);
            }
            _allocator.construct(&_v[diff], val);
            _size++;
            return (begin() + diff);
        }
        // insert-fill
        /*void insert(iterator position, size_type n, const value_type &val)
        {
            size_type diff = position - begin();
            resize(size() + n);
            position = begin() + diff;
            size_type diff_right = (end() - n) - position; //插入到结尾距离
            pointer pre_end = this->_end - n - 1;
            for (size_type i = 0; i < diff_right; i++)
                *(this->_end - 1 - i) = *pre_end--;
            for (size_type i = 0; i < n; i++)
                *(position + i) = val;
        }
        // insert-range
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
        {
            size_type diff = position - begin();
            size_type n = last - first;
            size_type diff_right = end() - position;

            resize(size() + n);
            position = begin() + diff;
            pointer pre_end = this->_end - n - 1;
            for (size_type i = 0; i < diff_right; i++)
                *(this->_end - 1 - i) = *pre_end--;
            for (size_type j = 0; j < n && first != last; j++, first++)
                *(position + j) = *first;
        }*/

        iterator erase(iterator position)
        {
            iterator it = position;
            iterator ite = end();
            iterator ret= it;
            if(position + 1 == ite){
                pop_back();
            }
            else{
                for(; it + 1 != ite; it++){
                    _allocator.destroy(it.base());
                    _allocator.construct(it.base(), *(it + 1));
                }
                _allocator.destroy(it.base());
                _size--;
            }
            return ret;
        }

        iterator erase(iterator first, iterator last)
        {
            iterator it = first;
            iterator ret;
            for (; first != last; ++first)
            {
                ret = erase(it);
            }
            return ret;
        }

        /*void swap(vector &x)
        {
            if(*this == x){
                return ;
            }
            
        }*/

        void clear()
        {
            for (size_type i = 0; i < _size; i++){
                _allocator.destroy(_v + i);
            }
            _size = 0;
        }

        // allocator
        allocator_type get_allocator() const
        {
            return (this->_allocator);
        }
    };

    // Non-member function overloads
    // relational operators
    template <class T, class Allocator>
    bool operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        for (size_t i = 0; i < lhs.size(); i++){
            if (lhs[i] != rhs[i]){
                return false;
            }
        }
        return true;
    }

    template <class T, class Allocator>
    bool operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Allocator>
    bool operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    // use operator<
    template <class T, class Allocator>
    bool operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Allocator>
    bool operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Allocator>
    bool operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Allocator>
    void swap(vector<T, Allocator> &x, vector<T, Allocator> &y)
    {
        x.swap(y);
    }
}

#endif