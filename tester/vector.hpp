#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "vecIterator.hpp"
#include "templates.hpp"
#include "iterator.hpp"
namespace ft
{
    template <class T, class Alloc = std::allocator<T> 
    >
    class vector
    {
        public:
            typedef T                                           value_type;
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef pointer                                     iterator;
            typedef const_pointer                               const_iterator;
            typedef ft::reverse_iterator<iterator>              reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
            typedef std::size_t                                 size_type;
            typedef ptrdiff_t                                   difference_type;

        public:
            /*constructors & destructor*/
            //constructors
            explicit vector(const allocator_type &alloc = allocator_type()) : m_alloc(alloc), m_data(nullptr), m_size(0), m_capacity(0)
            {
            }
            vector(const vector &x) : m_data(nullptr), m_size(0), m_capacity(0)
            {
                *this = x;
            }
            explicit vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type()) : m_alloc(alloc), m_data(nullptr), m_size(0), m_capacity(0)
            {
                m_data = m_alloc.allocate(n);
                m_alloc.construct(m_data);
                for (unsigned long long i = 0; i < n; i++)
                {
                    m_size = i;
                    m_data[i] = std::move(value);
                }
                m_size++;
                m_capacity = n;
            }
            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : m_alloc(alloc), m_data(nullptr), m_size(0), m_capacity(0)
            {
                size_t i = 0;
                for (InputIterator it = first; it != last; it++)
                    i++;
                m_data = m_alloc.allocate(i + 1);
                m_alloc.construct(m_data);
                for (size_t j = 0; i > j; j++)
                {
                    m_size++;
                    m_data[j] = *first;
                    first++;
                }
                m_capacity = i;
            }
            //destructor
            ~vector()
            {
                m_alloc.deallocate(m_data, m_capacity);
            }
            /*operator overloads*/
            vector &operator=(const vector &x)
            {
                m_alloc.deallocate(m_data, m_capacity);
                m_data = m_alloc.allocate(x.m_capacity);
                for (size_t i = 0; i < x.m_size; i++)
                    m_data[i] = std::move(x.m_data[i]);
                m_size = x.m_size;
                m_capacity = x.m_capacity;
                return (*this);
            }

