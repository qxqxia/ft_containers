#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <limits>
#include "vecIterator.hpp"
#include "templates.hpp"


template<class T, class Allocator = std::allocator<T>> 
class vector{
    public:
        typedef T           value_type;
        typedef Allocator   allocator_type;
    public:
        vector(void){}
        explicit vector(const allocator_type& alloc = allocator_type()){

        }
        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){

        }
            
        template <class InputIterator>         
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){

        }
            
        vector (const vector& x){

        }

        ~vector(void){}

        vector& operator=(vector const &x){

        }

        //iterator
        iterator begin(){
            return (iterator(this->begin));
        }

        const_iterator begin()const{
            return (const_iterator(this->begin));
        }

        iterator end(){
            return (iterator(this->end));
        }

        const_iterator end()const{
            return (const_iterator(this->end));
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
            return (this->_end - this->_begin);
        }

        size_type max_size()const{

        }

        void resize(size_type n, value_type val = value_type()){

        }

        size_type capacity()const{
            return (this->_capacity - this->_begin);
        }

        bool empty()const{
            return (size() == 0);
        }

        void reserve(size_type n){

        }

        void shrink_to_fit(){

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

        reference back(){return (*end());}
        
        const_reference back()const{return (*end());}

        //modifiers
        //assign in the range version
        template <class InputIterator>  
        void assign(InputIterator first, InputIterator last){

        }
        //assign in the file version
        void assign(size_type n, const value_type& val){

        }

        void push_back(const value_type& val){

        }

        void pop_back(){
            _allocator.destroy(this->_end - 1);
            return (this->_end);
        }
        //insert- single element
        iterator insert(iterator position, const value_type& val){

        }
        //insert-fill
        void insert(iterator position, size_type n, const value_type& val){

        }
        //insert-range
        template <class InputIterator>    
        void insert(iterator position, InputIterator first, InputIterator last){

        }
        
        iterator erase(iterator position){
            
        }

        iterator erase(iterator first, iterator last){
            for(; first != last; --last){
                erase(first);
            }
            return (iterator(first));
        }

        void swap(vector& x){

        }

        void clear(){
            size_type n = size();
            while(--n > 0){
                this->_allocator.destroy(--this->_end);
            }
        }

        template <class... Args>
        iterator emplace(const_iterator position, Args&&... args){

        }

        template <class... Args>  
        void emplace_back(Args&&... args){

        }

        //allocator
        allocator_type get_allocator() const{
            return (this->_allocator);
        }
    private:
        allocator_type  _allocator;
        pointer         _capacity;
        pointer         _begin;
        pointer         _end;
};
        
        //Non-member function overloads
        //relational operators
        template <class T, class Alloc>  
        bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){

        }

        template <class T, class Alloc>  
        bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
            return !(lhs == rhs);
        }

        template <class T, class Alloc>  
        bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
            return 
        }

        template <class T, class Alloc>  
        bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
            return 
        }

        template <class T, class Alloc>  
        bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
            return 
        }

        template <class T, class Alloc>  
        bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){

        }

        template <class T, class Alloc>  
        void swap(vector<T,Alloc>& x, vector<T,Alloc>& y){
            
        }


#endif