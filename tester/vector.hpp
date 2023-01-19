#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "utils.hpp"
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
        
        private:
                //attributes
                pointer         _array;
                allocator_type  _allocator;
                size_type       _size;
                size_type       _capacity;

                // Functions
                pointer _realloc(size_type n){
                    pointer newarray;

                    if (n > this->capacity()){
                        if (n > this->max_size())
                            throw std::length_error("length error");
                        newarray = this->get_allocator().allocate(n);
                        std::copy(this->begin(), this->end(), newarray);
                        for (long unsigned int i = 0; i < this->size(); ++i)
                            this->get_allocator().destroy(this->_array + i);
                        this->get_allocator().deallocate(this->_array, this->capacity());
                        this->_array = newarray;
                        this->_capacity = n;
                        return (newarray);
                    }
                    else
                        return (this->_array);
                }

                pointer _realloc_double(size_type n){
                    size_type   len;

                    if (this->capacity() - this->size() < n){
                        len = this->_check_len(n);
                        this->_array = this->_realloc(len);
                    }
                    return (this->_array);
                }

                size_type   _check_len(size_type n){
                    size_type   len;
        
                    if (this->max_size() - this->size() < n)
                        throw std::length_error("length error");
                    len = this->size() + std::max(this->size(), n);
                    if (len < this->size() || len > this->max_size())
                        return (this->max_size());
                    else
                        return (len);
                }

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
        
                friend void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
                    typename vector<T, Alloc>::pointer         tmp_arr;
                    typename vector<T, Alloc>::allocator_type  tmp_alloc;
                    typename vector<T, Alloc>::size_type       tmp_size;
                    typename vector<T, Alloc>::size_type       tmp_capacity;

                    tmp_arr = this->_array;
                    tmp_size = this->size();
                    tmp_capacity = this->capacity();
                    tmp_alloc = this->get_allocator();
                    this->_array = x._array;
                    this->_size = x.size();
                    this->_capacity = x.capacity();
                    this->_allocator = x.get_allocator();
                    x._array = tmp_arr;
                    x._size = tmp_size;
                    x._capacity = tmp_capacity;
                    x._allocator = tmp_alloc;
                }
                
        public:
            /*constructors & destructor*/
            //constructors
            explicit vector(const allocator_type &alloc = allocator_type()) : _allocator(alloc), _size(0), _capacity(0)
            {
                this->_array = this->_allocator.allocate(this->_capacity);
            }

            vector(const vector &x) : _allocator(x.get_allocator()), _size(x.size()), _capacity(x.capacity())
            {
                this->_array = this->_allocator.allocate(this->_capacity);
                std::copy(x.begin(), x.end(), this->begin());
            }

            explicit vector(size_type n, const value_type &value, const allocator_type &alloc) : _allocator(alloc), _size(n), _capacity(n)
            {
                this->_array = this->_allocator.allocate(this->_capacity);
                //fill range with value
                std::fill(this->begin(), this->end(), value);

            }

            template <class InputIterator>
            vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type &alloc) : _allocator(alloc), _size(last - first), _capacity(last - first)
            {
                this->_array = this->_allocator.allocate(this->_capacity);
                std::copy(first, last, this->begin());
            }

            //destructor
            ~vector()
            {
                for (long unsigned int i = 0; i < this->size(); ++i)
                    this->get_allocator().destroy(this->_array + i);
                this->_allocator.deallocate(this->_array, this->capacity());
            }

            /*operator overloads*/
            vector &operator=(const vector &x)
            {
                for(vector<T,Alloc>::iterator it = this->begin(); it < this->end(); ++it)
                {
                    this->_allocator.destroy(&*it);
                }
                this->_allocator.deallocate(this->_array, this->_capacity);
                this->_capacity = x.capacity();
                this->_size = x.size();
                this->_array = this->_allocator.allocate(this->_capacity);
                std::copy(x.begin(), x.end(), this->begin());
                return (*this);
            }

            const_reference operator[](size_type n) const
            {
                return (*(this->_array + n));
            }

            reference operator[](size_type n)
            {
                return (*(this->_array + n));
            }

            /*member function*/
            //iterator
            iterator begin() { return (iterator(this->_array)); }
            iterator end() { return (iterator(this->_array + this->_size)); }
            const_iterator begin() const { return (const_iterator(this->_array)); }
            const_iterator end() const { return (const_iterator(this->_array + this->_size)); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
            const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }
            reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
            reverse_iterator rend() { return (reverse_iterator(this->begin())); }
            
            //capacity
            size_type size() const { return (this->_size); }
            size_type max_size() const { return (this->_allocator.max_size()); } 
            
            void resize(size_type n, value_type val)
            {
                if (n > this->size())
                {
                    this->_array = this->_realloc(n);
                    std::fill_n(this->end(), n - this->size(), val);
                }
                else if(n < this->size())
                {
                    for (int i = n; i < this->size(); ++i)
                        this->get_allocator().destroy(this->_array + i);
                }
                this->_size = n;
            }

            void reserve(size_type n)
            {
                this->_array = this->_realloc(n);
            }

            size_type capacity() const { return (this->_capacity); }
            
            bool empty() const
            {
                return (this->_size == 0);
            }
            
            //access
            reference at(size_type n)
            {
                if (n >= this->size())
                    throw std::out_of_range("Out of Range error");
                return ((*this)[n]);
            }
            const_reference at(size_type n) const
            {
                if (n >= this->size())
                    throw std::out_of_range("Out of Range error");
                return ((*this)[n]);
            }
            
            reference front() { return ((*this)[0]); }
            const_reference front() const { return ((*this)[0]); }
            reference back() { return ((*this)[this->size() - 1]); }
            const_reference back() const { return ((*this)[this->size() - 1]); }
            
            //modifiers
            void assign(size_type n, const value_type &val)
            {
                value_type  *newarr;

                if (n > this->capacity())
                {
                    if (n > this->max_size())
                        throw std::length_error("length error");
                    newarr = this->get_allocator().allocate(n);
                    std::fill_n(newarr, n, val);
                    for (int i = 0; i < this->size(); ++i)
                        this->get_allocator().destroy(this->_array + i);
                    this->get_allocator().deallocate(this->_array, this->capacity());
                    this->_array = newarr;
                    this->_capacity = n;
                    this->_size = n;
                }
                else if (this->size() >= n)
                {
                    std::fill_n(this->begin(), n, val);
                    for (int i = n; i < this->size(); ++i)
                        this->get_allocator().destroy(this->_array + i);
                    this->_size = n;
                }
                else
                {   
                    std::fill_n(this->begin(), this->size(), val);
                    std::uninitialized_fill_n(\
                        this->begin() + this->size() + 1, n - this->size(), val);
                    this->_size = n;
                }
            }
            
            template <class InputIterator>
            void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
            {
                const size_type len = last - first;
                value_type      *newarr;
                InputIterator   mid;

                if (len > this->capacity())
                {
                    if (len > this->max_size())
                        throw std::length_error("length error");
                    newarr = this->get_allocator().allocate(len);
                    std::copy(first, last, newarr);
                    for (int i = 0; i < this->size(); ++i)
                        this->get_allocator().destroy(this->_array + i);
                    this->get_allocator().deallocate(this->_array, this->capacity());
                    this->_array = newarr;
                    this->_capacity = len;
                    this->_size = len;
                }
                else if (this->size() >= len)
                {
                    std::copy(first, last, this->begin());
                    for (int i = len; i < this->size(); ++i)
                        this->get_allocator().destroy(this->_array + i);
                    this->_size = len;
                }
                else
                {   
                    mid = first + this->size();
                    std::copy(first, mid, this->begin());
                    std::uninitialized_copy(mid, last, this->begin() + this->size());
                    this->_size = len;
                }
            }

            iterator insert(iterator position, const value_type &val)
            {
                unsigned int    index;

                index = position - this->begin();
                this->_array = this->_realloc_double(1);
                position = this->begin() + index;
                if (position != this->end())
                    std::copy_backward(position, this->end(), this->end() + 1);
                *position = val;
                this->_size += 1;
                return (position);
            }
            
            void insert(iterator position, size_type n, const value_type &val)
            {
                unsigned int    index;

                index = position - this->begin();
                this->_array = this->_realloc_double(n);
                position = this->begin() + index;
                if (position != this->end())
                    std::copy_backward(position, this->end(), this->end() + n);
                std::fill_n(position, n, val);
                this->_size += n;
            }
            
            template <class InputIterator>
            void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
            {
                unsigned int    index;
                unsigned int    size;
                
                size = last - first;
                index = position - this->begin();
                this->_array = this->_realloc_double(size);
                position = this->begin() + index;
                if (position != this->end())
                    std::copy_backward(position, this->end(), this->end() + size);
                std::copy(first, last, position);
                this->_size += size;
            }
            
            void push_back(const value_type &val)
            {
                size_type   n;

                if (this->size() == this->capacity())
                {
                    if (this->capacity() == 0)
                        n = 1;
                    else
                        n = this->capacity() * 2;
                    this->_array = this->_realloc(n);
                }
                this->_array[this->size()] = val;
                ++this->_size;
            }
           
            void pop_back() { 
                if (this->_size > 0){
                    this->get_allocator().destroy(&(*this)[this->_size() - 1]);
                    --this->_size;
                }
            }
            
            void clear() { 
                for(int i = 0; i < this->size(); ++i)
                    this->get_allocator().destroy(this->_array + i);
                this->_size = 0;
            }

            iterator erase(iterator position)
            {
                iterator    res(&*position);

                this->get_allocator().destroy(&*position);
                std::copy(position + 1, this->end(), position);   
                this->get_allocator().destroy(&*(this->end() - 1));
                --this->_size;
                return (res);
            }

            iterator erase(iterator first, iterator last)
            {
                iterator    res(first);

                for (ft::vector<T,Alloc>::iterator it = first; it < last; ++it)
                    this->get_allocator().destroy(&*it);
                std::copy(last, this->end(), first);   
                this->_size -= (last - first);
                return (res);
            }

            void swap(vector &x)
            {
                pointer         tmp_arr;
                allocator_type  tmp_alloc;
                size_type       tmp_size;
                size_type       tmp_capacity;

                tmp_arr = this->_array;
                tmp_size = this->size();
                tmp_capacity = this->capacity();
                tmp_alloc = this->get_allocator();
                this->_array = x._array;
                this->_size = x.size();
                this->_capacity = x.capacity();
                this->_allocator = x.get_allocator();
                x._array = tmp_arr;
                x._size = tmp_size;
                x._capacity = tmp_capacity;
                x._allocator = tmp_alloc;
            }

            // Allocator
            allocator_type  get_allocator(void) const{
                return allocator_type(this->_allocator); 
            }
    };
}

#endif