            const_reference operator[](size_type n) const
            {
                return (m_data[n]);
            }
            reference operator[](size_type n)
            {
                return (m_data[n]);
            }
            /*member function*/
            //iterator
            iterator begin() { return (iterator(m_data)); }
            //allocator_type get_allocator() const { return (m_alloc); }
            iterator end() { return (iterator(m_data + m_size)); }
            const_iterator begin() const { return (iterator(m_data)); }
            const_iterator end() const { return (iterator(m_data + m_size)); }
            const_reverse_iterator rbegin() const { return (reverse_iterator(iterator(m_data + m_size))); }
            const_reverse_iterator rend() const { return (reverse_iterator(iterator(m_data))); }
            reverse_iterator rbegin() { return (reverse_iterator(end())); }
            reverse_iterator rend() { return (reverse_iterator(begin())); }
            //capacity
            size_type size() const { return (m_size); }
            size_type max_size() const { return (m_alloc.max_size()); } 
            void resize(size_type n, value_type val = value_type())
            {
                if (n > m_size)
                {
                    if (n > m_capacity)
                    {
                        reserve(n);
                        for (; m_size < n; m_size++)
                            m_data[m_size] = val;
                    }
                    else
                    {
                        for (; m_size < n; m_size++)
                            m_data[m_size] = val;
                    }
                }
                else
                {
                    for (size_t i = m_size; i > n; i--)
                        m_data[m_size--].~value_type();
                }
            }
            void reserve(size_type n)
            {
                if (n <= m_capacity)
                    return;
                value_type *tmp = m_alloc.allocate(n);
                for (size_type i = 0; i < m_size; i++)
                    tmp[i] = m_data[i];
                m_alloc.deallocate(m_data, m_capacity);
                m_data = tmp;
                m_capacity = n;
            }
            size_type capacity() const { return (m_capacity); }
            bool empty() const
            {
                if (m_size == 0)
                    return (1);
                return (0);
            }
            //access
            reference at(size_type n)
            {
                if (n > m_size)
                    throw std::out_of_range("Out of Range error");
                return (m_data[n]);
            }
            const_reference at(size_type n) const
            {
                if (n > m_size)
                    throw std::out_of_range("Out of Range error");
                return (m_data[n]);
            }
            reference front() { return (m_data[0]); }
            const_reference front() const { return (m_data[0]); }
            reference back() { return (m_data[m_size - 1]); }
            const_reference back() const { return (m_data[m_size - 1]); }
            //modifiers
            void assign(size_type n, const value_type &val)
            {
                if (m_capacity < n)
                    reserve(n);
                for (size_t i = 0; i < n; i++)
                    m_data[i] = val;
                m_size = n;
            }
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                difference_type i = ft::distance(first, last);
                reserve(i);
                i = 0;
                m_size = 0;
                while (first != last)
                {
                    m_data[i] = *first;
                    first++;
                    m_size++;
                    i++;
                }
            }
            iterator insert(iterator position, const value_type &val)
            {
                difference_type d = ft::distance(begin(), position);
                if (m_size == 0)
                    reserve(1);
                else if (m_size + 1 > m_capacity)
                    reserve(m_capacity * 2);
                for (size_type i = d + 1; i <= m_size; i++)
                    std::swap(m_data[d], m_data[i]);
                m_alloc.construct(&m_data[d], val);
                m_size++;
                return (begin() + d);
            }
            void insert(iterator position, size_type n, const value_type &val)
            {
                difference_type d = ft::distance(begin(), position);
                long long j = d;
                if ((m_size + n) > m_capacity)
                {
                    if (n > m_size)
                        reserve(m_size + n);
                    else
                        reserve(m_capacity * 2);
                }
                else if (m_size == 0)
                    reserve(n);
                for (long long i = m_size - 1; i >= j; i--)
                    m_alloc.construct(&m_data[i + n], m_data[i]);
                for (size_type i = 0; i < n; i++)
                    m_alloc.construct(&m_data[j++], val);
                m_size += n;
            }
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
            {
                difference_type d = ft::distance(begin(), position);
                difference_type range = ft::distance(first, last);
                long long j = d;
                size_t n = range;
                if ((m_size + n) > m_capacity)
                {
                    if (n > m_size)
                        reserve(m_size + n);
                    else
                        reserve(m_capacity * 2);
                }
                else if (m_size == 0)
                    reserve(n);
                for (long long i = m_size - 1; i >= j; i--)
                    m_alloc.construct(&m_data[i + n], m_data[i]);
                for (size_type i = 0; i < n; i++)
                {
                    m_alloc.construct(&m_data[j++], *first);
                    first++;
                }
                m_size += n;
            }
            void push_back(const value_type &val)
            {
                if (m_size == 0)
                    reserve(1);
                else if (m_capacity == m_size)
                    reserve(m_capacity * 2);
                m_data[m_size] = val;
                m_size++;
            }
            void pop_back() { m_size--; }
            void clear() { m_size = 0; }
            iterator erase(iterator position)
            {
                difference_type d = std::distance(begin(), position);
                for (size_type i = d; i <= m_size - 1; i++)
                    std::swap(m_data[d], m_data[i]);
                m_size--;
                return (begin() + d);
            }
            iterator erase(iterator first, iterator last)
            {
                iterator pos(first);
                int i = 0;
                while (last != end())
                {
                    *first = *last;
                    first++;
                    last++;
                }
                for (; first != last; first++)
                    i++;
                m_size -= i;
                return (pos);
            }
            void swap(vector &x)
            {
                T *tmp_data;
                size_type tmp_size;

                tmp_data = x.m_data;
                x.m_data = this->m_data;
                this->m_data = tmp_data;
                tmp_size = x.m_size;
                x.m_size = this->m_size;
                this->m_size = tmp_size;
                tmp_size = x.m_capacity;
                x.m_capacity = this->m_capacity;
                this->m_capacity = tmp_size;
            }

            // Allocator
            allocator_type  get_allocator(void) const
            { return allocator_type(this->_allocator); }

        private:
            //attributes
            pointer         _array;
            allocator_type  _allocator;
            size_type       _size;
            size_type       _capacity;

            // Functions
            pointer _realloc(size_type n);

            pointer _realloc_double(size_type n);

            size_type   _check_len(size_type n);

            //non member funstion overloads
            friend bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
            {
                if (lhs.size() != rhs.size())
                    return (lhs.size() == rhs.size());
                return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
            }
        
            friend bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
            {
                return (!(lhs == rhs));
            }
      
            friend bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
            {
                return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
            }
        
            friend bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
            {
                return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
            }
       
            friend bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
            {
                if (lhs < rhs || lhs == rhs)
                    return (true);
                return (false);
            }
       
            friend bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
            {
                if (lhs > rhs || lhs == rhs)
                    return (true);
                return (false);
            }
     
            friend void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { x.swap(y); }
        };
        
}

#endif
