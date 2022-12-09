#ifndef VECTOR_HPP
#define VECTOR_HPP

template<class T, class Allocator = std::allocator<T>> 
class vector{
    public:
        explicit vector (const allocator_type& alloc = allocator_type()){}
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){}
            
        template <class InputIterator>         
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){}
            
        vector (const vector& x){}

    
};
#endif