#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <limits>
#include "vecIterator.hpp"
#include "templates.hpp"

namespace ft
{
    template<class T, class Allocator = std::allocator<T>> 
        class vector{
            public:
                typedef T           value_type;
                typedef Allocator   allocator_type;
            public:
                //default
                explicit vector(const allocator_type& alloc = allocator_type()) :
                        _allocator(alloc),_end_of_storage(0),_begin(0),_end(0){}
                //avec size
                explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
                        _allocator(alloc),_end_of_storage(0),_begin(0),_end(0){
                            try{
                                this->_begin = _allocator.allocate(n);
                            }catch (std::exception &e){
                                std::cout << e.what();
                            }
                            this->_end_of_storage = this->_begin + n;
                            this->_end = this->_begin;
                            for (; n > 0; n--){
                                _allocator.construct(_end++, val);
                            }
                }

                // 从迭代器构造vector   
                // Check whether it's an integral type.  If so, it's not an iterator. SFINAE
                template <class InputIterator>         
                vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) :
                 _allocator(alloc){
                    size_type n = last - first;
                    this->_begin = _allocator.allocate(n);
                    this->_end_of_storage = this->_begin + n;
                    this->_end = this->_begin;
                    for(; n > 0; n--){
                        _allocator.construct(_end++, *first++); //
                    }
                }
                
                //copy constructor
                vector (const vector& x){
                    size_type n = x.size();
                    this->_begin = _allocator.allocate(n);
                    this->_end_of_storage = this->_begin + n;
                    iterator tmp = this->_begin; //
                    for (; n > 0; n--){
                        _allocator.construct(_end++, *tmp++);//
                    }
                }

                ~vector(void){
                    clear();
                    _allocator.deallocate(this->_begin, capacity());
                }

                vector& operator=(vector const &x){
                    if (this == &x)
                        return (*this);
                    clear();
                    size_type n = x.size();
                    if (n > capacity())
                        reserve(n);
                    iterator tmp = this->_begin;
                    for(;n > 0; n--){
                        _allocator.construct(_end++, *tmp++);
                    }
                    return (*this);
                }

                //iterator
                iterator begin(){
                    return (iterator(this->_begin));
                }

                const_iterator begin()const{
                    return (const_iterator(this->_begin));
                }

                iterator end(){
                    return (iterator(this->_end));
                }

                const_iterator end()const{
                    return (const_iterator(this->_end));
                }

                reverse_iterator rbegin(){
                    return (reverse_iterator(end()));
                }

                const_reverse_iterator rbegin()const{
                    return (const_reverse_iterator(end()));
                }

                reverse_iterator rend(){
                    return (reverse_iterator(begin()));
                }

                const_reverse_iterator rend()const{
                    return (const_reverse_iterator(begin()));
                }

                //capacity
                size_type size()const{
                    return (size_type(end() - begin()));
                }

                ??size_type max_size()const{

                }

                void resize(size_type n, value_type val = value_type()){
                    if (n < size())
                        erase(begin() + n, end());
                    else    
                        insert(end(), n - size(), val);
                }

                size_type capacity()const{
                    return (size_type(this->_end_of_storage - begin()));
                }

                bool empty()const{
                    return (size() == 0);
                }

                ??void reserve(size_type n){

                }

                //element access
                reference operator[](size_type n){
                    return (*(begin() + n));
                }
                
                const_reference operator[](size_type n) const{
                    return (*(begin() + n));
                }

                reference at(size_type n);const_reference at (size_type n) const{
                    return ((*this)[n]);
                }

                reference front(){return (*begin());}
                
                const_reference front()const{return (*begin());}

                reference back(){return (*end() - 1);}
                
                const_reference back()const{return (*end() - 1);}

                //modifiers
                //assign in the range version
                ??template <class InputIterator>  
                void assign(InputIterator first, InputIterator last){

                }
                //assign in the file version
                ??void assign(size_type n, const value_type& val){

                }

                void push_back(const value_type& val){
                    if (_end != _end_of_storage){
                        _allocator.construct(_end, val);
                        ++_end;
                    }
                    //如果push_back之前capacity为0, 扩展后的capacity为1，否则新capacity是旧capacity的两倍
                    else
                        reserve(size() != 0? size() * 2 : 1);
                }

                void pop_back(){
                    --_end;
                    destroy(_end);
                }
                //insert- single element
                ??iterator insert(iterator position, const value_type& val){

                }
                //insert-fill
                ??void insert(iterator position, size_type n, const value_type& val){

                }
                //insert-range
                ??template <class InputIterator>    
                void insert(iterator position, InputIterator first, InputIterator last){

                }
                
                iterator erase(iterator position){
                    if (position + 1 != end()){
                        std::copy(position + 1, _end, position);
                    }
                    --_end;
                    destroy(_end);
                    return (position);
                }

                iterator erase(iterator first, iterator last){
                    for(; first != last; --last){
                        erase(first);
                    }
                    return (iterator(first));
                }

                ??void swap(vector& x){

                }

                void clear(){
                    erase(begin(), end());
                }

                //allocator
                allocator_type get_allocator() const{
                    return (this->_allocator);
                }
            protected:
                allocator_type  _allocator;
                iterator        _end_of_storage;
                iterator        _begin;
                iterator        _end;
        };
                
//Non-member function overloads
//relational operators
template <class T, class Alloc>  
bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
    if (lhs.size() != rhs.size())
        return (false);
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>  
bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
    return !(lhs == rhs);
}

template <class T, class Alloc>  
bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())
}

//use operator<
template <class T, class Alloc>  
bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
    return !(rhs < lhs);
}

template <class T, class Alloc>  
bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
    return (rhs < lhs);
}

template <class T, class Alloc>  
bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
    return !(lhs < rhs);
}

template <class T, class Alloc>  
void swap(vector<T,Alloc>& x, vector<T,Alloc>& y){
    x.swap(y);
    }
}


#endif