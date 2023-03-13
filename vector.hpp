#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include "iterator.hpp"
#include "utils.hpp"


namespace ft
{
    template <
        class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
        typedef T value_type;
        typedef Allocator allocator_type;

        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;

        typedef pointer                                     iterator;
        typedef const_pointer                               const_iterator;

        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

    protected:
        allocator_type  _allocator;
        size_type       _end_of_storage;
        size_type       _size;
        value_type      *_v;

        size_type get_next_size(size_type n){
            size_type   res;

            res = n > max_size() / 2 ? max_size() : _end_of_storage * 2;
            if (!res)
                res = 1;
            if (res < n)
                return (n);
            return (res);
        }

    public:
        // default
        explicit vector(const allocator_type &allocator = allocator_type()) : _allocator(allocator), _end_of_storage(0), _size(0)
        {
            _v = _allocator.allocate(0);
        }

        // avec size
        explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &allocator = allocator_type()) : _allocator(allocator), _end_of_storage(n), _size(n)
        {
            _v = _allocator.allocate(n);
            for (size_type i = 0; i < _size; i++)
            {
                _allocator.construct(_v + i, val);
            }
        }

        // 从迭代器构造vector
        // Check whether it's an integral type.  If so, it's not an iterator. SFINAE
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &allocator = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) : _allocator(allocator), _size(0),_end_of_storage(0)
        {
		_v = _allocator.allocate(0);
		assign(first, last);
		_end_of_storage = std::distance(first, last);
        }

        // copy constructor
        vector(const vector &x)
        {
            _allocator = x._allocator;
            _size = x._size;
            _end_of_storage = x._size;
            _v = _allocator.allocate(_end_of_storage);
            for (size_type i = 0; i < _size; i++)
            {
                _allocator.construct(_v + i, *(x._v + i)); //
            }
        }

        ~vector(void)
        {
            clear();
            _allocator.deallocate(_v, _end_of_storage);
        }

        vector &operator=(const vector &rhs)
        {
            if (this == &rhs)
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
            if (n > size()){
                reserve(get_next_size(n));
                insert(end(), n - size(), val);
            }
            else if (n < size()){
                erase(begin() + n, end());
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
                throw std::length_error("vector::reserve");
            }
            if (n > capacity())
            {
                T *tmp;

                size_type old_capacity = _end_of_storage;
                _end_of_storage = n;
                tmp = _allocator.allocate(_end_of_storage);
                for (size_type i = 0; i < _size; i++)
                {
                    _allocator.construct(tmp + i, *(_v + i));
                    _allocator.destroy(&_v[i]);
                }
                _allocator.deallocate(_v, old_capacity);
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

        void push_back(const value_type &val)
        {
            //如果push_back之前capacity为0, 扩展后的capacity为1，否则新capacity是旧capacity的两倍
            if (_end_of_storage == 0)
            {
                reserve(1);
            }

            // if (_size == _end_of_storage)
            if (_size  == _end_of_storage)
            {
                reserve(_size * 2);
            }
            T *end = &_v[_size];
            //_size++;
            _allocator.construct(end, val);
            _size++;
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
            if (_size + 1 > _end_of_storage)
            {
                reserve(_size * 2);
            }
            for (size_type i = _size; i > diff; i--)
            {
                _allocator.construct(&_v[i], _v[i - 1]);
                _allocator.destroy(&_v[i - 1]);
            }
            _allocator.construct(&_v[diff], val);
            _size++;
            return (begin() + diff);
        }
        // insert-fill
        void insert(iterator position, size_type n, const value_type &val)
        {
            if (_end_of_storage < _size + n){
                size_type   diff;

                diff = position - begin();
                if (_size + n > _end_of_storage){
                    size_type size_rev = std::max(_size * 2, _size + n); 
                    reserve(size_rev);
                }
                position = begin() + diff;
            }
            for (size_type i = 0; i < n; i++){
                position = insert(position, val) + 1;
            }
        }
        // insert-range
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
        {
            difference_type dist = 0;
            for (InputIterator tmp = last; tmp != first; tmp--)
            {
                dist++;
            }
            difference_type diff = position - begin();
            if (_size + dist > _end_of_storage)
            {
                reserve(_size + std::max((size_t)dist, _size));
            }
            for (difference_type i = _size; i > diff; i--)
            {
                _allocator.construct(&_v[i + dist - 1], _v[i - 1]);
                _allocator.destroy(&_v[i - 1]);
            }
            for (difference_type i = 0; i < dist; i++)
            {
                _allocator.construct(&_v[diff + i], *first);
                first++;
            }
            _size += dist;
        }

        iterator erase(iterator position)
        {
            iterator it = position;
            iterator ite = end();
            iterator ret = it;
            if (position + 1 == ite)
            {
                pop_back();
            }
            else
            {
                for (; it + 1 != ite; it++)
                {
                    //_allocator.destroy(it.base());
                    _allocator.destroy(it);
                    //_allocator.construct(it.base(), *(it + 1));
                    _allocator.construct(it, *(it + 1));
                }
                //_allocator.destroy(it.base());
                _allocator.destroy(it);
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

        void swap(vector &x)
        {
            if (*this == x)
            {
                return ;
            }
            ft::_swap(_size, x._size);
            ft::_swap(_end_of_storage, x._end_of_storage);
            ft::_swap(_v, x._v);
        }

        void clear()
        {
            for (size_type i = 0; i < _size; i++)
            {
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
        typedef typename    vector<T, Allocator>::const_iterator    it_type;
        if (lhs.size() != rhs.size())
            return (false);
        /*for (size_t i = 0; i < lhs.size(); i++)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;*/
        return ft::equal<it_type, it_type>(lhs.begin(), lhs.end(), rhs.begin());
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
