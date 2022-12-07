#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstddef>

namespace ft{
    //5 type d'iterators
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    //std::iterator_traits
    template< class Iter >
    struct iterator_traits{
        //迭代器相关类型
        //value_type:迭代器所指对象的类型
        //difference_type:两个迭代器之间距离的类型
        //pointer:迭代器所指对象的原生指针类型
        //reference:迭代器所指对象的原生引用类型
        //iterator_category:迭代器的类型。
        typedef typename Iter::iterator_category    iterator_category;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
    }
    //Specializations
    template <class T> 
    class iterator_traits<T*> {
        public:
            typedef random_access_iterator_tag          iterator_category;
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef T*                                  pointer;
            typedef T&                                  reference;
      
    };
    template <class T> 
    class iterator_traits<const T*> {
        public:
            typedef random_access_iterator_tag          iterator_category;
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef T*                                  pointer;
            typedef T&                                  reference;
    };
    
    //std::reverse_iterator
    
}

#endif